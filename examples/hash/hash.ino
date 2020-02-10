#include "Adafruit_nRFCrypto.h"

//CRYS_RND_State_t rnd_state;
//CRYS_RND_WorkBuff_t rnd_buf;

CRYS_HASHUserContext_t hs_context;

void cc310_enable(void)
{
  // Enable the CryptoCell hardware
  NRF_CRYPTOCELL->ENABLE = 1;
}

void cc310_disable(void)
{
  NRF_CRYPTOCELL->ENABLE = 0;
}

// the setup function runs once when you press reset or power the board
void setup() {
  while( !Serial) delay(10);
  Serial.println("\nCrypto example");

  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  nRFCrypto.begin();

  cc310_enable();

//  CRYS_RndInit(&rnd_state, &rnd_buf);

  uint8_t data[256] =
  {
    0x6b,0xc1,0xbe,0xe2,0x2e,0x40,0x9f,0x96,0xe9,0x3d,0x7e,0x11,0x73,0x93,0x17,0x2a,
    0x65,0xa2,0x32,0xd6,0xbc,0xd0,0xf9,0x39,0xed,0x1f,0xe1,0x28,0xc1,0x3b,0x0e,0x1b
  };
  CRYS_HASH_Result_t result;
  PRINT_BUFFER(data, sizeof(data));

  CRYS_HASH(CRYS_HASH_SHA256_mode, data, 32, result);
//  PRINT_INT ( CRYS_HASH_Update(&hs_context, data, sizeof(data)) );
  PRINT_BUFFER(result, 32);
  delay(10);


  cc310_disable();

  digitalWrite(LED_BUILTIN, LOW);
}
     
// the loop function runs over and over again forever
void loop() {
  digitalToggle(LED_BUILTIN); // turn the LED on (HIGH is the voltage level)

//  uint32_t rnd;

//  cc310_enable();
//  CRYS_RND_GenerateVector(&rnd_state, 4, (uint8_t*) &rnd);
//  cc310_disable();

//  PRINT_INT(rnd);
  delay(1000);                // wait for a second
}

