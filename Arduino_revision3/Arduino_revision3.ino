const int LED = 9;
const int BUTTON = 2;

void setup(){
  pinMode(LED, OUTPUT);
  pinMode(BUTTON, INPUT);
}

void loop(){
  if(digitalRead(BUTTON)==LOW){ //digitalRead - reads the signal value at the input
    digitalWrite(LED, LOW);
  }
  else{
    digitalWrite(LED, HIGH);
  }
}