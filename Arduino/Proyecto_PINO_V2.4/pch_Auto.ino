//#include <Proyecto_PINO_V2.4.ino>
void pch_Auto(){
  //-----*-*-*-*-*-*-------------Apertura de puerta chica---------*-*-*-*-*-*------------------*-*-*-*-*--------
  if(cont4>350 && apg==1 && apch==0 && digitalRead(s2)==HIGH && digitalRead(s6)==HIGH){ //comienza apertura de ch
    digitalWrite(rele[6],LOW); //Enciende apertura motor Pch
    apch=1;
    Serial.println("Comienza pertura de pch");
    delay(t);
  }

  if(apg==1 && digitalRead(s3)==HIGH && digitalRead(s2)==HIGH && digitalRead(s1)==LOW){
    digitalWrite(rele[6],LOW); //Enciende apertura motor Pch
    apch=2;
    Serial.println("continua con apertura de pch");
    delay(t);
  }

  if(apg==0 && apch==1 && digitalRead(s1)==HIGH && digitalRead(s2)==LOW){ //detiene apertura de puerta
    digitalWrite(rele[6],HIGH); //Apaga apertura motor Pch
    apch=0;
    cont5=0;// seguridad de los motores
    Serial.println("detiene apertura de pch");
    delay(t);
  }
  if(apg==1 && apch==0 && digitalRead(s1)==LOW && digitalRead(s2)==LOW && digitalRead(s6)==HIGH){ //continua con apertura de puerta
    digitalWrite(rele[6],LOW); //Enciende apertura motor Pch
    apch=1;
    Serial.println("continua con apertura de pch");
    delay(t);
  }
  if(apch==1 && digitalRead(s1)==HIGH){//Llega al fin de apertura ch S3
    apch=0;
    cpch=0;
    cont5=0;// seguridad de los motores
    digitalWrite(rele[6], HIGH);
    Serial.println("puerta abierta, s2");
    cont4=0;
    delay(t);
  }

  if(apch==0 && digitalRead(control[1])==HIGH && digitalRead(s3)==HIGH && digitalRead(s1)==LOW){
    digitalWrite(rele[6],LOW); //Enciende apertura motor Pch
    apch=2;
    Serial.println("continua con apertura de pch");
    delay(t);
  }
  
  if(apch==2 && digitalRead(s1)==HIGH){//Llega al fin de apertura ch S3
    apch=0;
    cpch=0;
    cont5=0;// seguridad de los motores
    digitalWrite(rele[6], HIGH);
    Serial.println("puerta abierta, s2");
    cont4=0;
    delay(t);
  }
//-----*-*-*-*-*-*-------------Cierre de puerta chica---------*-*-*-*-*-*------------------*-*-*-*-*--------

  if(digitalRead(s1)==HIGH && digitalRead(s2)==LOW && cpch==0 && cpg==0 && digitalRead(control[2])==HIGH && digitalRead(s6)==HIGH){// Comienza cierre de pch
    digitalWrite(rele[5],LOW); //Apaga apertura motor PG
    cpch=1;
    Serial.println("Comienza cierre de pch");
    delay(t);
  }
  if(digitalRead(control[2])==HIGH && cpch==1 && digitalRead(s1)==LOW && digitalRead(s2)==LOW){ //detiene cierre de puerta grande
    digitalWrite(rele[5],HIGH); //Apaga cierre motor PG
    cpch=0;
    cont5=0;// seguridad de los motores
    Serial.println("detiene cierre de pch");
    delay(t);
  }

  if(digitalRead(control[2])==HIGH && apch==0 && cpch==0 && digitalRead(s1)==LOW && digitalRead(s2)==LOW && digitalRead(s6)==HIGH){ //continua con cierre de pch
    digitalWrite(rele[5],LOW); //Enciende cierre motor PG
    cpch=1;
    Serial.println("continua con cierre de pch");
    delay(t);
  }

  if(cpch==1 && digitalRead(s2)==HIGH){//Llega al fin de cierre pg S4
    apch=0;
    cpch=0;
    cpg=3;
    cont4=0;
    cont5=0;// seguridad de los motores
    digitalWrite(rele[5], HIGH);
    Serial.println("puerta ch cerrada, s2");
    delay(t);
  }
}
