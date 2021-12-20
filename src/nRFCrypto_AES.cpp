/*
   The MIT License (MIT)

   Copyright (c) 2021 by Kongduino

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

#include "nRFCrypto_AES.h"
#include <cstring>
//--------------------------------------------------------------------+
// MACRO TYPEDEF CONSTANT ENUM DECLARATION
//--------------------------------------------------------------------+


//------------- IMPLEMENTATION -------------//
nRFCrypto_AES::nRFCrypto_AES(void) {
  _begun = false;
}

bool nRFCrypto_AES::begin() {
  if (_begun == true) return true;
  _begun = false;
  int ret = SaSi_LibInit();
  if (ret == SA_SILIB_RET_OK) _begun = true;
  return (ret == SA_SILIB_RET_OK);
}

void nRFCrypto_AES::end() {
  _begun = false;
  SaSi_LibFini();
}

int nRFCrypto_AES::Process(char *msg, uint8_t msgLen, uint8_t *IV, uint8_t *pKey, uint8_t pKeyLen,
                           char *retBuf, SaSiAesEncryptMode_t modeFlag, SaSiAesOperationMode_t opMode) {
  /*
    msg:    the message you want to encrypt. does not need to be a multiple of 16 bytes.
    msgLen:   its length
    IV:     the IV (16 bytes) for CBC
    pKey:   the key (16/24/32 bytes)
    pKeyLen:  its length
    retBuf:   the return buffer. MUST be a multiple of 16 bytes.
    modeFlag: encryptFlag / decryptFlag
    opMode:   ecbMode / cbcMode / ctrMode
  */
  if (!_begun) return -1;
  int ret = SaSi_LibInit();
  if (ret != SA_SILIB_RET_OK) return -2;
  if (pKeyLen % 8 != 0) return -3;
  if (pKeyLen < 16) return -3;
  if (pKeyLen > 32) return -3;
  SaSiAesUserContext_t pContext;
  SaSiError_t err = SaSi_AesInit(&pContext, modeFlag, opMode, _paddingType);
  SaSiAesUserKeyData_t keyData;
  keyData.pKey = pKey;
  keyData.keySize = pKeyLen;
  err = SaSi_AesSetKey(&pContext, _userKey, &keyData, sizeof(keyData));
  if (err != SASI_OK) return -4;
  uint8_t cx, ln = msgLen, ptLen, modulo = 0;
  if (msgLen < 16) {
    ptLen = 16;
    modulo = 16 - msgLen;
  } else {
    modulo = msgLen % 16;
    if (modulo != 0) {
      uint8_t x = (msgLen / 16);
      ptLen = (x + 1) * 16;
      modulo = 16 - modulo;
    } else ptLen = msgLen;
  }
  char pDataIn[ptLen] = {modulo};
  // Padding included!
  memcpy(pDataIn, msg, msgLen);
  size_t dataOutBuffSize;
  memset(retBuf, 0, ptLen);
  if (ptLen > 16) {
    for (cx = 0; cx < ptLen - 16; cx += 16) {
      err = SaSi_AesBlock(&pContext, (uint8_t *) (pDataIn + cx), 16, (uint8_t *) (retBuf + cx));
      if (err != SASI_OK) return -5;
    }
    err = SaSi_AesFinish(
            &pContext,
            (size_t) 16,
            (uint8_t *) (pDataIn + cx),
            (size_t) 16,
            (uint8_t *) (retBuf + cx),
            &dataOutBuffSize);
    if (err != SASI_OK) return -6;
  } else {
    err = SaSi_AesBlock(&pContext, (uint8_t *) pDataIn, 16, (uint8_t *) retBuf);
    if (err != SASI_OK) return -5;
    err = SaSi_AesFinish(
            &pContext,
            (size_t) 0,
            (uint8_t *) (pDataIn),
            (size_t) 0,
            (uint8_t *) (retBuf),
            &dataOutBuffSize);
    if (err != SASI_OK) return -6;
  }
  return 0;
}
