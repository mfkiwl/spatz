// Copyright 2021 ETH Zurich and University of Bologna.
// Solderpad Hardware License, Version 0.51, see LICENSE for details.
// SPDX-License-Identifier: SHL-0.51
//
// Author: Matteo Perotti <mperotti@iis.ee.ethz.ch>
//         Basile Bougenot <bbougenot@student.ethz.ch>

#include "vector_macros.h"

void TEST_CASE1() {
  VSET(16, e8, m1);
  VLOAD_8(v3, 0x21, 0x75, 0x7f, 0x3a, 0x50, 0x6d, 0x3f, 0x3e, 0x74, 0x11, 0x29,
          0xea, 0x14, 0xce, 0xb0, 0x37);
  VLOAD_8(v2, 0xfe, 0xa7, 0x06, 0xaa, 0x35, 0x3c, 0x2c, 0x58, 0xa1, 0xc4, 0x40,
          0x42, 0x52, 0x40, 0xa8, 0x53);
  VLOAD_8(v1, 0x30, 0xef, 0xb4, 0x12, 0x6d, 0x3b, 0x2c, 0x5e, 0xf0, 0x25, 0xd7,
          0x70, 0xc2, 0x62, 0xe0, 0x99);
  asm volatile("vmacc.vv v1, v2, v3");
  VCMP_U8(1, v1, 0xee, 0x42, 0xae, 0x96, 0xfd, 0xc7, 0x00, 0xae, 0xe4, 0x29,
          0x17, 0xc4, 0x2a, 0xe2, 0x60, 0x6e);

  VSET(16, e16, m1);
  VLOAD_16(v3, 0x1c20, 0x11e4, 0xde38, 0x642f, 0x3eb5, 0xa0af, 0x48e1, 0x5fc4,
           0x3d2a, 0x67d5, 0x3f07, 0x2889, 0x8812, 0x0bd9, 0x56f4, 0xe068);
  VLOAD_16(v2, 0x02cc, 0xd99c, 0xdba2, 0xf282, 0x0f99, 0xa219, 0x2dcc, 0x17cc,
           0xe8fb, 0x1e83, 0xed20, 0xbfee, 0xee87, 0x6b0f, 0xf6cf, 0x4cd1);
  VLOAD_16(v1, 0xe3f0, 0x42db, 0x2fde, 0x1983, 0x910c, 0x853b, 0x82aa, 0x9ac2,
           0x4631, 0x1f8b, 0x68c3, 0x6fbc, 0x3b5c, 0xf98b, 0x2db1, 0x8e75);
  asm volatile("vmacc.vv v1, v2, v3");
  VCMP_U16(2, v1, 0x8d70, 0x6dcb, 0xb74e, 0x6761, 0xa639, 0xf452, 0x22f6,
           0x86f2, 0x4e5f, 0x378a, 0xc4a3, 0x561a, 0xb8da, 0x5e42, 0xf4fd,
           0xa35d);

  VSET(16, e32, m2);
  VLOAD_32(v4, 0x0401c584, 0x69049955, 0x4a71aa0c, 0xc651666f, 0x273fcd5d,
           0x23ca1d7d, 0x599c994e, 0xb2d8adc5, 0x4710afae, 0x69c61cad,
           0x96ee5026, 0x2c197996, 0xd95da451, 0x3a654fb9, 0xbe990e4b,
           0xc41fd55a);
  VLOAD_32(v2, 0x39d5b56a, 0xc578a540, 0x51283b5c, 0x07b4ba9d, 0xe5aba5e4,
           0x28720dc8, 0x600fb42b, 0xf2937fa7, 0x4032d36f, 0xc676e3b3,
           0xf1cd5f96, 0x1c14bcbf, 0x7dea81ed, 0x40270562, 0x9577b3be,
           0xea615f0a);
  VLOAD_32(v6, 0xa055bbb6, 0x71f9a668, 0x0be640c9, 0x2336ca55, 0xca121638,
           0xbf234fb5, 0xe7c83142, 0xb7048f12, 0x8eb340e3, 0xef253e93,
           0xffef4a03, 0xdf346833, 0xd0922181, 0xf159ee1d, 0xf86a7c06,
           0xfcb24a2d);
  asm volatile("vmacc.vv v6, v2, v4");
  VCMP_U32(3, v6, 0x448bd85e, 0xf2cbc4a8, 0x5cd02119, 0xf69b4268, 0x3c60ee0c,
           0xa233b25d, 0x4c72c95c, 0xe2b1a595, 0xefb7d755, 0x95d6b28a,
           0xd3be5a47, 0x6338471d, 0xfb1a117e, 0xabe00fef, 0xbede88b0,
           0x913705b1);
}

