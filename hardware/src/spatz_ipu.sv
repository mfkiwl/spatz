// Copyright 2021 ETH Zurich and University of Bologna.
// Licensed under the Apache License, Version 2.0, see LICENSE for details.
// SPDX-License-Identifier: Apache-2.0
//
// Author: Domenic Wüthrich, ETH Zurich
//
// The IPU distributes the operands to the four SIMD lanes and afterwards
// collects the results.

module spatz_ipu import spatz_pkg::*; import rvv_pkg::vew_e; (
    input  logic   clk_i,
    input  logic   rst_ni,
    // Operation Signals
    input  op_e    operation_i,
    input  logic   operation_valid_i,
    input  elen_t  op_s1_i,
    input  elen_t  op_s2_i,
    input  elen_t  op_d_i,
    input  elenb_t carry_i,
    input  vew_e   sew_i,
    // Result Output
    output elenb_t be_o,
    output elen_t  result_o
  );

  /////////////
  // Signals //
  /////////////

  // Is the operation signed
  logic is_signed;
  assign is_signed = operation_i inside {VMIN, VMAX, VMULH, VMULHSU};

  struct packed {
    // Input operands
    struct packed {
      logic [1:0][7:0] ew8;
      logic [15:0] ew16;
      logic [31:0] ew32;
    } [2:0] ops;
    // Input carry
    logic [1:0] ew8_carry;
    logic ew16_carry;
    logic ew32_carry;
    // Valid lanes
    logic [1:0] ew8_valid;
    logic ew16_valid;
    logic ew32_valid;
  } lane_signal_inp;

  // SIMD output signals
  struct packed {
    // Results
    logic [1:0][7:0] ew8_res;
    logic [15:0] ew16_res;
    logic [31:0] ew32_res;
  } lane_signal_res;

  /////////////////
  // Distributor //
  /////////////////

  // Distribute operands to the SIMD lanes
  always_comb begin : distributor
    lane_signal_inp = 'x;

    unique case (sew_i)
      rvv_pkg::EW_8: begin
        lane_signal_inp.ops[0].ew32   = is_signed && operation_i != VMULHSU ? 32'($signed(op_s1_i[31:24])) : 32'(op_s1_i[31:24]);
        lane_signal_inp.ops[0].ew16   = is_signed && operation_i != VMULHSU ? 16'($signed(op_s1_i[23:16])) : 16'(op_s1_i[23:16]);
        lane_signal_inp.ops[0].ew8[1] = op_s1_i[15:8];
        lane_signal_inp.ops[0].ew8[0] = op_s1_i[7:0];

        lane_signal_inp.ops[1].ew32   = is_signed ? 32'($signed(op_s2_i[31:24])) : 32'(op_s2_i[31:24]);
        lane_signal_inp.ops[1].ew16   = is_signed ? 16'($signed(op_s2_i[23:16])) : 16'(op_s2_i[23:16]);
        lane_signal_inp.ops[1].ew8[1] = op_s2_i[15:8];
        lane_signal_inp.ops[1].ew8[0] = op_s2_i[7:0];

        lane_signal_inp.ops[2].ew32   = is_signed ? 32'($signed(op_d_i[31:24])) : 32'(op_d_i[31:24]);
        lane_signal_inp.ops[2].ew16   = is_signed ? 16'($signed(op_d_i[23:16])) : 16'(op_d_i[23:16]);
        lane_signal_inp.ops[2].ew8[1] = op_d_i[15:8];
        lane_signal_inp.ops[2].ew8[0] = op_d_i[7:0];

        lane_signal_inp.ew8_carry[0] = carry_i[0];
        lane_signal_inp.ew8_carry[1] = carry_i[1];
        lane_signal_inp.ew16_carry   = carry_i[2];
        lane_signal_inp.ew32_carry   = carry_i[3];

        // Activate all lanes
        lane_signal_inp.ew32_valid = operation_valid_i;
        lane_signal_inp.ew16_valid = operation_valid_i;
        lane_signal_inp.ew8_valid  = {2{operation_valid_i}};
      end

      rvv_pkg::EW_16: begin
        lane_signal_inp.ops[0].ew32 = is_signed && operation_i != VMULHSU ? 32'($signed(op_s1_i[31:16])) : 32'(op_s1_i[31:16]);
        lane_signal_inp.ops[0].ew16 = op_s1_i[15:0];

        lane_signal_inp.ops[1].ew32 = is_signed ? 32'($signed(op_s2_i[31:16])) : 32'(op_s2_i[31:16]);
        lane_signal_inp.ops[1].ew16 = op_s2_i[15:0];

        lane_signal_inp.ops[2].ew32 = is_signed ? 32'($signed(op_d_i[31:16])) : 32'(op_d_i[31:16]);
        lane_signal_inp.ops[2].ew16 = op_d_i[15:0];

        lane_signal_inp.ew16_carry = carry_i[0];
        lane_signal_inp.ew32_carry = carry_i[1];

        // Activate the 32 and 16b lanes
        lane_signal_inp.ew32_valid = operation_valid_i;
        lane_signal_inp.ew16_valid = operation_valid_i;
        lane_signal_inp.ew8_valid  = 2'b00;
      end

      default: begin
        lane_signal_inp.ops[0].ew32 = op_s1_i;
        lane_signal_inp.ops[1].ew32 = op_s2_i;
        lane_signal_inp.ops[2].ew32 = op_d_i;
        lane_signal_inp.ew32_carry  = carry_i[0];

        // Activate the 32b lane
        lane_signal_inp.ew32_valid = operation_valid_i;
        lane_signal_inp.ew16_valid = 1'b0;
        lane_signal_inp.ew8_valid  = 2'b00;
      end
    endcase
  end

  ///////////////
  // Collector //
  ///////////////

  // Collect results from the SIMD lanes
  always_comb begin : collector
    unique case (sew_i)
      rvv_pkg::EW_8 : result_o = {lane_signal_res.ew32_res[7:0], lane_signal_res.ew16_res[7:0], lane_signal_res.ew8_res[1], lane_signal_res.ew8_res[0]};
      rvv_pkg::EW_16: result_o = {lane_signal_res.ew32_res[15:0], lane_signal_res.ew16_res};
      default: result_o        = lane_signal_res.ew32_res;
    endcase
  end

  // TODO: CHANGE
  assign be_o = '1;

  ////////////////
  // SIMD Lanes //
  ////////////////

  spatz_simd_lane #(
    .Width (8)
  ) i_simd_lane_8b_0 (
    .clk_i            (clk_i                        ),
    .rst_ni           (rst_ni                       ),
    .operation_i      (operation_i                  ),
    .operation_valid_i(lane_signal_inp.ew8_valid[0] ),
    .op_s1_i          (lane_signal_inp.ops[0].ew8[0]),
    .op_s2_i          (lane_signal_inp.ops[1].ew8[0]),
    .op_d_i           (lane_signal_inp.ops[2].ew8[0]),
    .is_signed_i      (is_signed                    ),
    .carry_i          (lane_signal_inp.ew8_carry[0] ),
    .sew_i            (sew_i                        ),
    .result_o         (lane_signal_res.ew8_res[0]   )
  );

  spatz_simd_lane #(
    .Width (8)
  ) i_simd_lane_8b_1 (
    .clk_i            (clk_i                        ),
    .rst_ni           (rst_ni                       ),
    .operation_i      (operation_i                  ),
    .operation_valid_i(lane_signal_inp.ew8_valid[1] ),
    .op_s1_i          (lane_signal_inp.ops[0].ew8[1]),
    .op_s2_i          (lane_signal_inp.ops[1].ew8[1]),
    .op_d_i           (lane_signal_inp.ops[2].ew8[1]),
    .is_signed_i      (is_signed                    ),
    .carry_i          (lane_signal_inp.ew8_carry[1] ),
    .sew_i            (sew_i                        ),
    .result_o         (lane_signal_res.ew8_res[1]   )
  );

  spatz_simd_lane #(
    .Width (16)
  ) i_simd_lane_16b_0 (
    .clk_i            (clk_i                      ),
    .rst_ni           (rst_ni                     ),
    .operation_i      (operation_i                ),
    .operation_valid_i(lane_signal_inp.ew16_valid ),
    .op_s1_i          (lane_signal_inp.ops[0].ew16),
    .op_s2_i          (lane_signal_inp.ops[1].ew16),
    .op_d_i           (lane_signal_inp.ops[2].ew16),
    .is_signed_i      (is_signed                  ),
    .carry_i          (lane_signal_inp.ew16_carry ),
    .sew_i            (sew_i                      ),
    .result_o         (lane_signal_res.ew16_res   )
  );

  spatz_simd_lane #(
    .Width (32)
  ) i_simd_lane_32b_0 (
    .clk_i            (clk_i                      ),
    .rst_ni           (rst_ni                     ),
    .operation_i      (operation_i                ),
    .operation_valid_i(lane_signal_inp.ew32_valid ),
    .op_s1_i          (lane_signal_inp.ops[0].ew32),
    .op_s2_i          (lane_signal_inp.ops[1].ew32),
    .op_d_i           (lane_signal_inp.ops[2].ew32),
    .is_signed_i      (is_signed                  ),
    .carry_i          (lane_signal_inp.ew32_carry ),
    .sew_i            (sew_i                      ),
    .result_o         (lane_signal_res.ew32_res   )
  );

endmodule : spatz_ipu
