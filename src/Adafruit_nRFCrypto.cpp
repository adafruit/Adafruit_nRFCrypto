/* 
 * The MIT License (MIT)
 *
 * Copyright (c) 2020 Ha Thach (tinyusb.org) for Adafruit Industries
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "variant.h"
#include "common_inc.h"
#include "Adafruit_nRFCrypto.h"

// Only nRF52840 has CC310
#ifndef NRF_CRYPTOCELL
  #error CryptoCell CC310 is not supported on this board
#endif

//--------------------------------------------------------------------+
// MACRO TYPEDEF CONSTANT ENUM DECLARATION
//--------------------------------------------------------------------+

Adafruit_nRFCrypto nRFCrypto;

//------------- IMPLEMENTATION -------------//

Adafruit_nRFCrypto::Adafruit_nRFCrypto(void)
{

}

bool Adafruit_nRFCrypto::begin(void)
{
  NVIC_SetPriority(CRYPTOCELL_IRQn, 2);
  NVIC_EnableIRQ(CRYPTOCELL_IRQn);

  enable();

  VERIFY_ERROR(SaSi_LibInit(), false);

  disable();

  return true;
}

void Adafruit_nRFCrypto::end(void)
{
  enable();

  SaSi_LibFini();
//  CRYS_RND_UnInstantiation()

  NVIC_DisableIRQ(CRYPTOCELL_IRQn);

  disable();
}

void Adafruit_nRFCrypto::enable(void)
{
  NRF_CRYPTOCELL->ENABLE = 1;
}

void Adafruit_nRFCrypto::disable(void)
{
  NRF_CRYPTOCELL->ENABLE = 0;
}
