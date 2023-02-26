//Curso de comunicaciones Digitales - UMNG - 2023
// Profesor: José Rugeles 

#include <Wire.h>

const int MPU_addr=0x68;  // Direccion del sensor MPU6050 en el bus I2C
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;

void setup()
{
  Serial.begin(9600);  // Inicializar la comunicación serial a 9600 baudios
  Wire.begin();        // Inicializar el bus I2C
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);     // PWR_MGMT_1 register
  Wire.write(0);        // Setear en 0 para activar el sensor
  Wire.endTransmission(true);
}

void loop()
{
  Wire.beginTransmission(MPU_addr); // Iniciar la comunicación con el MPU6050
  Wire.write(0x3B);                 // Direccion del registro donde comienza la lectura
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr,14,true); // Leer 14 bytes de datos

  AcX=Wire.read()<<8|Wire.read();   // Leer los valores del acelerometro
  AcY=Wire.read()<<8|Wire.read();
  AcZ=Wire.read()<<8|Wire.read();
  Tmp=Wire.read()<<8|Wire.read();   // Leer el valor de la temperatura
  GyX=Wire.read()<<8|Wire.read();   // Leer los valores del giroscopio
  GyY=Wire.read()<<8|Wire.read();
  GyZ=Wire.read()<<8|Wire.read();

  int sensorValue = analogRead(A0); // Leer el valor del potenciometro
  float voltage = sensorValue * (5.0 / 1023.0); // Convertir el valor del potenciometro a voltaje
  
  Serial.print("Pt: ");
  Serial.print(voltage);
  Serial.print("V, ");
  Serial.print("Acel: ");
  Serial.print(AcX);
  Serial.print(",");
  Serial.print(AcY);
  Serial.print(",");
  Serial.print(AcZ);
  Serial.print(", Temp: ");
  Serial.print(Tmp/605.0+21.0); // Convertir el valor de la temperatura a grados Celsius
  Serial.print(", Gir: ");
  Serial.print(GyX);
  Serial.print(",");
  Serial.print(GyY);
  Serial.print(",");
  Serial.println(GyZ);

  delay(100); // Esperar 500 milisegundos antes de tomar otra muestra
}