void TEST_CASE2() {
  VSET(16, e8, m1);
  VLOAD_8(v3, 0x21, 0x75, 0x7f, 0x3a, 0x50, 0x6d, 0x3f, 0x3e, 0x74, 0x11, 0x29,
          0xea, 0x14, 0xce, 0xb0, 0x37);
  VLOAD_8(v2, 0xfe, 0xa7, 0x06, 0xaa, 0x35, 0x3c, 0x2c, 0x58, 0xa1, 0xc4, 0x40,
          0x42, 0x52, 0x40, 0xa8, 0x53);
  VLOAD_8(v1, 0x30, 0xef, 0xb4, 0x12, 0x6d, 0x3b, 0x2c, 0x5e, 0xf0, 0x25, 0xd7,
          0x70, 0xc2, 0x62, 0xe0, 0x99);
  VLOAD_8(v0, 0xAA, 0xAA);
  asm volatile("vmacc.vv v1, v2, v3, v0.t");
  VCMP_U8(5, v1, 0x30, 0x42, 0xb4, 0x96, 0x6d, 0xc7, 0x2c, 0xae, 0xf0, 0x29,
          0xd7, 0xc4, 0xc2, 0xe2, 0xe0, 0x6e);

  VSET(16, e16, m1);
  VLOAD_16(v3, 0x1c20, 0x11e4, 0xde38, 0x642f, 0x3eb5, 0xa0af, 0x48e1, 0x5fc4,
           0x3d2a, 0x67d5, 0x3f07, 0x2889, 0x8812, 0x0bd9, 0x56f4, 0xe068);
  VLOAD_16(v2, 0x02cc, 0xd99c, 0xdba2, 0xf282, 0x0f99, 0xa219, 0x2dcc, 0x17cc,
           0xe8fb, 0x1e83, 0xed20, 0xbfee, 0xee87, 0x6b0f, 0xf6cf, 0x4cd1);
  VLOAD_16(v1, 0xe3f0, 0x42db, 0x2fde, 0x1983, 0x910c, 0x853b, 0x82aa, 0x9ac2,
           0x4631, 0x1f8b, 0x68c3, 0x6fbc, 0x3b5c, 0xf98b, 0x2db1, 0x8e75);
  VLOAD_8(v0, 0xAA, 0xAA);
  asm volatile("vmacc.vv v1, v2, v3, v0.t");
  VCMP_U16(6, v1, 0xe3f0, 0x6dcb, 0x2fde, 0x6761, 0x910c, 0xf452, 0x82aa,
           0x86f2, 0x4631, 0x378a, 0x68c3, 0x561a, 0x3b5c, 0x5e42, 0x2db1,
           0xa35d);

  VSET(16, e32, m2);
  VLOAD_32(v4, 0x0401c584, 0x69049955, 0x4a71aa0c, 0xc651666f, 0x273fcd5d,
           0x23ca1d7d, 0x599c994e, 0xb2d8adc5, 0x4710afae, 0x69c61cad,
           0x96ee5026, 0x2c197996, 0xd95da451, 0x3a654fb9, 0xbe990e4b,
           0xc41fd55a);
  VLOAD_32(v2, 0x39d5b56a, 0xc578a540, 0x51283b5c, 0x07b4ba9d, 0xe5aba5e4,
           0x28720dc8, 0x600fb42b, 0xf2937fa7, 0x4032d36f, 0xc676e3b3,
           0xf1cd5f96, 0x1c14bcbf, 0x7dea81ed, 0x40270562, 0x9577b3be,
           0xea615f0a);
  VLOAD_32(v6, 0xa055bbb6, 0x71f9a668, 0x0be640c9, 0x2336ca55, 0xca121638,
           0xbf234fb5, 0xe7c83142, 0xb7048f12, 0x8eb340e3, 0xef253e93,
           0xffef4a03, 0xdf346833, 0xd0922181, 0xf159ee1d, 0xf86a7c06,
           0xfcb24a2d);
  VLOAD_8(v0, 0xAA, 0xAA);
  asm volatile("vmacc.vv v6, v2, v4, v0.t");
  VCMP_U32(7, v6, 0xa055bbb6, 0xf2cbc4a8, 0x0be640c9, 0xf69b4268, 0xca121638,
           0xa233b25d, 0xe7c83142, 0xe2b1a595, 0x8eb340e3, 0x95d6b28a,
           0xffef4a03, 0x6338471d, 0xd0922181, 0xabe00fef, 0xf86a7c06,
           0x913705b1);
}

