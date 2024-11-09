void puertaCH(){
//-----*-*-*-*-*-*-------------Apertura de puerta chica---------*-*-*-*-*-*------------------*-*-*-*-*--------
  if(digitalRead(control[3])==HIGH && apch==0 && cpch==0 && digitalRead(s2)==HIGH  && digitalRead(s4)==LOW){ //comienza apertura de ch
    digitalWrite(rele[6],LOW); //Enciende apertura motor Pch
    apch=1;
    Serial.println("Comienza pertura de pch");
    delay(t);
  }

  if(digitalRead(control[3])==HIGH && apch==1 && digitalRead(s1)==LOW && digitalRead(s2)==LOW){ //detiene apertura de puerta
    digitalWrite(rele[6],HIGH); //Apaga apertura motor Pch
    apch=0;
    //cont5=0;// seguridad de los motores
    Serial.println("detiene apertura de pch");
    delay(t);
  }
  if(digitalRead(control[3])==HIGH && apch==0 && cpch==0 && digitalRead(s1)==LOW && digitalRead(s2)==LOW){ //continua con apertura de puerta
    digitalWrite(rele[6],LOW); //Enciende apertura motor Pch
    apch=1;
    Serial.println("continua con apertura de pch");
    delay(t);
  }
  if(apch==1 && digitalRead(s1)==HIGH && contpch==tspch){//Llega al fin de apertura ch S3
    apch=0;
    cpch=0;
    cont5=0;// seguridad de los motores
    contpch=0;
    digitalWrite(rele[6], HIGH);//Apaga motor de pch
    Serial.println("puerta abierta, s2");
    delay(t);
  }
//-----*-*-*-*-*-*-------------Cierre de puerta chica---------*-*-*-*-*-*------------------*-*-*-*-*--------

  if(digitalRead(s1)==HIGH && digitalRead(s2)==LOW && cpch==0 && apch==0 && digitalRead(control[4])==HIGH && digitalRead(s6)==HIGH){// Comienza cierre de pch
    digitalWrite(rele[5],LOW); //Cierre Pch
    cpch=1;
    Serial.println("Comienza cierre de pch");
    delay(t);
  }
  if(digitalRead(control[4])==HIGH && cpch==1 && digitalRead(s1)==LOW && digitalRead(s2)==LOW){ //detiene cierre de puerta grande
    digitalWrite(rele[5],HIGH); //Apaga cierre motor PG
    cont5=0;// seguridad de los motores
    cpch=0;
    Serial.println("detiene cierre de pch");
    delay(t);
  }

  if(digitalRead(control[4])==HIGH && apch==0 && cpch==0 && digitalRead(s1)==LOW && digitalRead(s2)==LOW && digitalRead(s6)==HIGH){ //continua con cierre de pch
    digitalWrite(rele[5],LOW); //Enciende cierre motor PG
    cpch=1;
    Serial.println("continua con cierre de pch");
    delay(t);
  }

  if(cpch==1 && digitalRead(s2)==HIGH&&contpch==tspch){//Llega al fin de cierre pg S4
    apch=0;
    cpch=0;
    cont5=0;// seguridad de los motores
    contpch=0;
    digitalWrite(rele[5], HIGH);
    Serial.println("puerta cerrada, s2");
    delay(t);
  }
  
}
