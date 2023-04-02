#include <SPI.h>
#include <RH_NRF24.h>

RH_NRF24 nrf24;

void setup() {
  Serial.begin(9600);
  
  if (!nrf24.init())
    Serial.println("fallo de inicializacion");
  if (!nrf24.setChannel(102))
    Serial.println("fallo en establecer canal");
  if (!nrf24.setRF(RH_NRF24::DataRate250kbps, RH_NRF24::TransmitPower0dBm))
    Serial.println("fallo en opciones RF");
}

void loop() {
  if (nrf24.available()) {
    uint8_t buf[RH_NRF24_MAX_MESSAGE_LEN];
    uint8_t len = sizeof(buf);

    if (nrf24.recv(buf, &len)) {
      Serial.print("Recibido: ");
      Serial.println((char*)buf);
    } else {
      Serial.println("fallo en recepcion");
    }
  }
}
