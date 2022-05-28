// Copyright 2021 ETH Zurich and University of Bologna.
// Solderpad Hardware License, Version 0.51, see LICENSE for details.
// SPDX-License-Identifier: SHL-0.51
//
// Author: Matteo Perotti <mperotti@iis.ee.ethz.ch>
//         Basile Bougenot <bbougenot@student.ethz.ch>

#include "vector_macros.h"

void TEST_CASE1(void) {
  VSET(16, e8, m1);
  VLOAD_8(v2, 0xcd, 0x42, 0x2c, 0xc4, 0x7a, 0x7b, 0xd1, 0x21, 0x38, 0x1d, 0x2e,
          0x4f, 0xe7, 0x3d, 0x63, 0xd8);
  VLOAD_8(v3, 0x11, 0xa1, 0x7c, 0xde, 0x02, 0x38, 0x4e, 0x03, 0x1e, 0xc6, 0x16,
          0xa0, 0xca, 0x83, 0x54, 0x90);
  asm volatile("vdiv.vv v1, v2, v3");
  VCMP_I8(1, v1, 0xfd, 0x00, 0x00, 0x01, 0x3d, 0x02, 0x00, 0x0b, 0x01, 0x00,
          0x02, 0x00, 0x00, 0x00, 0x01, 0x00);

  VSET(16, e16, m1);
  VLOAD_16(v2, 0x9e55, 0xf806, 0xa137, 0xa5fc, 0x38ae, 0x58c3, 0x2a66, 0x6bd7,
           0x74e7, 0xa845, 0x2052, 0x6f9a, 0x6d88, 0x2861, 0xdaea, 0x2075);
  VLOAD_16(v3, 0x5e64, 0x0a44, 0xdde5, 0x813f, 0x78b9, 0x29be, 0x28b4, 0x1b2f,
           0xc4a3, 0x4a05, 0x5501, 0x49bb, 0xe5f8, 0xfa20, 0x4edf, 0xf892);
  asm volatile("vdiv.vv v1, v2, v3");
  VCMP_I16(2, v1, 0xffff, 0x0000, 0x0002, 0x0000, 0x0000, 0x0002, 0x0001,
           0x0003, 0xffff, 0xffff, 0x0000, 0x0001, 0xfffc, 0xfffa, 0x0000,
           0xfffc);

  VSET(16, e32, m1);
  VLOAD_32(v2, 0xed578a38, 0xba7b1912, 0xb99934ef, 0x21a85df9, 0xb01c09f2,
           0xd0cb54fc, 0x9b617331, 0xd32cf029, 0xaea08daa, 0xd76f06e2,
           0x99b8e084, 0x9fdc6bfc, 0x3103b573, 0xaf1e96b4, 0x54fe9ea1,
           0x0ceff9c0);
  VLOAD_32(v3, 0x0000002d, 0x0000001e, 0x0000003e, 0xffffffe0, 0x0000004b,
           0x00000064, 0xffffff88, 0x0000003b, 0x00000011, 0xffffffc3,
           0xffffffa2, 0x0000004b, 0xffffffcc, 0xffffffb1, 0xffffff9d,
           0xffffffba);
  asm volatile("vdiv.vv v1, v2, v3");
  VCMP_I32(3, v1, 0xff95db40, 0xfdaec51b, 0xfedd4f4f, 0xfef2bd11, 0xfeef4ea4,
           0xff872740, 0x00d6a792, 0xff3d81e7, 0xfb369eec, 0x00aa3ed6,
           0x01168b3a, 0xfeb7d87b, 0xff0eb2ab, 0x01061804, 0xff24374a,
           0xffd0afa2);
};

