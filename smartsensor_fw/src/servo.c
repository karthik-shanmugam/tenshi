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

// This file has battery buzzer related functions

#include "inc/servo.h"
#include <avr/io.h>
// Private global variables
void setRegister0A(uint8_t data);
void setRegister0B(uint8_t data);
void setRegister1A(uint8_t data);
void setRegister1B(uint8_t data);

// Private helper functions
int adc_read(void);

// Public functions called from main.c
void initServo() {
  // Does everything to set up the analog stuffs.
  // Turn on pin PC1 (which maps to IN0)
  // ADMUX |= (1 << MUX3) | (1 << MUX1);
  // Enable the ADC and set the division factor between
  // the system clock frequency and the input clock to the ADC.
  // ADCSRA |= (1 << ADPS1) | (1 << ADPS0) | (1 << ADEN);

  // set register to pwm mode
  // TCCR0B = (1 << CS01) | (1 << WGM02);
  // DIGITAL_SET_OUT(PIN_DEFINITION(C, 0));
  // DIGITAL_SET_OUT(PIN_DEFINITION(A, 5));
  // TCCR0A = (1 << WGM00);
  // TCCR0A |= (1 << COM0A1) | (1 << COM0B1);
  // OCR0A = 0x7F;
  // OCR0B = 0x3F;


  // DIGITAL_SET_OUT(PIN_DEFINITION(B, 3));
  OCR1BL = 0x7F;
  DIGITAL_SET_OUT(PIN_DEFINITION(A, 6));
  TCCR1A = (1 << COM1B1) | (1 << WGM10);
  TCCR1B = (1 << WGM12) | (1 << CS11) | (1 << CS10);

  // Enable Timer/Counter1 Overflow Interrupt
  TIMSK = (1 << TOIE1);
}

void activeServoRec(uint8_t *data, uint8_t len, uint8_t inband) {
}
void activeServoSend(uint8_t *outData, uint8_t *outLen, uint8_t *inband) {
  // TODO(cduck): Write this function
}



// Private helper functions
void setRegister0A(uint8_t data) {
  OCR0A = data;
}
void setRegister0B(uint8_t data) {
  OCR0B = data;
}
void setRegister1A(uint8_t data) {
  OCR1A = data;
}
void setRegister1B(uint8_t data) {
  OCR1B = data;
}
// Taken from http://www.adnbr.co.uk/articles/adc-and-pwm-basics
// by Sumita because I can't code.
// It's for the ATtiny13, though.
/*int adc_read(void) {
    // I actually use this one. It's the analog in version of DIGITAL_READ.
    // Start the conversion
    ADCSRA |= (1 << ADSC);

    // Wait for it to finish
    while (ADCSRA & (1 << ADSC)) {}

    return ADC;  // For 10-bit resolution
}*/
