 #include <SoftwareSerial.h>

SoftwareSerial GSM(3, 2);

int buttonPin = 13;
int buttonState = 0;

char num[] = "+639567100591";
char msg[] = "PAKITULUNGAN NGA AKO NAKIDNAP AKO SALAMAT NG MARAMI";

void gsmCheck(String cmd, char *res, int t, int retries) {
  for (int i = 0; i < retries; i++) {
    Serial.println(cmd);
    GSM.println(cmd);
    delay(t);
    while (GSM.available() > 0) {
      if (GSM.find(res)) {
        Serial.println(res);
        return;
      } else {
        Serial.println("Error");
      }
    }
    delay(t);
  }
  Serial.println("No response");
}

void sendSMS(char *number, char *msg) {
  Serial.println("Sending SMS...");
  GSM.print("AT+CMGS=\"");
  GSM.print(number);
  GSM.println("\"");
  delay(100);
  if (GSM.find(">")) {
    GSM.println(msg);
    GSM.write(byte(26));
    Serial.println("SMS sent");
  } else {
    Serial.println("Error: Could not send SMS");
  }
}

void setup() {
  Serial.begin(9600);
  GSM.begin(9600);
  pinMode(buttonPin, INPUT);

  Serial.println("Initializing.....");
  gsmCheck("AT", "OK", 1000, 5);
  gsmCheck("ATE1", "OK", 1000, 5);
  gsmCheck("AT+CPIN?", "READY", 1000, 5);
  gsmCheck("AT+CMGF=1", "OK", 1000, 5);
  gsmCheck("AT+CNMI=2,2,0,0,0", "OK", 1000, 5);
  Serial.println("Initialized Successfully");
}

void loop() {
  buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH) {
    sendSMS(num, msg);
    Serial.println("Button Pressed!");
    delay(5000);
  } else {
    Serial.println("Button unpressed!");
    delay(1000);
  }
}