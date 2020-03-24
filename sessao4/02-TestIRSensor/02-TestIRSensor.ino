// Sensor de bloqueio
#define IR_SENSOR 2

bool obstacle_flag = 0;

void setup() {
	Serial.begin(9600);
	pinMode(IR_SENSOR, INPUT);
}

void loop() {
	if(digitalRead(IR_SENSOR) == 0) obstacle_flag = 1;
	else if(digitalRead(IR_SENSOR) == 1) obstacle_flag = 0;

	if(obstacle_flag == 1) Serial.println("Passagem Bloqueada");
	else if(obstacle_flag == 0) Serial.println("Passagem Não Bloqueada");
	delay(200);
}
