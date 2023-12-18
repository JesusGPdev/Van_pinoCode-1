int BTNS[] = {8, 9,10,11,12,13};
int SAL_ARD [] = {2, 3, 4, 5, 6, 7};
int SAL_LED[] = {A5, A4, A3, A2, A1, A0};
bool stts=LOW;
int b=0;

void setup() {
  Serial.begin(115200);
  for(int i=0; i<6 ; i++){
    pinMode(BTNS[i], INPUT);
    pinMode(SAL_ARD[i] , OUTPUT);
    pinMode(SAL_LED[i] , OUTPUT);
    
    digitalWrite(SAL_LED[i], HIGH);
    delay(300);
    digitalWrite(SAL_LED[i], LOW);
  }
}

void loop() {

  /*if(digitalRead(BTNS[b])==HIGH){
    Serial.println("Flag 1");
    stts = !stts;
    digitalWrite(SAL[b], stts);
    while(digitalRead(BTNS[b])==HIGH){
      Serial.println("Flag 2");
      delay(500);
    }*/
  for(int i=0; i<6 ; i++){
  if(digitalRead(BTNS[i])==HIGH){
    Serial.println(i);
    stts = !stts;
      Serial.print("STATUS: ");
      Serial.println(stts);
      Serial.print("BTNS: ");
      Serial.println(BTNS[i]);
      Serial.print("-----------------------");
      Serial.print(" ");
    digitalWrite(SAL_ARD[i], stts);
    digitalWrite(SAL_LED[i], stts);
    /*while(digitalRead(BTNS[i])==HIGH){
      
    }*/
    delay(500);
    }
  }
}
