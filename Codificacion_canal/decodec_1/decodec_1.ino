void setup() {
  // Configurar el registro ADCSRA para ajustar el tiempo de muestreo 
  ADCSRA |= (1 << ADPS2) | (1 << ADPS0);

  // Configurar el puerto serial para la transmisión a 9600 baudios, 8 bits de datos, sin paridad
  Serial.begin(9600,SERIAL_8N1);
}

void loop() {
  // Wait for data to be available on the serial port
  while (!Serial.available()) {
    // Do nothing
  }

  // Read the incoming byte
  uint8_t encoded_packet = Serial.read();

  // Extract original packet and parity bits
  uint8_t packet = encoded_packet & 0b00001111;
  bool p1 = encoded_packet >> 7;
  bool p2 = (encoded_packet >> 6) & 1;
  bool p3 = (encoded_packet >> 5) & 1;
  bool p4 = (encoded_packet >> 4) & 1;

  // Calculate new parity bits
  bool np1 = (packet >> 3) ^ (packet >> 2) ^ (packet >> 1) ^ packet ^ p2 ^ p3 ^ p4;
  bool np2 = (packet >> 2) ^ (packet >> 1) ^ packet ^ p1 ^ p3 ^ p4;
  bool np3 = (packet >> 1) ^ packet ^ p1 ^ p2 ^ p4;
  bool np4 = packet ^ p1 ^ p2 ^ p3;

  // Check for errors
  if (p1 != np1 || p2 != np2 || p3 != np3 || p4 != np4) {
    Serial.println("Error en la transmision!");
  } else {
    Serial.println("Paquete decodificado correctamente: " + String(packet, BIN));
  }
}