void TEST_CASE2(void) {
  VSET(16, e8, m1);
  VLOAD_8(v2, 0xcd, 0x42, 0x2c, 0xc4, 0x7a, 0x7b, 0xd1, 0x21, 0x38, 0x1d, 0x2e,
          0x4f, 0xe7, 0x3d, 0x63, 0xd8);
  VLOAD_8(v3, 0x11, 0xa1, 0x7c, 0xde, 0x02, 0x38, 0x4e, 0x03, 0x1e, 0xc6, 0x16,
          0xa0, 0xca, 0x83, 0x54, 0x90);
  VLOAD_8(v0, 0xAA, 0xAA);
  VCLEAR(v1);
  asm volatile("vdiv.vv v1, v2, v3, v0.t");
  VCMP_I8(5, v1, 0, 0x00, 0, 0x01, 0, 0x02, 0, 0x0b, 0, 0x00, 0, 0x00, 0, 0x00,
          0, 0x00);

  VSET(16, e16, m1);
  VLOAD_16(v2, 0x9e55, 0xf806, 0xa137, 0xa5fc, 0x38ae, 0x58c3, 0x2a66, 0x6bd7,
           0x74e7, 0xa845, 0x2052, 0x6f9a, 0x6d88, 0x2861, 0xdaea, 0x2075);
  VLOAD_16(v3, 0x5e64, 0x0a44, 0xdde5, 0x813f, 0x78b9, 0x29be, 0x28b4, 0x1b2f,
           0xc4a3, 0x4a05, 0x5501, 0x49bb, 0xe5f8, 0xfa20, 0x4edf, 0xf892);
  VLOAD_8(v0, 0xAA, 0xAA);
  VCLEAR(v1);
  asm volatile("vdiv.vv v1, v2, v3, v0.t");
  VCMP_I16(6, v1, 0, 0x0000, 0, 0x0000, 0, 0x0002, 0, 0x0003, 0, 0xffff, 0,
           0x0001, 0, 0xfffa, 0, 0xfffc);

  VSET(16, e32, m1);
  VLOAD_32(v2, 0xed578a38, 0xba7b1912, 0xb99934ef, 0x21a85df9, 0xb01c09f2,
           0xd0cb54fc, 0x9b617331, 0xd32cf029, 0xaea08daa, 0xd76f06e2,
           0x99b8e084, 0x9fdc6bfc, 0x3103b573, 0xaf1e96b4, 0x54fe9ea1,
           0x0ceff9c0);
  VLOAD_32(v3, 0x0000002d, 0x0000001e, 0x0000003e, 0xffffffe0, 0x0000004b,
           0x00000064, 0xffffff88, 0x0000003b, 0x00000011, 0xffffffc3,
           0xffffffa2, 0x0000004b, 0xffffffcc, 0xffffffb1, 0xffffff9d,
           0xffffffba);
  VLOAD_8(v0, 0xAA, 0xAA);
  VCLEAR(v1);
  asm volatile("vdiv.vv v1, v2, v3, v0.t");
  VCMP_I32(7, v1, 0, 0xfdaec51b, 0, 0xfef2bd11, 0, 0xff872740, 0, 0xff3d81e7, 0,
           0x00aa3ed6, 0, 0xfeb7d87b, 0, 0x01061804, 0, 0xffd0afa2);
};

