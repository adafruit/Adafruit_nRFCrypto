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

#include "Adafruit_nRFCrypto.h"

#include "nrf_cc310/include/crys_ecpki_domain.h"
#include "nrf_cc310/include/crys_ecpki_kg.h"

//--------------------------------------------------------------------+
// MACRO TYPEDEF CONSTANT ENUM DECLARATION
//--------------------------------------------------------------------+


//------------- IMPLEMENTATION -------------//
Adafruit_nRFCrypto_ECPKI::Adafruit_nRFCrypto_ECPKI(void)
{
  _domain = NULL;
}


bool Adafruit_nRFCrypto_ECPKI::begin(void)
{
  return true;
}

void Adafruit_nRFCrypto_ECPKI::end(void)
{
}

bool Adafruit_nRFCrypto_ECPKI::setDomain(CRYS_ECPKI_DomainID_t id)
{
  nRFCrypto.enable();

  _domain = CRYS_ECPKI_GetEcDomain(id);

  nRFCrypto.disable();
  return _domain != NULL;
}

bool Adafruit_nRFCrypto_ECPKI::genKeyPair(Adafruit_nRFCrypto_Random& rnd, CRYS_ECPKI_UserPrivKey_t* private_key, CRYS_ECPKI_UserPublKey_t* public_key)
{
  nRFCrypto.enable();

  CRYS_ECPKI_KG_TempData_t* tempbuf = (CRYS_ECPKI_KG_TempData_t*) rtos_malloc( sizeof(CRYS_ECPKI_KG_TempData_t) );

  uint32_t err = CRYS_ECPKI_GenKeyPair(rnd.getContext(), CRYS_RND_GenerateVector, _domain,
                                       private_key, public_key,
                                       tempbuf, NULL);

  nRFCrypto.disable();

  rtos_free(tempbuf);

  VERIFY_ERROR(err, false);
  return true;
}

