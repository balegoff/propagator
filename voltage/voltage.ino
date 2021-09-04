void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

void loop() {
  // Read the input on analog pin 2:
  int sensorValue = analogRead(A2);
  
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  float voltage = sensorValue * (5.0 / 1023.0);

  // Print value on serial port with 3 decimals
  Serial.println(voltage, 3);

  // Wait 10 ms
  delay(10);
}
