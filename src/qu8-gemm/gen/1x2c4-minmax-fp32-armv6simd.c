// Auto-generated file. Do not edit!
//   Template: src/qs8-gemm/c4-armv6simd.c.in
//   Generator: tools/xngen
//
// Copyright 2022 Google LLC
//
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree.

#include <assert.h>
#include <fp16.h>

#include <arm_acle.h>

#include <xnnpack/intrinsics-polyfill.h>
#include <xnnpack/math.h>
#include <xnnpack/gemm.h>
#include <xnnpack/unaligned.h>


void xnn_qu8_gemm_minmax_fp32_ukernel_1x2c4__armv6simd(
    size_t mr,
    size_t nc,
    size_t kc,
    const uint8_t* restrict a,
    size_t a_stride,
    const void* restrict w,
    uint8_t* restrict c,
    size_t cm_stride,
    size_t cn_stride,
    const union xnn_qu8_conv_minmax_params params[restrict XNN_MIN_ELEMENTS(1)])
{
  assert(mr != 0);
  assert(mr <= 1);
  assert(nc != 0);
  assert(kc != 0);

  kc = round_up_po2(kc, 4 * sizeof(int8_t));
  const uint8_t* a0 = a;
  uint8_t* c0 = c;

  const int16x2_t vb_minus_zero_point = (int16x2_t) params->fp32_armv6simd.minus_kernel_zero_point;
  const float vscale = params->fp32_armv6simd.scale;
  const float vmagic_bias = params->fp32_armv6simd.magic_bias;
  do {
    int32_t vacc0x0 = ((const int32_t*) w)[0];
    int32_t vacc0x1 = ((const int32_t*) w)[1];
    w = (const void*) ((const int32_t*) w + 2);

    size_t k = kc;
    do {
      const int8x4_t va0 = (int8x4_t) unaligned_load_s32(a0); a0 += 4;

      const int16x2_t va0c02 = __uxtb16(va0);
      const int16x2_t va0c13 = __uxtb16(__ror(va0, 8));

      const int8x4_t vb0 = *((const int8x4_t*) w); w = (const int8_t*) w + 4;
      const int16x2_t vb0c02 = __uxtab16(vb_minus_zero_point, vb0);

      vacc0x0 = __smlad(va0c02, vb0c02, vacc0x0);

      const int16x2_t vb0c13 = __uxtab16(vb_minus_zero_point, __ror(vb0, 8));
      vacc0x0 = __smlad(va0c13, vb0c13, vacc0x0);
      const int8x4_t vb1 = *((const int8x4_t*) w); w = (const int8_t*) w + 4;
      const int16x2_t vb1c02 = __uxtab16(vb_minus_zero_point, vb1);

      vacc0x1 = __smlad(va0c02, vb1c02, vacc0x1);

      const int16x2_t vb1c13 = __uxtab16(vb_minus_zero_point, __ror(vb1, 8));
      vacc0x1 = __smlad(va0c13, vb1c13, vacc0x1);

      k -= 4 * sizeof(uint8_t);
    } while (k != 0);

    float vfpacc0x0 = (float) vacc0x0;
    float vfpacc0x1 = (float) vacc0x1;

    vfpacc0x0 *= vscale;
    vfpacc0x1 *= vscale;

    vfpacc0x0 += vmagic_bias;
    vfpacc0x1 += vmagic_bias;

    int32_t vout0x0 = (int32_t) fp32_to_bits(vfpacc0x0);
    int32_t vout0x1 = (int32_t) fp32_to_bits(vfpacc0x1);

    const int32_t vmagic_bias_less_zero_point = params->fp32_armv6simd.magic_bias_less_zero_point;
    vout0x0 = __qsub(vout0x0, vmagic_bias_less_zero_point);
    vout0x1 = __qsub(vout0x1, vmagic_bias_less_zero_point);

    vout0x0 = __usat(vout0x0, 8);
    vout0x1 = __usat(vout0x1, 8);

    const uint32_t vout0 = (uint32_t) (uint8_t) vout0x0 | ((uint32_t) vout0x1 << 8);

    uint32_t vout = vout0;

    const int8x4_t voutput_min = (int8x4_t) params->fp32_armv6simd.output_min;
    __usub8((int8x4_t) vout, voutput_min);
    vout = (uint32_t) __sel((uint8x4_t) vout, (uint8x4_t) voutput_min);

    const int8x4_t voutput_max = (int8x4_t) params->fp32_armv6simd.output_max;
    __usub8((int8x4_t) vout, voutput_max);
    vout = (uint32_t) __sel((uint8x4_t) voutput_max, (uint8x4_t) vout);

    if XNN_LIKELY(nc >= 2) {
      unaligned_store_u16(c0, (uint16_t) vout);

      a0 = (const uint8_t*) ((uintptr_t) a0 - kc);

      c0 = (uint8_t*) ((uintptr_t) c0 + cn_stride);

      nc -= 2;
    } else {
      *c0 = (uint8_t) vout;

      nc = 0;
    }
  } while (nc != 0);
}