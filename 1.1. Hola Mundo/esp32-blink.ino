void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Hello ESP32");

  pinMode(LED, OUTPUT); // configure D2 GPIO as OUTPUT
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(2, HIGH); // set D2 voltage to HIGH
  delay(500); // 1 second delay
  digitalWrite(LED, LOW); // set D2 voltage to LOW
  delay(500); // 1 second delay
}
