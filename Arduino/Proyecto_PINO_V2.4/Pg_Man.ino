void puertaG(){
//-----*-*-*-*-*-*-------------Apertura de puerta grande---------*-*-*-*-*-*------------------*-*-*-*-*--------
  if(digitalRead(control[1])==HIGH && apg==0 && cpg==0 && digitalRead(s4)==HIGH){ //comienza apertura de pg
    digitalWrite(rele[8],LOW); //Enciende apertura motor PG
    apg=1;
    Serial.println("Comienza pertura de puerta Grande");
    delay(t);
  }

  if(digitalRead(control[1])==HIGH && apg==1 && digitalRead(s3)==LOW && digitalRead(s4)==LOW){ //detiene apertura de puerta
    digitalWrite(rele[8],HIGH); //Apaga apertura motor PG
    apg=0;
    //cont5=0;// seguridad de los motores
    Serial.println("detiene apertura de puerta Grande");
    delay(t);
  }
  if(digitalRead(control[1])==HIGH && apg==0 && cpg==0 && digitalRead(s3)==LOW && digitalRead(s4)==LOW){ //continua con apertura de puerta
    digitalWrite(rele[8],LOW); //Enciende apertura motor PG
    apg=1;
    Serial.println("continua con apertura de pg");
    delay(t);
  }
  if(apg==1 && digitalRead(s3)==HIGH&&contpg==tspg){//Llega al fin de apertura pg S3
    apg=0;
    cpg=0;
    contpg=0;
    cont5=0;// seguridad de los motores
    digitalWrite(rele[8], HIGH);
    Serial.println("puerta abierta, s3");
    delay(t);
  }
//-----*-*-*-*-*-*-------------Cierre de puerta grande---------*-*-*-*-*-*------------------*-*-*-*-*--------

  if(digitalRead(s3)==HIGH && digitalRead(s4)==LOW && digitalRead(s1)==LOW && cpg==0 && apg==0 && digitalRead(control[2])==HIGH && digitalRead(s6)==HIGH){// Comienza cierre de pg
    digitalWrite(rele[7],LOW); //Apaga apertura motor PG
    cpg=1;
    Serial.println("Comienza cierre de puerta Grande");
    delay(t);
  }
  if(digitalRead(control[2])==HIGH && cpg==1 && digitalRead(s3)==LOW && digitalRead(s4)==LOW){ //detiene cierre de puerta grande
    digitalWrite(rele[7],HIGH); //Apaga cierre motor PG
    cpg=0;
    //cont5=0;// seguridad de los motores
    Serial.println("detiene cierre de puerta Grande");
    delay(t);
  }

  if(digitalRead(control[2])==HIGH && apg==0 && cpg==0 && digitalRead(s3)==LOW && digitalRead(s4)==LOW && digitalRead(s6)==HIGH){ //continua con cierre de puerta grande
    digitalWrite(rele[7],LOW); //Enciende cierre motor PG
    cpg=1;
    Serial.println("continua con cierre de puerta");
    delay(t);
  }

  if(cpg==1 && digitalRead(s4)==HIGH&&contpg==tspg){//Llega al fin de cierre pg S4
    apg=0;
    cpg=0;
    cont5=0;// seguridad de los motores
    contpg=0;
    digitalWrite(rele[7], HIGH);
    Serial.println("puerta cerrada, s4");
    delay(t);
  }
  
}
