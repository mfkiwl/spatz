// Copyright 2021 ETH Zurich and University of Bologna.
// Solderpad Hardware License, Version 0.51, see LICENSE for details.
// SPDX-License-Identifier: SHL-0.51
//
// Author: Matteo Perotti <mperotti@iis.ee.ethz.ch>
//         Basile Bougenot <bbougenot@student.ethz.ch>

#include "vector_macros.h"

void TEST_CASE1(void) {
  VSET(16, e8, m1);
  VLOAD_8(v2, 0x53, 0x4f, 0xde, 0xea, 0x47, 0x3c, 0x41, 0xf8, 0xd6, 0xd0, 0x93,
          0x35, 0xfc, 0x70, 0x33, 0xe4);
  VLOAD_8(v3, 0xaa, 0x24, 0xaa, 0xde, 0x92, 0x00, 0x7f, 0xe5, 0xb3, 0xf8, 0xa0,
          0xa8, 0xbb, 0xc6, 0x65, 0x81);
  asm volatile("vmulhsu.vv v1, v2, v3");
  VCMP_I8(1, v1, 0x37, 0x0b, 0xe9, 0xec, 0x28, 0x00, 0x20, 0xf8, 0xe2, 0xd1,
          0xbb, 0x22, 0xfd, 0x56, 0x14, 0xf1);

  VSET(16, e16, m1);
  VLOAD_16(v2, 0x0f50, 0x47f9, 0xa4ca, 0xf94d, 0x720c, 0x444c, 0x3681, 0x96bd,
           0x5d37, 0xd64e, 0xe792, 0xdb64, 0xfaa6, 0xafe6, 0xf4e8, 0xe5ea);
  VLOAD_16(v3, 0x7784, 0xa42e, 0x499b, 0x0c01, 0x9d2b, 0x600d, 0x2bbd, 0xcb41,
           0xdda1, 0xb5d7, 0xafbc, 0xc74f, 0xab45, 0x986f, 0xf0f2, 0xcf3c);
  asm volatile("vmulhsu.vv v1, v2, v3");
  VCMP_I16(2, v1, 0x0726, 0x2e28, 0xe5c6, 0xffaf, 0x4604, 0x199f, 0x094f,
           0xac6d, 0x50b3, 0xe262, 0xef3a, 0xe37f, 0xfc6b, 0xd04d, 0xf58f,
           0xeae2);

  VSET(16, e32, m1);
  VLOAD_32(v2, 0xeded4bf3, 0xc9e27167, 0x4175509c, 0x80a3ae04, 0x9f1b2c07,
           0x87ea397b, 0x862e2800, 0x3cd09f37, 0x9a313d78, 0x596661ee,
           0x31f99717, 0x64e65802, 0xbd567027, 0xf7c459be, 0x57b6d9cd,
           0x94bc3eb4);
  VLOAD_32(v3, 0xa147b233, 0x19880f3d, 0x8dd8815e, 0xbc318dca, 0x2c436b94,
           0x29ba4191, 0x637f89b7, 0xe39d7818, 0xf48ff2d6, 0xb1dc7c7e,
           0xfa5da298, 0x5c1aae36, 0x83e04069, 0xecf36c08, 0x40d2e3a3,
           0xe7468a97);
  asm volatile("vmulhsu.vv v1, v2, v3");
  VCMP_I32(3, v1, 0xf49d2cff, 0xfa9a5a26, 0x2444f976, 0xa25f8c94, 0xef3f26f6,
           0xec6d24a0, 0xd0a728d5, 0x361265a6, 0x9ebdaf85, 0x3e1cc92b,
           0x30e004f5, 0x244d4baf, 0xdda8d640, 0xf8612ea2, 0x1635f870,
           0x9f184dfb);
};

