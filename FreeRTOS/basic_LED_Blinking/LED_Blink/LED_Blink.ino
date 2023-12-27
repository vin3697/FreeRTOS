#define RED 8
#define GREEN 6
#define BLUE 3



void setup() {
  // put your setup code here, to run once:
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(RED, digitalRead(RED)^1);
  digitalWrite(GREEN, digitalRead(GREEN)^1);
  digitalWrite(BLUE, digitalRead(BLUE)^1);
  delay(500);

}