void TEST_CASE3() {
  VSET(16, e8, m1);
  int32_t scalar = 5;
  VLOAD_8(v2, 0x60, 0xe3, 0xa0, 0xb7, 0x35, 0x23, 0xa3, 0xf4, 0x5f, 0x6e, 0x07,
          0x01, 0xe7, 0x51, 0x53, 0x29);
  VLOAD_8(v1, 0xfb, 0x1b, 0xc0, 0x36, 0xa7, 0xe0, 0xc8, 0x47, 0x57, 0xe0, 0x51,
          0xaa, 0xd2, 0x93, 0x83, 0xa8);
  asm volatile("vmacc.vx v1, %[A], v2" ::[A] "r"(scalar));
  VCMP_U8(9, v1, 0xdb, 0x8a, 0xe0, 0xc9, 0xb0, 0x8f, 0xf7, 0x0b, 0x32, 0x06,
          0x74, 0xaf, 0x55, 0x28, 0x22, 0x75);

  VSET(16, e16, m1);
  scalar = -5383;
  VLOAD_16(v2, 0x992e, 0x9a07, 0x90c3, 0xf1ce, 0xd53c, 0x8f07, 0x2d2f, 0x5ab1,
           0x0a79, 0x0523, 0x6f34, 0xe5fd, 0xc95a, 0xca1c, 0x36bf, 0x16a1);
  VLOAD_16(v1, 0x0a9f, 0x7ee0, 0x494e, 0xb6d0, 0x394c, 0xc8e7, 0xc117, 0x8108,
           0xb1af, 0x9f16, 0x22ab, 0xa244, 0xf1c9, 0xe363, 0x9bed, 0xa06f);
  asm volatile("vmacc.vx v1, %[A], v2" ::[A] "r"(scalar));
  VCMP_U16(10, v1, 0x145d, 0xb5af, 0x54f9, 0x342e, 0x78a8, 0x4cb6, 0xa9ce,
           0x8131, 0x7b60, 0x9c21, 0xd43f, 0x9759, 0x0e53, 0x109f, 0x71b4,
           0xcd08);

  VSET(16, e32, m2);
  scalar = 6474219;
  VLOAD_32(v2, 0x709e784e, 0x8e13e48a, 0xad5df7fd, 0x738c8997, 0x0a0030d0,
           0x7569b952, 0x507fd5c7, 0x5d09af12, 0x0bf1c209, 0x7be6ed49,
           0x842ba667, 0x53360ec0, 0xd85d7415, 0xf20de61f, 0x153e7e16,
           0xec5512e4);
  VLOAD_32(v4, 0xb2436fad, 0x6b162382, 0xd94eebe7, 0x9c43d906, 0xb80f178d,
           0x5cf91d42, 0x7764b8a3, 0x6269f72c, 0xb0dff3a6, 0x838d6893,
           0xa98a861e, 0x758b63de, 0xde488617, 0x371696ab, 0xc3ba8192,
           0x7ca33236);
  asm volatile("vmacc.vx v4, %[A], v2" ::[A] "r"(scalar));
  VCMP_U32(11, v4, 0x8e0d1d47, 0xf29d4830, 0xb5213626, 0xb21bb5a3, 0xbc2f367d,
           0x18eb9d88, 0x91c53550, 0x69a6ceb2, 0xc09822e9, 0x66c98b96,
           0xf6b125ab, 0xef3fae1e, 0x4c40925e, 0x6b652c20, 0x998385c4,
           0x75d88d82);
}

