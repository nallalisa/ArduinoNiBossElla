#include <SoftwareSerial.h>

#define rxPin 8
#define txPin 9
SoftwareSerial gpsSerial(rxPin,txPin); 

void setup()
{
  // Serial.begin(115200);

  Serial.begin(9600);
  
  gpsSerial.begin(9600);

  Serial.println("Initializing...");
  delay(1000);
}

void loop()
{
  while (gpsSerial.available() > 0)
    Serial.write(gpsSerial.read());
}
