// Auto-generated file. Do not edit!
//   Template: src/qs8-gemm/scalar.c.in
//   Generator: tools/xngen
//
// Copyright 2021 Google LLC
//
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree.

#include <assert.h>

#include <xnnpack/gemm.h>
#include <xnnpack/math.h>


void xnn_qd8_f32_qc8w_gemm_minmax_ukernel_4x4__wasm(
    size_t mr,
    size_t nc,
    size_t kc,
    const int8_t* restrict a,
    size_t a_stride,
    const void* restrict w,
    float* restrict c,
    size_t cm_stride,
    size_t cn_stride,
    const union xnn_f32_minmax_params params[restrict XNN_MIN_ELEMENTS(1)],
    const struct xnn_qd8_quantization_params quantization_params[restrict XNN_MIN_ELEMENTS(1)])
{
  assert(mr != 0);
  assert(mr <= 4);
  assert(nc != 0);
  assert(kc != 0);

  const int8_t* a0 = a;
  float* c0 = c;
  const int8_t* a1 = (const int8_t*) ((uintptr_t) a0 + a_stride);
  float* c1 = (float*) ((uintptr_t) c0 + cm_stride);
  if XNN_UNPREDICTABLE(mr < 2) {
    a1 = a0;
    c1 = c0;
  }
  const int8_t* a2 = (const int8_t*) ((uintptr_t) a1 + a_stride);
  float* c2 = (float*) ((uintptr_t) c1 + cm_stride);
  if XNN_UNPREDICTABLE(mr <= 2) {
    a2 = a1;
    c2 = c1;
  }
  const int8_t* a3 = (const int8_t*) ((uintptr_t) a2 + a_stride);
  float* c3 = (float*) ((uintptr_t) c2 + cm_stride);
  if XNN_UNPREDICTABLE(mr != 4) {
    a3 = a2;
    c3 = c2;
  }

  do {
    const int32_t vksum0 = ((const int32_t*) w)[0];
    const int32_t vksum1 = ((const int32_t*) w)[1];
    const int32_t vksum2 = ((const int32_t*) w)[2];
    const int32_t vksum3 = ((const int32_t*) w)[3];
    const int32_t vinput_zero_point0 = quantization_params[0].zero_point;
    int32_t vacc0x0 = vksum0 * vinput_zero_point0;
    int32_t vacc0x1 = vksum1 * vinput_zero_point0;
    int32_t vacc0x2 = vksum2 * vinput_zero_point0;
    int32_t vacc0x3 = vksum3 * vinput_zero_point0;
    const int32_t vinput_zero_point1 = quantization_params[1].zero_point;
    int32_t vacc1x0 = vksum0 * vinput_zero_point1;
    int32_t vacc1x1 = vksum1 * vinput_zero_point1;
    int32_t vacc1x2 = vksum2 * vinput_zero_point1;
    int32_t vacc1x3 = vksum3 * vinput_zero_point1;
    const int32_t vinput_zero_point2 = quantization_params[2].zero_point;
    int32_t vacc2x0 = vksum0 * vinput_zero_point2;
    int32_t vacc2x1 = vksum1 * vinput_zero_point2;
    int32_t vacc2x2 = vksum2 * vinput_zero_point2;
    int32_t vacc2x3 = vksum3 * vinput_zero_point2;
    const int32_t vinput_zero_point3 = quantization_params[3].zero_point;
    int32_t vacc3x0 = vksum0 * vinput_zero_point3;
    int32_t vacc3x1 = vksum1 * vinput_zero_point3;
    int32_t vacc3x2 = vksum2 * vinput_zero_point3;
    int32_t vacc3x3 = vksum3 * vinput_zero_point3;
    w = (const int32_t*) w + 4;

    size_t k = kc;
    do {
      const int32_t va0 = (int32_t) *a0++;
      const int32_t va1 = (int32_t) *a1++;
      const int32_t va2 = (int32_t) *a2++;
      const int32_t va3 = (int32_t) *a3++;

      const int32_t vb0 = (int32_t) ((const int8_t*) w)[0];
      const int32_t vb1 = (int32_t) ((const int8_t*) w)[1];
      const int32_t vb2 = (int32_t) ((const int8_t*) w)[2];
      const int32_t vb3 = (int32_t) ((const int8_t*) w)[3];
      w = (const int8_t*) w + 4;

      vacc0x0 += va0 * vb0;
      vacc0x1 += va0 * vb1;
      vacc0x2 += va0 * vb2;
      vacc0x3 += va0 * vb3;
      vacc1x0 += va1 * vb0;
      vacc1x1 += va1 * vb1;
      vacc1x2 += va1 * vb2;
      vacc1x3 += va1 * vb3;
      vacc2x0 += va2 * vb0;
      vacc2x1 += va2 * vb1;
      vacc2x2 += va2 * vb2;
      vacc2x3 += va2 * vb3;
      vacc3x0 += va3 * vb0;
      vacc3x1 += va3 * vb1;
      vacc3x2 += va3 * vb2;
      vacc3x3 += va3 * vb3;

      k -= sizeof(int8_t);
    } while (k != 0);

    const float vascale0 = quantization_params[0].inv_scale;
    float vout0x0 = (float) vacc0x0 * vascale0;
    float vout0x1 = (float) vacc0x1 * vascale0;
    float vout0x2 = (float) vacc0x2 * vascale0;
    float vout0x3 = (float) vacc0x3 * vascale0;
    const float vascale1 = quantization_params[1].inv_scale;
    float vout1x0 = (float) vacc1x0 * vascale1;
    float vout1x1 = (float) vacc1x1 * vascale1;
    float vout1x2 = (float) vacc1x2 * vascale1;
    float vout1x3 = (float) vacc1x3 * vascale1;
    const float vascale2 = quantization_params[2].inv_scale;
    float vout2x0 = (float) vacc2x0 * vascale2;
    float vout2x1 = (float) vacc2x1 * vascale2;
    float vout2x2 = (float) vacc2x2 * vascale2;
    float vout2x3 = (float) vacc2x3 * vascale2;
    const float vascale3 = quantization_params[3].inv_scale;
    float vout3x0 = (float) vacc3x0 * vascale3;
    float vout3x1 = (float) vacc3x1 * vascale3;
    float vout3x2 = (float) vacc3x2 * vascale3;
    float vout3x3 = (float) vacc3x3 * vascale3;

    const float vbscale0 = ((const float*) w)[0];
    const float vbscale1 = ((const float*) w)[1];
    const float vbscale2 = ((const float*) w)[2];
    const float vbscale3 = ((const float*) w)[3];
    const float vbias0 = ((const float*) w)[4];
    vout0x0 = math_muladd_f32(vout0x0, vbscale0, vbias0);
    const float vbias1 = ((const float*) w)[5];
    vout0x1 = math_muladd_f32(vout0x1, vbscale1, vbias1);
    const float vbias2 = ((const float*) w)[6];
    vout0x2 = math_muladd_f32(vout0x2, vbscale2, vbias2);
    const float vbias3 = ((const float*) w)[7];
    vout0x3 = math_muladd_f32(vout0x3, vbscale3, vbias3);
    vout1x0 = math_muladd_f32(vout1x0, vbscale0, vbias0);
    vout1x1 = math_muladd_f32(vout1x1, vbscale1, vbias1);
    vout1x2 = math_muladd_f32(vout1x2, vbscale2, vbias2);
    vout1x3 = math_muladd_f32(vout1x3, vbscale3, vbias3);
    vout2x0 = math_muladd_f32(vout2x0, vbscale0, vbias0);
    vout2x1 = math_muladd_f32(vout2x1, vbscale1, vbias1);
    vout2x2 = math_muladd_f32(vout2x2, vbscale2, vbias2);
    vout2x3 = math_muladd_f32(vout2x3, vbscale3, vbias3);
    vout3x0 = math_muladd_f32(vout3x0, vbscale0, vbias0);
    vout3x1 = math_muladd_f32(vout3x1, vbscale1, vbias1);
    vout3x2 = math_muladd_f32(vout3x2, vbscale2, vbias2);
    vout3x3 = math_muladd_f32(vout3x3, vbscale3, vbias3);

    w = (const float*) w + 8;

    const float voutput_min = params->scalar.min;
    vout0x0 = __builtin_wasm_max_f32(vout0x0, voutput_min);
    vout1x0 = __builtin_wasm_max_f32(vout1x0, voutput_min);
    vout2x0 = __builtin_wasm_max_f32(vout2x0, voutput_min);
    vout3x0 = __builtin_wasm_max_f32(vout3x0, voutput_min);
    vout0x1 = __builtin_wasm_max_f32(vout0x1, voutput_min);
    vout1x1 = __builtin_wasm_max_f32(vout1x1, voutput_min);
    vout2x1 = __builtin_wasm_max_f32(vout2x1, voutput_min);
    vout3x1 = __builtin_wasm_max_f32(vout3x1, voutput_min);
    vout0x2 = __builtin_wasm_max_f32(vout0x2, voutput_min);
    vout1x2 = __builtin_wasm_max_f32(vout1x2, voutput_min);
    vout2x2 = __builtin_wasm_max_f32(vout2x2, voutput_min);
    vout3x2 = __builtin_wasm_max_f32(vout3x2, voutput_min);
    vout0x3 = __builtin_wasm_max_f32(vout0x3, voutput_min);
    vout1x3 = __builtin_wasm_max_f32(vout1x3, voutput_min);
    vout2x3 = __builtin_wasm_max_f32(vout2x3, voutput_min);
    vout3x3 = __builtin_wasm_max_f32(vout3x3, voutput_min);

    const float voutput_max = params->scalar.max;
    vout0x0 = __builtin_wasm_min_f32(vout0x0, voutput_max);
    vout1x0 = __builtin_wasm_min_f32(vout1x0, voutput_max);
    vout2x0 = __builtin_wasm_min_f32(vout2x0, voutput_max);
    vout3x0 = __builtin_wasm_min_f32(vout3x0, voutput_max);
    vout0x1 = __builtin_wasm_min_f32(vout0x1, voutput_max);
    vout1x1 = __builtin_wasm_min_f32(vout1x1, voutput_max);
    vout2x1 = __builtin_wasm_min_f32(vout2x1, voutput_max);
    vout3x1 = __builtin_wasm_min_f32(vout3x1, voutput_max);
    vout0x2 = __builtin_wasm_min_f32(vout0x2, voutput_max);
    vout1x2 = __builtin_wasm_min_f32(vout1x2, voutput_max);
    vout2x2 = __builtin_wasm_min_f32(vout2x2, voutput_max);
    vout3x2 = __builtin_wasm_min_f32(vout3x2, voutput_max);
    vout0x3 = __builtin_wasm_min_f32(vout0x3, voutput_max);
    vout1x3 = __builtin_wasm_min_f32(vout1x3, voutput_max);
    vout2x3 = __builtin_wasm_min_f32(vout2x3, voutput_max);
    vout3x3 = __builtin_wasm_min_f32(vout3x3, voutput_max);

    if XNN_LIKELY(nc >= 4) {
      c3[0] = vout3x0;
      c3[1] = vout3x1;
      c3[2] = vout3x2;
      c3[3] = vout3x3;
      c2[0] = vout2x0;
      c2[1] = vout2x1;
      c2[2] = vout2x2;
      c2[3] = vout2x3;
      c1[0] = vout1x0;
      c1[1] = vout1x1;
      c1[2] = vout1x2;
      c1[3] = vout1x3;
      c0[0] = vout0x0;
      c0[1] = vout0x1;
      c0[2] = vout0x2;
      c0[3] = vout0x3;

      a0 = (const int8_t*) ((uintptr_t) a0 - kc);
      a1 = (const int8_t*) ((uintptr_t) a1 - kc);
      a2 = (const int8_t*) ((uintptr_t) a2 - kc);
      a3 = (const int8_t*) ((uintptr_t) a3 - kc);

      c0 = (float*) ((uintptr_t) c0 + cn_stride);
      c1 = (float*) ((uintptr_t) c1 + cn_stride);
      c2 = (float*) ((uintptr_t) c2 + cn_stride);
      c3 = (float*) ((uintptr_t) c3 + cn_stride);

      nc -= 4;
    } else {
      if (nc & 2) {
        c3[0] = vout3x0;
        c3[1] = vout3x1;
        vout3x0 = vout3x2;
        c3 += 2;
        c2[0] = vout2x0;
        c2[1] = vout2x1;
        vout2x0 = vout2x2;
        c2 += 2;
        c1[0] = vout1x0;
        c1[1] = vout1x1;
        vout1x0 = vout1x2;
        c1 += 2;
        c0[0] = vout0x0;
        c0[1] = vout0x1;
        vout0x0 = vout0x2;
        c0 += 2;
      }
      if (nc & 1) {
        c3[0] = vout3x0;
        c2[0] = vout2x0;
        c1[0] = vout1x0;
        c0[0] = vout0x0;
      }

      nc = 0;
    }
  } while (nc != 0);
}