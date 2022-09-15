// Auto-generated file. Do not edit!
//   Template: src/f16-vbinary/vop-fp16arith.c.in
//   Generator: tools/xngen
//
// Copyright 2022 Google LLC
//
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree.

#include <assert.h>

#include <arm_fp16.h>

#include <xnnpack/common.h>
#include <xnnpack/vbinary.h>


void xnn_f16_vsqrdiff_ukernel__fp16arith_x1(
    size_t batch,
    const void* restrict input_a,
    const void* restrict input_b,
    void* restrict output,
    const union xnn_f16_default_params params[restrict XNN_MIN_ELEMENTS(1)])
{
  assert(batch != 0);
  assert(batch % sizeof(float16_t) == 0);
  assert(input_a != NULL);
  assert(input_b != NULL);
  assert(output != NULL);

  const float16_t* a = (const float16_t*) input_a;
  const float16_t* b = (const float16_t*) input_b;
  float16_t* o = (float16_t*) output;


  do {
    const float16_t va = *a++;
    const float16_t vb = *b++;
    float16_t vacc = vsubh_f16(va, vb);
    vacc = vmulh_f16(vacc, vacc);
    *o++ = vacc;
    batch -= sizeof(float16_t);
  } while (batch != 0);
}
