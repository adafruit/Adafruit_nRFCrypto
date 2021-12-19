/*
   The MIT License (MIT)

   Copyright (c) 2021 Kongduino

   Permission is hereby granted, free of charge, to any person obtaining a copy
   of this software and associated documentation files (the "Software"), to deal
   in the Software without restriction, including without limitation the rights
   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
   copies of the Software, and to permit persons to whom the Software is
   furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in
   all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
   THE SOFTWARE.
*/

#ifndef NRFCRYPTO_AES_H_
#define NRFCRYPTO_AES_H_

#include "nrf_cc310/include/ssi_aes.h"
#include "nrf_cc310/include/sns_silib.h"

class nRFCrypto_AES {
  public:
    nRFCrypto_AES(void);
    bool begin(void);
    void end(void);
    int Process(char *msg, uint8_t msgLen, uint8_t *IV, uint8_t *pKey, uint8_t pKeyLen,
                   char *retBuf, SaSiAesEncryptMode_t modeFlag, SaSiAesOperationMode_t opMode);
    SaSiAesEncryptMode_t encryptFlag = (SaSiAesEncryptMode_t) 0; // SASI_AES_ENCRYPT
    SaSiAesEncryptMode_t decryptFlag = (SaSiAesEncryptMode_t) 1; // SASI_AES_DECRYPT
    SaSiAesOperationMode_t ecbMode = (SaSiAesOperationMode_t) 0; // SASI_AES_MODE_ECB
    SaSiAesOperationMode_t cbcMode = (SaSiAesOperationMode_t) 1; // SASI_AES_MODE_CBC
    SaSiAesOperationMode_t ctrMode = (SaSiAesOperationMode_t) 3; // SASI_AES_MODE_CTR
  private:
    bool _begun;
    SaSiAesPaddingType_t _paddingType = (SaSiAesPaddingType_t) 0; // SASI_AES_PADDING_NONE
    SaSiAesKeyType_t _userKey = (SaSiAesKeyType_t) 0; // SASI_AES_USER_KEY
};

#endif /* NRFCRYPTO_RANDOM_H_ */ 
