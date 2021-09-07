#include<ESP8266WiFi.h>
#include<BlynkSimpleEsp8266.h>


char auth[] = "GLDfb_mLx7l5Jj4uzzTt3bCWOOP9HjMq";

char ssid[] = "tedata_nomap (A)";
char pass[] = "Gsaiho2019.";

void setup() {
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
}


void loop() {
  Blynk.run();
}