void TEST_CASE2(void) {
  VSET(16, e8, m1);
  VLOAD_8(v2, 0x53, 0x4f, 0xde, 0xea, 0x47, 0x3c, 0x41, 0xf8, 0xd6, 0xd0, 0x93,
          0x35, 0xfc, 0x70, 0x33, 0xe4);
  VLOAD_8(v3, 0xaa, 0x24, 0xaa, 0xde, 0x92, 0x00, 0x7f, 0xe5, 0xb3, 0xf8, 0xa0,
          0xa8, 0xbb, 0xc6, 0x65, 0x81);
  VLOAD_8(v0, 0xAA, 0xAA);
  VCLEAR(v1);
  asm volatile("vmulhsu.vv v1, v2, v3, v0.t");
  VCMP_I8(5, v1, 0, 0x0b, 0, 0xec, 0, 0x00, 0, 0xf8, 0, 0xd1, 0, 0x22, 0, 0x56,
          0, 0xf1);

  VSET(16, e16, m1);
  VLOAD_16(v2, 0x0f50, 0x47f9, 0xa4ca, 0xf94d, 0x720c, 0x444c, 0x3681, 0x96bd,
           0x5d37, 0xd64e, 0xe792, 0xdb64, 0xfaa6, 0xafe6, 0xf4e8, 0xe5ea);
  VLOAD_16(v3, 0x7784, 0xa42e, 0x499b, 0x0c01, 0x9d2b, 0x600d, 0x2bbd, 0xcb41,
           0xdda1, 0xb5d7, 0xafbc, 0xc74f, 0xab45, 0x986f, 0xf0f2, 0xcf3c);
  VLOAD_8(v0, 0xAA, 0xAA);
  VCLEAR(v1);
  asm volatile("vmulhsu.vv v1, v2, v3, v0.t");
  VCMP_I16(6, v1, 0, 0x2e28, 0, 0xffaf, 0, 0x199f, 0, 0xac6d, 0, 0xe262, 0,
           0xe37f, 0, 0xd04d, 0, 0xeae2);

  VSET(16, e32, m1);
  VLOAD_32(v2, 0xeded4bf3, 0xc9e27167, 0x4175509c, 0x80a3ae04, 0x9f1b2c07,
           0x87ea397b, 0x862e2800, 0x3cd09f37, 0x9a313d78, 0x596661ee,
           0x31f99717, 0x64e65802, 0xbd567027, 0xf7c459be, 0x57b6d9cd,
           0x94bc3eb4);
  VLOAD_32(v3, 0xa147b233, 0x19880f3d, 0x8dd8815e, 0xbc318dca, 0x2c436b94,
           0x29ba4191, 0x637f89b7, 0xe39d7818, 0xf48ff2d6, 0xb1dc7c7e,
           0xfa5da298, 0x5c1aae36, 0x83e04069, 0xecf36c08, 0x40d2e3a3,
           0xe7468a97);
  VLOAD_8(v0, 0xAA, 0xAA);
  VCLEAR(v1);
  asm volatile("vmulhsu.vv v1, v2, v3, v0.t");
  VCMP_I32(7, v1, 0, 0xfa9a5a26, 0, 0xa25f8c94, 0, 0xec6d24a0, 0, 0x361265a6, 0,
           0x3e1cc92b, 0, 0x244d4baf, 0, 0xf8612ea2, 0, 0x9f184dfb);
};

