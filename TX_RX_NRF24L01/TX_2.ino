#include <SPI.h>
#include <RH_NRF24.h>

RH_NRF24 nrf24;
const int ledPin = 6;

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  
  if (!nrf24.init())
    Serial.println("fallo de inicializacion");
  if (!nrf24.setChannel(102))
    Serial.println("fallo en establecer canal");
  if (!nrf24.setRF(RH_NRF24::DataRate250kbps, RH_NRF24::TransmitPower0dBm))
    Serial.println("fallo en opciones RF");
}

void loop() {
  uint8_t data[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  nrf24.send(data, sizeof(data));
  nrf24.waitPacketSent();

  digitalWrite(ledPin, HIGH);
  delay(1000);
  digitalWrite(ledPin, LOW);

  delay(1000);
}
