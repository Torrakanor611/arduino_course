// Definição de constantes para facilitar a identificação dos portos
  // LEDs
#define RED_PIN       5
#define GREEN_PIN     4 
#define BLUE_PIN      3

  // Botões
#define BUTTON_R_PIN  8
#define BUTTON_G_PIN  7
#define BUTTON_B_PIN  6


// Função setup - é executada uma única vez
void setup() {
  pinMode(BUTTON_R_PIN, INPUT);
  pinMode(RED_PIN, OUTPUT);
  /* Continuar o código aqui */
  pinMode(BUTTON_G_PIN, INPUT);
  pinMode(GREEN_PIN, OUTPUT);

  pinMode(BUTTON_B_PIN, INPUT);
  pinMode(BLUE_PIN, OUTPUT);
}


// Função loop - é executada em ciclo infinito
void loop() {
  int bt_read_r = digitalRead(BUTTON_R_PIN);   // o valor lógico de tensão no porto 8 (BUTTON_R_PIN) é lido para a variável bt_read
  int bt_read_g = digitalRead(BUTTON_G_PIN);
  int bt_read_b = digitalRead(BUTTON_B_PIN);

  if(bt_read_r == HIGH){
     digitalWrite(RED_PIN, HIGH);
  }else{
    digitalWrite(RED_PIN, LOW);
  }

  if(bt_read_g == 1){
     digitalWrite(GREEN_PIN, 1);
  }else{
    digitalWrite(GREEN_PIN, 0);
  }

  if(bt_read_b == HIGH){
     digitalWrite(BLUE_PIN, HIGH);
  }else{
    digitalWrite(BLUE_PIN, LOW);
  }
}