void TEST_CASE3(void) {
  VSET(16, e8, m1);
  VLOAD_8(v2, 0x21, 0x87, 0xa0, 0xa8, 0x6a, 0x6f, 0x6a, 0x6b, 0x74, 0x99, 0x37,
          0xa4, 0xdc, 0x4f, 0xc3, 0x55);
  uint64_t scalar = 5;
  asm volatile("vmulhsu.vx v1, v2, %[A]" ::[A] "r"(scalar));
  VCMP_I8(9, v1, 0x00, 0xfd, 0xfe, 0xfe, 0x02, 0x02, 0x02, 0x02, 0x02, 0xfd,
          0x01, 0xfe, 0xff, 0x01, 0xfe, 0x01);

  VSET(16, e16, m1);
  VLOAD_16(v2, 0x62b8, 0xc1e3, 0xb151, 0x08ce, 0x06c4, 0x1d2f, 0x7448, 0xfcd5,
           0x398c, 0xb933, 0x436d, 0x748f, 0x58d9, 0x1cd6, 0x86db, 0x20f2);
  scalar = 816;
  asm volatile("vmulhsu.vx v1, v2, %[A]" ::[A] "r"(scalar));
  VCMP_I16(10, v1, 0x013a, 0xff3a, 0xff05, 0x001c, 0x0015, 0x005d, 0x0172,
           0xfff5, 0x00b7, 0xff1e, 0x00d6, 0x0173, 0x011b, 0x005b, 0xfe7d,
           0x0069);

  VSET(16, e32, m1);
  VLOAD_32(v2, 0xa7cac3f7, 0xb3894e05, 0xbac8e70b, 0x05479577, 0x19d8bf63,
           0xb952c1ad, 0x9eaa74c0, 0x9e38d5c8, 0x51c77b3b, 0xa5f44521,
           0x65042faa, 0x8e7e5345, 0x76ae481c, 0x0ab27b6f, 0xa388cf2b,
           0x58218f7f);
  scalar = 7389998;
  asm volatile("vmulhsu.vx v1, v2, %[A]" ::[A] "r"(scalar));
  VCMP_I32(11, v1, 0xffd92575, 0xffde51c5, 0xffe1831f, 0x00025357, 0x000b6288,
           0xffe0de52, 0xffd5205d, 0xffd4ee51, 0x0024059f, 0xffd85637,
           0x002c7ed9, 0xffce00ba, 0x003446bb, 0x0004b63d, 0xffd7455b,
           0x0026d1e0);
};

void TEST_CASE4(void) {
  VSET(16, e8, m1);
  VLOAD_8(v2, 0x21, 0x87, 0xa0, 0xa8, 0x6a, 0x6f, 0x6a, 0x6b, 0x74, 0x99, 0x37,
          0xa4, 0xdc, 0x4f, 0xc3, 0x55);
  uint64_t scalar = 5;
  VLOAD_8(v0, 0xAA, 0xAA);
  VCLEAR(v1);
  asm volatile("vmulhsu.vx v1, v2, %[A], v0.t" ::[A] "r"(scalar));
  VCMP_I8(13, v1, 0, 0xfd, 0, 0xfe, 0, 0x02, 0, 0x02, 0, 0xfd, 0, 0xfe, 0, 0x01,
          0, 0x01);

  VSET(16, e16, m1);
  VLOAD_16(v2, 0x62b8, 0xc1e3, 0xb151, 0x08ce, 0x06c4, 0x1d2f, 0x7448, 0xfcd5,
           0x398c, 0xb933, 0x436d, 0x748f, 0x58d9, 0x1cd6, 0x86db, 0x20f2);
  scalar = 816;
  VLOAD_8(v0, 0xAA, 0xAA);
  VCLEAR(v1);
  asm volatile("vmulhsu.vx v1, v2, %[A], v0.t" ::[A] "r"(scalar));
  VCMP_I16(14, v1, 0, 0xff3a, 0, 0x001c, 0, 0x005d, 0, 0xfff5, 0, 0xff1e, 0,
           0x0173, 0, 0x005b, 0, 0x0069);

  VSET(16, e32, m1);
  VLOAD_32(v2, 0xa7cac3f7, 0xb3894e05, 0xbac8e70b, 0x05479577, 0x19d8bf63,
           0xb952c1ad, 0x9eaa74c0, 0x9e38d5c8, 0x51c77b3b, 0xa5f44521,
           0x65042faa, 0x8e7e5345, 0x76ae481c, 0x0ab27b6f, 0xa388cf2b,
           0x58218f7f);
  scalar = 7389998;
  VLOAD_8(v0, 0xAA, 0xAA);
  VCLEAR(v1);
  asm volatile("vmulhsu.vx v1, v2, %[A], v0.t" ::[A] "r"(scalar));
  VCMP_I32(15, v1, 0, 0xffde51c5, 0, 0x00025357, 0, 0xffe0de52, 0, 0xffd4ee51,
           0, 0xffd85637, 0, 0xffce00ba, 0, 0x0004b63d, 0, 0x0026d1e0);
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
