
void setup() {
  // Configurar el registro ADCSRA para ajustar el tiempo de muestreo 
  ADCSRA |= (1 << ADPS2) | (1 << ADPS0);

  // Configurar el puerto serial para la transmisión a 9600 baudios, 8 bits de datos, sin paridad
  Serial.begin(9600,SERIAL_8N1);
}

void loop() {
  // Original 8-bit packet
  uint8_t packet = 0b10111011;

  // Calculate parity bits
  bool p1 = (packet >> 7) ^ (packet >> 6) ^ (packet >> 5) ^ (packet >> 4);
  bool p2 = (packet >> 6) ^ (packet >> 5) ^ (packet >> 4) ^ (packet >> 3);
  bool p3 = (packet >> 5) ^ (packet >> 4) ^ (packet >> 3) ^ (packet >> 2);
  bool p4 = (packet >> 4) ^ (packet >> 3) ^ (packet >> 2) ^ (packet >> 1);

  // Combine original packet and parity bits
  uint8_t encoded_packet = (p1 << 7) | (p2 << 6) | (p3 << 5) | (p4 << 4) | packet;

  // Send encoded packet using RS232
  Serial.write(encoded_packet);

  // Wait for 1 second before sending the next packet
  delay(1000);
}
