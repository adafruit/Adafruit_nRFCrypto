#include "Adafruit_nRFCrypto.h"

//CRYS_RND_State_t rnd_state;
//CRYS_RND_WorkBuff_t rnd_buf;

/* Input data for testing
 * Same data is stored in input_data.bin file, to verify the result, run hash sum on your PC
 * and compare the result with this sketch
 *
 *  $ sha1sum input_data.bin
 *    9f9da10ec23735930089a8f89b34f7b5d267903e
 *
 *  $ sha224sum input_data.bin
 *    68abe34d09a758be6b2fb3a7a997983a639687099d35406f927a5cc5  input_data.bin
 *
 *  $ sha256sum input_data.bin
 *    75cfb39b62c474921e2aad979c210f8b69180a9d58e9f296a4b9904ae6e7aa40
 *
 *
 *
 */
uint8_t input_data[] =
{
  0x6b, 0xc1, 0xbe, 0xe2, 0x2e, 0x40, 0x9f, 0x96, 0xe9, 0x3d, 0x7e, 0x11, 0x73, 0x93, 0x17, 0x2a,
  0x65, 0xa2, 0x32, 0xd6, 0xbc, 0xd0, 0xf9, 0x39, 0xed, 0x1f, 0xe1, 0x28, 0xc1, 0x3b, 0x0e, 0x1b
//0x99,0xfd,0x18,0xa3,0x5d,0x50,0x81,0x84,0xa6,0xf3,0x61,0xc6,0x7c,0xd9,0xb1,0x0b,
//		0x4c,0xd1,0xd8,0xb2,0x46,0x57,0x2a,0x4d,0x03,0xb0,0xae,0x55,0x6b,0x36,0x24,0x1d,
//		0xd6,0xf0,0x46,0x05,0x71,0x65,0x4f,0xf0,0xe4,0xb2,0xba,0xf8,0x31,0xdb,0x4c,0x60,
//		0xdf,0x5f,0x54,0xc9,0x59,0x0f,0x32,0xa9,0x91,0x1f,0x16,0xfa,0xe8,0x7e,0x0a,0x2f
};

// the setup function runs once when you press reset or power the board
void setup()
{
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);

  while( !Serial) delay(10);
  Serial.println("nRFCrypto Hash example");

  nRFCrypto.begin();
  nRFCrypto.Hash.begin();

  test_hash(CRYS_HASH_SHA1_mode   , "SHA1  ");
  test_hash(CRYS_HASH_SHA224_mode , "SHA224");
  test_hash(CRYS_HASH_SHA256_mode , "SHA256");
//  test_hash(CRYS_HASH_SHA384_mode , "SHA384");
  test_hash(CRYS_HASH_SHA512_mode , "SHA512");
//  test_hash(CRYS_HASH_MD5_mode    , "MD5");

  nRFCrypto.Hash.end();
}

void test_hash(uint32_t mode, const char* modestr)
{
  uint32_t result[16];
  uint8_t  result_len; // depending on Hash mode

  nRFCrypto.Hash.init(mode);
  nRFCrypto.Hash.update(input_data, sizeof(input_data));
  result_len = nRFCrypto.Hash.finish(result);

  Serial.print(modestr);
  Serial.print(" : ");
  Serial.printBuffer( (uint8_t*) result, result_len);
  Serial.println();

  Serial.flush();
}

void loop()
{
  digitalToggle(LED_BUILTIN);
  delay(1000);
}

