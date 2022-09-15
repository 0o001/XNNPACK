// Auto-generated file. Do not edit!
//   Template: src/f16-vbinary/vopc-f16c.c.in
//   Generator: tools/xngen
//
// Copyright 2022 Google LLC
//
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree.

#include <assert.h>

#include <immintrin.h>

#include <xnnpack/common.h>
#include <xnnpack/intrinsics-polyfill.h>
#include <xnnpack/vbinary.h>


void xnn_f16_vrdivc_minmax_ukernel__f16c_x8(
    size_t batch,
    const void* restrict input_a,
    const void* restrict input_b,
    void* restrict output,
    const union xnn_f16_minmax_params params[restrict XNN_MIN_ELEMENTS(1)]) XNN_OOB_READS
{
  assert(batch != 0);
  assert(batch % sizeof(uint16_t) == 0);
  assert(input_a != NULL);
  assert(input_b != NULL);
  assert(output != NULL);

  const uint16_t* a = (const uint16_t*) input_a;
  const uint16_t* b = (const uint16_t*) input_b;
  uint16_t* o = (uint16_t*) output;

  const __m256 vy_min = _mm256_load_ps(params->avx.min);
  const __m256 vy_max = _mm256_load_ps(params->avx.max);

  const __m256 vb = _mm256_cvtph_ps(_mm_set1_epi16((short) *b));
  for (; batch >= 8 * sizeof(uint16_t); batch -= 8 * sizeof(uint16_t)) {
    const __m256 va = _mm256_cvtph_ps(_mm_loadu_si128((const __m128i*) a));
    a += 8;

    __m256 vy = _mm256_cvtph_ps(_mm256_cvtps_ph(_mm256_div_ps(vb, va), _MM_FROUND_NO_EXC));

    vy = _mm256_max_ps(vy, vy_min);
    vy = _mm256_min_ps(vy, vy_max);

    _mm_storeu_si128((__m128i*) o, _mm256_cvtps_ph(vy, _MM_FROUND_NO_EXC));
    o += 8;
  }
  if XNN_UNLIKELY(batch != 0) {
    const __m256 va = _mm256_cvtph_ps(_mm_loadu_si128((const __m128i*) a));

    __m256 vy = _mm256_cvtph_ps(_mm256_cvtps_ph(_mm256_div_ps(vb, va), _MM_FROUND_NO_EXC));

    vy = _mm256_max_ps(vy, vy_min);
    vy = _mm256_min_ps(vy, vy_max);

    __m128i vh = _mm256_cvtps_ph(vy, _MM_FROUND_NO_EXC);
    if (batch & (4 * sizeof(uint16_t))) {
      _mm_storel_epi64((__m128i*) o, vh);
      vh = _mm_unpackhi_epi64(vh, vh);
      o += 4;
    }
    if (batch & (2 * sizeof(uint16_t))) {
      _mm_storeu_si32(o, vh);
      vh = _mm_srli_epi64(vh, 32);
      o += 2;
    }
    if (batch & (1 * sizeof(uint16_t))) {
      *o = (uint16_t) _mm_extract_epi16(vh, 0);
    }
  }
}
