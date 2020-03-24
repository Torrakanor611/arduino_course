  /*
   * Bibliotecas
   */
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include "music.h"


  /*
   * Inicialização de variáveis
   */
int thisNote = 0;           // nota atual de uma certa música, varia entre 0 e songSize(thisSong)-1
int thisSong = -1;          // música atual, varia entre 0 e NUMBER_OF_SONGS-1

char stopFlag = 0;          // quando stopFlag = 1, significa que o botão stop foi pressionado
char nextFlag = 0;          // quando nextFlag = 1, significa que o botão next foi pressionado
char prevFlag = 0;          // quando prevFlag = 1, significa que o botão prev foi pressionado
                            // após uma flag ser lida como '1' é necessário colocá-la a '0' novamente

char state = MANAGE_STATE;  // variável de estado, indica o estado atual do funcionamento do sistema
                            // pode variar tomar os seguites valores: STOP_STATE, PLAY_STATE e MANAGE_STATE


LiquidCrystal_I2C lcd(0x27,16,2);


  /*
  * Função setup - é executada uma única vez
  */
void setup() {
  pinMode(BUZZER_PIN , D3);
  pinMode(STOP_BUTTON_PIN, D7);
  pinMode(NEXT_BUTTON_PIN, D6);
  pinMode(PREV_BUTTON_PIN, D8);

  lcd.init();
  lcd.backlight();  
  lcd.noBacklight();
  lcd.clear();
}


  /*
   * Função loop - é executada em ciclo infinito
   */
void loop() {
  
  readButtons();  // faz a leitura dos botões para que as flags possam ser atualizadas
  
  switch(state) {
    case PLAY_STATE:
      play(thisSong,thisNote);
      thisNote++;   // igual a: thisNote = thisNote + 1;
      if(thisNote > songSize(thisSong)) state = MANAGE_STATE;
      break;
    
    case STOP_STATE:
      if()
      break;
    
    case MANAGE_STATE:
      thisSong++;   // igual a: thisNote = thisNote + 1;
      if(thisSong == NUMBER_OF_SONGS) thisSong = 0;
      thisNote = 0;
      state = PLAY_STATE;
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Faixa ");
      lcd.print(thisSong+1);
      delay(200);
      break;
  }
  
}
