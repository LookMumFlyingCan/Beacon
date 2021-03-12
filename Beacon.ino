#include <RadioLib.h>

SX1278 radio = new Module(10,9,13,12);

void setup() {
   delay(5000);

  SerialUSB.begin(115200);

  SerialUSB.print(F("[SX1278] Initializing ... "));
  int state = radio.beginFSK();
  if (state == ERR_NONE) {
    SerialUSB.println(F("success!"));
  } else {
    SerialUSB.print(F("failed, code "));
    SerialUSB.println(state);
    while (true);
  }

  state = radio.setFrequency(435.6);
  state = radio.setBitRate(1.2);
  state = radio.setFrequencyDeviation(0);
  state = radio.setOutputPower(5);
  state = radio.setDataShaping(RADIOLIB_SHAPING_1_0);
  state = radio.setOOK(true);
  state = radio.setPreambleLength(1);
  if (state != ERR_NONE) {
    SerialUSB.print(F("Unable to set configuration, code "));
    SerialUSB.println(state);
    while (true);
  }

}

void loop() {

  char charArr[] = "Hello World";
  int len = strlen(charArr);
  radio.startTransmit((uint8_t *)charArr, len);
  
  delay(500);
}
