#define POT_PIN       A0

void setup() {
  pinMode(POT_PIN, INPUT);
  Serial.begin(9600);
}

void loop() {
  int analogValue = analogRead(POT_PIN);  // analogValue - [0, 1023]
  double voltage = analogValue/204.6;     // voltage - [0, 5] V
  Serial.print("Tensão no porto A7 (POT_PIN): ");
  Serial.println(voltage);
  delay(200);
}
