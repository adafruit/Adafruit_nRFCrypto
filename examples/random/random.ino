#include "Adafruit_nRFCrypto.h"

Adafruit_nRFCrypto_Random rnd;

// the setup function runs once when you press reset or power the board
void setup()
{
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);

  while( !Serial) delay(10);
  Serial.println("nRFCrypto Random example");

  nRFCrypto.begin();

  rnd.begin();

  nRFCrypto.end();

}

void loop()
{
  digitalToggle(LED_BUILTIN);
  delay(1000);
}