void TEST_CASE3(void) {
  VSET(16, e8, m1);
  VLOAD_8(v2, 0x14, 0xab, 0x4d, 0xcd, 0xc3, 0x7c, 0xb5, 0xf0, 0xc1, 0x90, 0x14,
          0x59, 0x98, 0xda, 0x76, 0x84);
  int64_t scalar = 5;
  asm volatile("vdiv.vx v1, v2, %[A]" ::[A] "r"(scalar));
  VCMP_I8(9, v1, 0x04, 0xef, 0x0f, 0xf6, 0xf4, 0x18, 0xf1, 0xfd, 0xf4, 0xea,
          0x04, 0x11, 0xec, 0xf9, 0x17, 0xe8);

  VSET(16, e16, m1);
  VLOAD_16(v2, 0x19c9, 0x865a, 0x3063, 0xd5c2, 0xbe39, 0x98c7, 0x1ca7, 0x5d1e,
           0x8fdc, 0x3396, 0x9442, 0xee77, 0x7da8, 0xf200, 0xaba3, 0x4cd6);
  scalar = -538;
  asm volatile("vdiv.vx v1, v2, %[A]" ::[A] "r"(scalar));
  VCMP_I16(10, v1, 0xfff4, 0x0039, 0xffe9, 0x0014, 0x001f, 0x0031, 0xfff3,
           0xffd4, 0x0035, 0xffe8, 0x0033, 0x0008, 0xffc5, 0x0006, 0x0028,
           0xffdc);

  VSET(16, e32, m1);
  VLOAD_32(v2, 0x49dd393c, 0xfc1d701e, 0x7670b541, 0x5ef6c28f, 0x60da5cab,
           0x6be56bc4, 0x6f629cde, 0xf1ab595a, 0x3d99363b, 0xb8a7840e,
           0x84071026, 0x6697d435, 0x3768cf44, 0x82f1a5a1, 0xf5d4f40e,
           0xcda97e6d);
  scalar = 649;
  asm volatile("vdiv.vx v1, v2, %[A]" ::[A] "r"(scalar));
  VCMP_I32(11, v1, 0x001d22cc, 0xfffe77b2, 0x002eb818, 0x00257573, 0x00263435,
           0x002a8f5a, 0x002befac, 0xfffa58e4, 0x00184c36, 0xffe3db85,
           0xffcf1946, 0x002877d8, 0x0015db3d, 0xffceabd8, 0xfffbfd39,
           0xffec24e2);
};

void TEST_CASE4(void) {
  VSET(16, e8, m1);
  VLOAD_8(v2, 0x14, 0xab, 0x4d, 0xcd, 0xc3, 0x7c, 0xb5, 0xf0, 0xc1, 0x90, 0x14,
          0x59, 0x98, 0xda, 0x76, 0x84);
  int64_t scalar = 5;
  VLOAD_8(v0, 0xAA, 0xAA);
  VCLEAR(v1);
  asm volatile("vdiv.vx v1, v2, %[A], v0.t" ::[A] "r"(scalar));
  VCMP_I8(13, v1, 0, 0xef, 0, 0xf6, 0, 0x18, 0, 0xfd, 0, 0xea, 0, 0x11, 0, 0xf9,
          0, 0xe8);

  VSET(16, e16, m1);
  VLOAD_16(v2, 0x19c9, 0x865a, 0x3063, 0xd5c2, 0xbe39, 0x98c7, 0x1ca7, 0x5d1e,
           0x8fdc, 0x3396, 0x9442, 0xee77, 0x7da8, 0xf200, 0xaba3, 0x4cd6);
  scalar = -538;
  VLOAD_8(v0, 0xAA, 0xAA);
  VCLEAR(v1);
  asm volatile("vdiv.vx v1, v2, %[A], v0.t" ::[A] "r"(scalar));
  VCMP_I16(14, v1, 0, 0x0039, 0, 0x0014, 0, 0x0031, 0, 0xffd4, 0, 0xffe8, 0,
           0x0008, 0, 0x0006, 0, 0xffdc);

  VSET(16, e32, m1);
  VLOAD_32(v2, 0x49dd393c, 0xfc1d701e, 0x7670b541, 0x5ef6c28f, 0x60da5cab,
           0x6be56bc4, 0x6f629cde, 0xf1ab595a, 0x3d99363b, 0xb8a7840e,
           0x84071026, 0x6697d435, 0x3768cf44, 0x82f1a5a1, 0xf5d4f40e,
           0xcda97e6d);
  scalar = 649;
  VLOAD_8(v0, 0xAA, 0xAA);
  VCLEAR(v1);
  asm volatile("vdiv.vx v1, v2, %[A], v0.t" ::[A] "r"(scalar));
  VCMP_I32(15, v1, 0, 0xfffe77b2, 0, 0x00257573, 0, 0x002a8f5a, 0, 0xfffa58e4,
           0, 0xffe3db85, 0, 0x002877d8, 0, 0xffceabd8, 0, 0xffec24e2);
};

int main(void) {
  INIT_CHECK();
  enable_vec();

  TEST_CASE1();
  TEST_CASE2();
  TEST_CASE3();
  TEST_CASE4();

  EXIT_CHECK();
}