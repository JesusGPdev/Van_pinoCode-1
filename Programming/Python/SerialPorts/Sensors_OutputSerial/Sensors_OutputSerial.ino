String inputString;
int OUT_13 = 13;
int OUT_12 = 12;
int OUT_11 = 11;
int OUT_10 = 10;
int OUT_9  =  9;
int OUT_8  =  8;

void setup(){
  Serial.begin(115200);
  pinMode(OUT_13, OUTPUT);
  pinMode(OUT_12, OUTPUT);
  pinMode(OUT_11, OUTPUT);
  pinMode(OUT_10, OUTPUT);
  pinMode(OUT_9, OUTPUT);
  pinMode(OUT_8, OUTPUT);
  }

void loop(){
  delay(100);
  SerialEvent();
  }

void SerialEvent(){
  while(Serial.available()){
    char inputChar = Serial.read();
    inputString += inputChar;
    }
    if (inputString.indexOf("ON_13")>=0){
      digitalWrite(OUT_13, HIGH);
      delay(100);
      Serial.println("13_on");
    } else if (inputString.indexOf("OFF_13")>=0){
      digitalWrite(OUT_13, LOW);
      delay(100);
      Serial.println("13_off");
    }else if (inputString.indexOf("ON_12")>=0){
      digitalWrite(OUT_12, HIGH);
      delay(100);
      Serial.println("12_on");
    }else if (inputString.indexOf("OFF_12")>=0){
      digitalWrite(OUT_12, LOW);
      delay(100);
      Serial.println("12_off");
    }else if (inputString.indexOf("ON_11")>=0){
      digitalWrite(OUT_11, HIGH);
      delay(100);
      Serial.println("11_on");
    }else if (inputString.indexOf("OFF_11")>=0){
      digitalWrite(OUT_11, LOW);
      delay(100);
      Serial.println("11_off");
    }else if (inputString.indexOf("ON_10")>=0){
      digitalWrite(OUT_10, HIGH);
      delay(100);
      Serial.println("10_on");
    }else if (inputString.indexOf("OFF_10")>=0){
      digitalWrite(OUT_10, LOW);
      delay(100);
      Serial.println("10_off");
    }else if (inputString.indexOf("ON_9")>=0){
      digitalWrite(OUT_9, HIGH);
      delay(100);
      Serial.println("9_on");
    }else if (inputString.indexOf("OFF_9")>=0){
      digitalWrite(OUT_9, LOW);
      delay(100);
      Serial.println("9_off");
    }else if (inputString.indexOf("ON_8")>=0){
      digitalWrite(OUT_8, HIGH);
      delay(100);
      Serial.println("8_on");
    }else if (inputString.indexOf("OFF_8")>=0){
      digitalWrite(OUT_8, LOW);
      delay(100);
      Serial.println("8_off");
    }
    
    inputString = "";
  }
