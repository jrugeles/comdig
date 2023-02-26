//Curso de comunicaciones Digitales - UMNG - 2023
// Profesor: José Rugeles 

void setup() {
  // Configurar el registro ADCSRA para ajustar el tiempo de muestreo 
  ADCSRA |= (1 << ADPS2) | (1 << ADPS0);

  // Configurar el puerto serial para la transmisión a 115200 baudios, 7 bits de datos, sin paridad
  Serial.begin(115200,SERIAL_7N1);

  // Configurar la salida digital 7 como salida, para ver el tiempo de muestreo
  pinMode(7, OUTPUT);
}

void loop() {
  // Tomar una muestra del ADC
  int adc_val = analogRead(A0);

  // Generar un pulso digital corto en la salida digital 7
  digitalWrite(7, HIGH);
  delayMicroseconds(5);
  digitalWrite(7, LOW);

  // Esperar 1 microsegundos antes de enviar el valor a través del puerto serial
  delayMicroseconds(10);

  // Enviar el valor a través del puerto serial
  Serial.println(adc_val);

  // Esperar 500 microsegundos antes de tomar la siguiente muestra
  delayMicroseconds(670);
}
