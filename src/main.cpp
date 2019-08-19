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

#include <Arduino.h>

#include "lighting.h"

// Setup the LED strip.
APA102<13, 14> ledStrip;
APA102_struct strip[ledCount];

// setup configures the underlying hardware for use in the main loop.
void setup() {
  Serial.begin(9600);
  Off(strip, millis());
}

// loop executes over and over on the microcontroller. Reads messages from OSC
// and updates LED array accordingly.
void loop() {
  unsigned long t = millis();
  UpdateGlitter(strip, t);

  rgb_color colors[ledCount];
  for (uint16_t i = 0; i < ledCount; i++) {
    colors[i] = (rgb_color){(uint8_t)AnimatePulse(&strip[i].rStart, &strip[i].rEnd, t),
                            (uint8_t)AnimatePulse(&strip[i].gStart, &strip[i].gEnd, t),
                            (uint8_t)AnimatePulse(&strip[i].bStart, &strip[i].bEnd, t)};
  }
  ledStrip.write(colors, ledCount, 31);
}
