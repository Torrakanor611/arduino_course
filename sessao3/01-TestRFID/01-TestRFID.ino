#include <SPI.h>
#include <MFRC522.h>

#define SDA_PIN 10
#define SCK_PIN 13
#define MOSI_PIN 11
#define MISO_PIN 12
#define RESET_PIN 9

MFRC522 rfid(SDA_PIN, RESET_PIN);

String id;


void setup() {
	Serial.begin(9600);
	SPI.begin();
	rfid.PCD_Init();
	delay(5);
}


void loop() {
	id = readCard();
	if(!id.equals("")) {
		Serial.println("\n\n**********************");
		Serial.println("      Leitor OK!");
		Serial.println(" Novo cartao detetado");
		Serial.print(" ID: ");
		Serial.println(id);
		Serial.println("**********************");
	}
	delay(1000);
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
