/*
 * Copyright (c) Clinton Freeman 2019
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
 * associated documentation files (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge, publish, distribute,
 * sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or
 * substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT
 * NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
#ifndef _LIGHTING_ACH_
#define _LIGHTING_ACH_

#include <Arduino.h>
#include <APA102.h>

const uint16_t ledCount = 45;

typedef struct {
  uint8_t intensity;
  unsigned long t;
} Keyframe_struct;

typedef struct {
  Keyframe_struct rStart;
  Keyframe_struct rEnd;
  Keyframe_struct gStart;
  Keyframe_struct gEnd;
  Keyframe_struct bStart;
  Keyframe_struct bEnd;
} APA102_struct;

int AnimatePulse(const Keyframe_struct *start,
                 const Keyframe_struct *end,
                 unsigned long current_time);

void Off(APA102_struct *colors, unsigned long current_time);

void UpdateGlitter(APA102_struct *colors, unsigned long current_time);

#endif
