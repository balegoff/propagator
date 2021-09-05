void setup()
{
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

void loop()
{

  // Read analog pin 0
  int sensor_value = analogRead(A0); 

  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  float voltage = sensor_value * (5.0 / 1023.0);

  // Print value on serial port as float
  Serial.println(voltage, DEC);

  // Wait 10 ms
  delay(10);
  
}