void TEST_CASE4() {
  VSET(16, e8, m1);
  int32_t scalar = 5;
  VLOAD_8(v2, 0x60, 0xe3, 0xa0, 0xb7, 0x35, 0x23, 0xa3, 0xf4, 0x5f, 0x6e, 0x07,
          0x01, 0xe7, 0x51, 0x53, 0x29);
  VLOAD_8(v1, 0xfb, 0x1b, 0xc0, 0x36, 0xa7, 0xe0, 0xc8, 0x47, 0x57, 0xe0, 0x51,
          0xaa, 0xd2, 0x93, 0x83, 0xa8);
  VLOAD_8(v0, 0xAA, 0xAA);
  asm volatile("vmacc.vx v1, %[A], v2, v0.t" ::[A] "r"(scalar));
  VCMP_U8(13, v1, 0xfb, 0x8a, 0xc0, 0xc9, 0xa7, 0x8f, 0xc8, 0x0b, 0x57, 0x06,
          0x51, 0xaf, 0xd2, 0x28, 0x83, 0x75);

  VSET(16, e16, m1);
  scalar = -5383;
  VLOAD_16(v2, 0x992e, 0x9a07, 0x90c3, 0xf1ce, 0xd53c, 0x8f07, 0x2d2f, 0x5ab1,
           0x0a79, 0x0523, 0x6f34, 0xe5fd, 0xc95a, 0xca1c, 0x36bf, 0x16a1);
  VLOAD_16(v1, 0x0a9f, 0x7ee0, 0x494e, 0xb6d0, 0x394c, 0xc8e7, 0xc117, 0x8108,
           0xb1af, 0x9f16, 0x22ab, 0xa244, 0xf1c9, 0xe363, 0x9bed, 0xa06f);
  VLOAD_8(v0, 0xAA, 0xAA);
  asm volatile("vmacc.vx v1, %[A], v2, v0.t" ::[A] "r"(scalar));
  VCMP_U16(14, v1, 0x0a9f, 0xb5af, 0x494e, 0x342e, 0x394c, 0x4cb6, 0xc117,
           0x8131, 0xb1af, 0x9c21, 0x22ab, 0x9759, 0xf1c9, 0x109f, 0x9bed,
           0xcd08);

  VSET(16, e32, m2);
  scalar = 6474219;
  VLOAD_32(v2, 0x709e784e, 0x8e13e48a, 0xad5df7fd, 0x738c8997, 0x0a0030d0,
           0x7569b952, 0x507fd5c7, 0x5d09af12, 0x0bf1c209, 0x7be6ed49,
           0x842ba667, 0x53360ec0, 0xd85d7415, 0xf20de61f, 0x153e7e16,
           0xec5512e4);
  VLOAD_32(v4, 0xb2436fad, 0x6b162382, 0xd94eebe7, 0x9c43d906, 0xb80f178d,
           0x5cf91d42, 0x7764b8a3, 0x6269f72c, 0xb0dff3a6, 0x838d6893,
           0xa98a861e, 0x758b63de, 0xde488617, 0x371696ab, 0xc3ba8192,
           0x7ca33236);
  VLOAD_8(v0, 0xAA, 0xAA);
  asm volatile("vmacc.vx v4, %[A], v2, v0.t" ::[A] "r"(scalar));
  VCMP_U32(15, v4, 0xb2436fad, 0xf29d4830, 0xd94eebe7, 0xb21bb5a3, 0xb80f178d,
           0x18eb9d88, 0x7764b8a3, 0x69a6ceb2, 0xb0dff3a6, 0x66c98b96,
           0xa98a861e, 0xef3fae1e, 0xde488617, 0x6b652c20, 0xc3ba8192,
           0x75d88d82);
}

int main(void) {
  INIT_CHECK();
  enable_vec();

  TEST_CASE1();
  //TEST_CASE2();
  TEST_CASE3();
  //TEST_CASE4();

  EXIT_CHECK();
}