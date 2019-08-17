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
#include "lighting.h"

uint8_t LERP(uint8_t left, uint8_t right, float ratio) {
  if (ratio > 1.0) {
    return right;
  }

  if (ratio < 0.0) {
    return left;
  }

  if (left < right) {
    return left + ((right - left) * ratio);
  } else {
    return left - ((left - right) * ratio);
  }
}

int AnimatePulse(const Keyframe_struct *start,
                 const Keyframe_struct *end,
                 unsigned long current_time) {
  // Normalise dt.
  float delta_t = (current_time - start->t) / (float) (end->t - start->t);

  // Determine current brightness.
  return LERP(start->intensity, end->intensity, delta_t);
}

void Off(APA102_struct *colors, unsigned long current_time) {
  for (uint16_t i = 0; i < ledCount; i++) {
    colors[i] = APA102_struct{Keyframe_struct{0, current_time},
                              Keyframe_struct{0, current_time},
                              Keyframe_struct{0, current_time},
                              Keyframe_struct{0, current_time},
                              Keyframe_struct{0, current_time},
                              Keyframe_struct{0, current_time}};
  }
}

void UpdateGlitter(APA102_struct *colors, unsigned long current_time) {
  for (uint16_t i = 0; i < ledCount; i++) {
    if (current_time >= colors[i].rEnd.t && (random(0, 100) / 100.0) > 0.95) {
      uint8_t r = LERP(159, 222, (random(0, 100) / 100.0));
      uint8_t g = LERP(161, 245, (random(0, 100) / 100.0));
      uint8_t b = LERP(221, 213, (random(0, 100) / 100.0));

      unsigned long et = current_time + random(0, 300);

      colors[i] = APA102_struct{Keyframe_struct{r, et},
                                Keyframe_struct{0, et + 100},
                                Keyframe_struct{g, et},
                                Keyframe_struct{0, et + 100},
                                Keyframe_struct{b, et},
                                Keyframe_struct{0, et + 100}};
    }
  }
}