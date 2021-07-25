/*
 *    This file is part of darktable,
 *    Copyright (C) 2021 darktable developers.
 *
 *    darktable is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    darktable is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with darktable.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

// When included by a C++ file, restrict qualifiers are not allowed
#ifdef __cplusplus
#define DT_RESTRICT
#else
#define DT_RESTRICT restrict
#endif

/* Helper to force heap vectors to be aligned on 64 bits blocks to enable AVX2 */
#define DT_ALIGNED_ARRAY __attribute__((aligned(64)))
#define DT_ALIGNED_PIXEL __attribute__((aligned(16)))

// utility type to ease declaration of aligned small arrays to hold a pixel (and document their purpose)
typedef DT_ALIGNED_PIXEL float dt_aligned_pixel_t[4];

// a 3x3 matrix, padded to permit SSE instructions to be used for multiplication and addition
typedef float DT_ALIGNED_ARRAY dt_colormatrix_t[4][4];

// convert a 3x3 matrix into the padded format optimized for vectorization
static inline void repack_3x3_to_3xSSE(const float input[9], dt_colormatrix_t output)
{
  output[0][0] = input[0];
  output[0][1] = input[1];
  output[0][2] = input[2];
  output[0][3] = 0.0f;

  output[1][0] = input[3];
  output[1][1] = input[4];
  output[1][2] = input[5];
  output[1][3] = 0.0f;

  output[2][0] = input[6];
  output[2][1] = input[7];
  output[2][2] = input[8];
  output[2][3] = 0.0f;

  for(size_t c = 0; c < 4; c++)
    output[3][c] = 0.0f;
}

// convert a 3x3 matrix into the padded format optimized for vectorization
static inline void repack_double3x3_to_3xSSE(const double input[9], dt_colormatrix_t output)
{
  output[0][0] = input[0];
  output[0][1] = input[1];
  output[0][2] = input[2];
  output[0][3] = 0.0f;

  output[1][0] = input[3];
  output[1][1] = input[4];
  output[1][2] = input[5];
  output[1][3] = 0.0f;

  output[2][0] = input[6];
  output[2][1] = input[7];
  output[2][2] = input[8];
  output[2][3] = 0.0f;

  for(size_t c = 0; c < 4; c++)
    output[3][c] = 0.0f;
}

// modelines: These editor modelines have been set for all relevant files by tools/update_modelines.sh
// vim: shiftwidth=2 expandtab tabstop=2 cindent
// kate: tab-indents: off; indent-width 2; replace-tabs on; indent-mode cstyle; remove-trailing-spaces modified;
