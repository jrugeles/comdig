//Curso de comunicaciones Digitales - UMNG - 2023
// Profesor: José Rugeles 

#include <Wire.h>
#include <Arduino.h>

// Definir constantes para el puerto serie
const int baud_rate = 9600;
const int parity_bit = 1;

void setup() {
  // Inicializar el puerto serie
  Serial.begin(baud_rate, SERIAL_8O1);

  // Inicializar el módulo MPU6050
  Wire.begin();
  Wire.beginTransmission(0x68); // Dirección del MPU6050
  Wire.write(0x6B); // Dirección del registro de configuración
  Wire.write(0); // Configurar el MPU6050 para que se active
  Wire.endTransmission(true);
  
  // Configurar el terminal A0 como entrada analógica
  pinMode(A0, INPUT);
}

void loop() {
  // Leer el valor analógico en el terminal A0
  int voltage = analogRead(A0);
  
  // Leer la aceleración en el eje X del MPU6050
  Wire.beginTransmission(0x68); // Dirección del MPU6050
  Wire.write(0x3B); // Dirección del registro de lectura de la aceleración en el eje X
  Wire.endTransmission(false);
  Wire.requestFrom(0x68, 2, true); Lee 2 Bytes 
  int16_t accelerometer_x = Wire.read() << 8 | Wire.read();
  
  // Transmitir los datos por el puerto serie
  Serial.print(voltage);
  Serial.print(",");
  Serial.println(accelerometer_x);
  
  // Esperar un tiempo antes de la siguiente lectura
  delay(100);
}
