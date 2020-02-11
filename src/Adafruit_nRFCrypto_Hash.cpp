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

#include "common_inc.h"
#include "rtos.h"
#include "Adafruit_nRFCrypto.h"

//--------------------------------------------------------------------+
// MACRO TYPEDEF CONSTANT ENUM DECLARATION
//--------------------------------------------------------------------+

// Length of Digest Op mode in bytes
static const uint8_t digest_len_arr[] =
{
  CRYS_HASH_SHA1_DIGEST_SIZE_IN_BYTES,
  CRYS_HASH_SHA224_DIGEST_SIZE_IN_BYTES,
  CRYS_HASH_SHA256_DIGEST_SIZE_IN_BYTES,
  CRYS_HASH_SHA384_DIGEST_SIZE_IN_BYTES,
  CRYS_HASH_SHA512_DIGEST_SIZE_IN_BYTES,
  CRYS_HASH_MD5_DIGEST_SIZE_IN_BYTES
};


//------------- IMPLEMENTATION -------------//
Adafruit_nRFCrypto_Hash::Adafruit_nRFCrypto_Hash(void)
{
  _context = NULL;
  _digest_len = 0;
}

bool Adafruit_nRFCrypto_Hash::begin(void)
{
  _context = (CRYS_HASHUserContext_t*) rtos_malloc(sizeof(CRYS_HASHUserContext_t));
  return _context != NULL;
}

void Adafruit_nRFCrypto_Hash::end(void)
{
  rtos_free(_context);
  _context = NULL;
}

bool Adafruit_nRFCrypto_Hash::init(CRYS_HASH_OperationMode_t mode)
{
  nRFCrypto.enable();

  VERIFY_ERROR( CRYS_HASH_Init(_context, mode), false );
  if ( mode < CRYS_HASH_NumOfModes ) _digest_len = digest_len_arr[mode];

  nRFCrypto.disable();
  return true;
}

bool Adafruit_nRFCrypto_Hash::update(uint8_t data[], size_t size)
{
  nRFCrypto.enable();
  VERIFY_ERROR( CRYS_HASH_Update(_context, data, size), false );
  nRFCrypto.disable();
  return true;
}

uint8_t Adafruit_nRFCrypto_Hash::finish(uint32_t result[16])
{
  nRFCrypto.enable();
  VERIFY_ERROR( CRYS_HASH_Finish(_context, result), 0);
  nRFCrypto.disable();

  return _digest_len;
}



