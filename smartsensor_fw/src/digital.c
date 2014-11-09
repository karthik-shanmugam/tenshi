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
  if (counter == 0) {
    DIGITAL_SET(IN1, 1);
    TCCR1A = (1 << COM1A1) | (1 << COM1A0);
    OCR1A = 0xAFFF;
    counter++;
  } else if (counter == 1) {
    TCCR1A = 0;
    DIGITAL_SET(IN1, 0);
    counter++;
  } else if (counter == 20) {
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
  TCCR1A = 0;
  TCCR1B = (1 << CS10);
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

