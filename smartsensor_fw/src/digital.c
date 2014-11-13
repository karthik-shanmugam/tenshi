// Licensed to Pioneers in Engineering under one
// or more contributor license agreements.  See the NOTICE file
// distributed with this work for additional information
// regarding copyright ownership.  Pioneers in Engineering licenses
// this file to you under the Apache License, Version 2.0 (the
// "License"); you may not use this file except in compliance
//  with the License.  You may obtain a copy of the License at
//
//    http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing,
// software distributed under the License is distributed on an
// "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied.  See the License for the
// specific language governing permissions and limitations
// under the License

// This file has digital io smart sensor related functions

#include "inc/digital.h"
#include <avr/io.h>
#include <avr/interrupt.h>

// Private global variables
// Private helper functions


// Public functions called from main.c

ISR(TIMER1_OVF_vect) {
  static unsigned char counter = 0;
  static unsigned char previousH = 0x0F;
  static unsigned char previousL = 0xA0;
  static unsigned char direction = 1;
  static unsigned char slower = 0;
  if (counter == 0) {
    // DIGITAL_SET(IN1, 1);
    TCCR1A = (1 << COM1A1) | (1 << COM1A0) | (1 << COM1B1) | (1<< COM1B0);
    TCCR1B = (1 << CS10) | (1 << WGM13);
    slower++;
    if (slower % 10 == 0) {
      previousL == previousL + direction;
    }
    if (previousL == 0) {
      previousH = previousH + direction;
    }
    if (previousL == 0x40 && previousH == 0x1F) {
      direction = -1;
    }
    if (previousL == 0xA0 && previousH == 0x0F) {
      direction = 1;
    }
    OCR1AH = previousH;
    OCR1AL = previousL;
    OCR1BH = 0x0F;
    OCR1BL = 0xA0;
    counter++;
  } else if (counter == 1) {
    // TCCR1A = 0;
    // DIGITAL_SET(IN1, 1);
    TCCR1A = (1 << WGM11);
    TCCR1B = (1 << CS10) | (1 << WGM12) | (1 << WGM13);
    counter++;
  } else if (counter == 19) {
    // DIGITAL_TOGGLE(IN3);
    counter = 0;
  } else {
    counter++;
  }
}
// Public functions called from main.c
void initDigital() {
  // 0.01639344262 is cycle length
  // 0x10 is 1 ms
  // 0x19 is 1.5 ms
  // 0x1F is 2 ms
  DIGITAL_SET_OUT(IN1);
  DIGITAL_SET_OUT(IN3);
  TCCR1A = 0;
  TCCR1B = (1 << CS10) | (1 << WGM13);
  ICR1H = 0x1F;
  ICR1L = 0x40;
  TIMSK = (1 << TOIE1);
  sei();


  // DIGITAL_PULLUP_ON(IN0);
  // DIGITAL_SET_LOW(IN1);
  // DIGITAL_SET_LOW(IN2);
  // DIGITAL_SET_LOW(IN3);

  // TODO(tobinsarah): allow configuration as input/output for each relevant pin
  // DIGITAL_SET_IN(IN0);
  // DIGITAL_SET_OUT(IN1);
  // DIGITAL_SET_OUT(IN2);
  // DIGITAL_SET_OUT(IN3);
}
void activeDigitalRec(uint8_t *data, uint8_t len, uint8_t inband) {
  *data = 0;
}
void activeDigitalSend(uint8_t *outData, uint8_t *outLen, uint8_t *inband) {
  *outLen = 0;
}

