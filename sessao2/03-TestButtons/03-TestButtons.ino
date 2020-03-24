#define BUTTON_0 6
#define BUTTON_1 7
#define BUTTON_2 8

void setup() {
  pinMode(BUTTON_0, INPUT);
  pinMode(BUTTON_1, INPUT);
  pinMode(BUTTON_2, INPUT);
  Serial.begin(9600);
}

void loop() {
  Serial.print("B0: ");
  Serial.print(digitalRead(BUTTON_0));
  Serial.print("\tB1: ");
  Serial.print(digitalRead(BUTTON_1));
  Serial.print("\tB2: ");
  Serial.println(digitalRead(BUTTON_2));
  delay(100);
}
