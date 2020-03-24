#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>

// Leitor RFID
#define SDA_PIN 10
#define SCK_PIN 13
#define MOSI_PIN 11
#define MISO_PIN 12
#define RESET_PIN 9

// Leds
#define RED_LED 4
#define GREEN_LED 5
#define BLUE_LED A0
#define YELLOW_LED A1

// Servo
#define SERVO_PIN 3

// Sensor de bloqueio
#define IR_SENSOR 2

// Sensor de ultrassons
#define TRIG_PIN 8
#define ECHO_PIN 7

// Estados
#define SCAN_STATE 0
#define OPEN_STATE 1
#define CLOSED_STATE 2

// Número de cartões na base de dados
#define ID_NUM 2

// Distância a partir da qual a luz de presença acende
#define MAX_DISTANCE 20


MFRC522 rfid(SDA_PIN, RESET_PIN);
Servo servo;


String id = "";
String myid[ID_NUM] = {"", ""};		// base de dados de cartões


int state = 0;				// variável de estado
bool obstacle_flag = 0;		// flag para indicar se há bloqueio
long duration = 0;			// duração do pulso recebido do sensor de ultrassons
int distance = 0;			// distância entre o objeto e o sensor de ultrassons


void setup() {
	// init SPI
  SPI.begin();
	// init RFID
  rfid.PCD_Init();
	delay(5);
	// init servo
  servo.attach(SERVO_PIN);
	// set servo to 0 deg
  servo.write(0);
	// set pin modes (leds, ir sensor, trig and echo)
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);

  pinMode(IR_SENSOR, INPUT);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

void loop() {

	switch(state) {
		// Estado SCAN_STATE
		case SCAN_STATE:
			// set green led low
      digitalWrite(GREEN_LED, LOW);
			// set red led high
      digitalWrite(RED_LED, HIGH);
			// set yellow led low
      digitalWrite(YELLOW_LED, LOW);
			// read card id and store in variable 'id'
      id = readCard();
			// search id in myid database
			for(int i=0; i<ID_NUM; i++) {
				if(myid[i].equals(id)) {
					state = OPEN_STATE;
				}
			}
			// set trig pin low
      digitalWrite(TRIG_PIN, LOW);
			// wait 2 us
      delayMicroseconds(2); 
			// set trig pin high
      digitalWrite(TRIG_PIN, HIGH);
			// wait 10 us
      delayMicroseconds(10);
			// set trig pin low
      digitalWrite(TRIG_PIN, LOW);
			// get echo pin high time and store in variable 'duration'
      duration = pulseIn(ECHO_PIN, HIGH);
			// calculate distance based on duration
      distance = duration * 0,034/2;
			break;

		// Estado OPEN_STATE
		case OPEN_STATE:
			// set green led high
      digitalWrite(GREEN_LED, HIGH);
			// set red led low
      digitalWrite(RED_LED, LOW);
			delay(300);
			// set servo to 90 deg
      servo.write(90);
			// set obstacle flag to 0
      obstacle_flag = 0;
			// wait for 5 sec
			for(int i=0; i<5000; i++) {
				delay(1);
				// check if the passage is blocked, set obstacle flag to 1 and set yellow led high
        if(digitalRead(IR_SENSOR) == 1) obstacle_flag = 0;
			}
			// if obstacle flag is 1 go to open state
      if(obstacle_flag == 1){
        state = OPEN_STATE;
      // else if obstacle flag is 0 go to closed state
      }else{
        state = CLOSED_STATE;
      }
			break;

		// Estado CLOSED_STATE
		case CLOSED_STATE:
			// set yellow led low
      digitalWrite(YELLOW_LED, LOW);
			// set servo to 0 deg
      servo.write(0);
			// go to scan state
     state = SCAN_STATE;
			break;
	}
	// if distance less than MAX_DISTANCE turn white led on
  if(distance <= MAX_DISTANCE){
    pinMode(BLUE_LED, HIGH);
  }
	delay(1);
}

String readCard() {
	String content= "";
	if(rfid.PICC_IsNewCardPresent()) {
		if(rfid.PICC_ReadCardSerial()) {
			for(byte i=0; i<rfid.uid.size; i++) {
				if(rfid.uid.uidByte[i] < 0x10) content.concat(String("0"));
				content.concat(String(rfid.uid.uidByte[i], HEX));
			}
			content.toUpperCase();
		}
	}
	return content;
}
