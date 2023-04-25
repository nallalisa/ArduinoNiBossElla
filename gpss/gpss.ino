#include <TinyGPS++.h>
#include <SoftwareSerial.h>

static const int RXPin = 4, TXPin = 3;

static const uint32_t GPSBaud = 9600;

TinyGPSPlus gps;

SoftwareSerial ss (RXPin, TXPin);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  ss.begin(GPSBaud);
}

void loop() {
  // put your main code here, to run repeatedly:
  while(ss.available()>0)
    if(gps.encode(ss.read()))
      displayInfo();
  
  if(millis() > 5000 && gps.charsProcessed() < 10){
    Serial.println(F("No GPS detected: Check wiring."));
    while(true);
  }
}

void displayInfo(){
  Serial.print(F("Location: "));
  if(gps.location.isValid()){
    Serial.print(gps.location.lat(), 6);
    Serial.print(F(", "));
    Serial.print(gps.location.lng(), 6);
  }
  else{
    Serial.print(F("INVALID"));
  }
  Serial.println();
}
