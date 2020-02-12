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

#ifndef ADAFRUIT_NRFCRYPTO_ECPKI_H_
#define ADAFRUIT_NRFCRYPTO_ECPKI_H_

#include "nrf_cc310/include/crys_ecpki_types.h"

class Adafruit_nRFCrypto_ECPKI
{
  public:
    Adafruit_nRFCrypto_ECPKI(void);

    bool begin(void);
    void end(void);

    bool setDomain(CRYS_ECPKI_DomainID_t id);

    bool genKeyPair(Adafruit_nRFCrypto_Random& rnd, CRYS_ECPKI_UserPrivKey_t* private_key, CRYS_ECPKI_UserPublKey_t* public_key);

  private:
    const CRYS_ECPKI_Domain_t * _domain;
//    CRYS_RND_State_t _state;
};

#endif /* ADAFRUIT_NRFCRYPTO_ECPKI_H_ */
