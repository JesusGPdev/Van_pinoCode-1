void candado(){
  if((digitalRead(control[11])==HIGH&&cont3<50)){// apaga todo y pone todo en cero
    cont=0;
    subir=0;
    bajar=0;
    incli=0;
    decli=0;
    apch=0;
    cpch=0;
    apg=0;
    cpg=0;
    for(int i=1; i<9; i++){         //Apaga Salidas digitales, Relevadores
    digitalWrite(rele[i], HIGH);
  }
    digitalWrite(boc, HIGH);
    delay(t);
    digitalWrite(boc, LOW);
    delay(t);
    digitalWrite(boc, HIGH);
    delay(t);
    digitalWrite(boc, LOW);
    Serial.println("Puesto todas las variables en CERO");
  }
  cont3=0;
  while(digitalRead(control[11])==HIGH){
    cont3++;
    if(cont3==t2&&automatico==0){
      automatico=1;
      EEPROM.write(0, automatico);
      Serial.print("Modo Automatico Activado: ");
      Serial.println(automatico);
      cont3=0;
      digitalWrite(boc, HIGH);
    delay(t/2);
    digitalWrite(boc, LOW);
    delay(t/2);
    digitalWrite(boc, HIGH);
    delay(t/2);
    digitalWrite(boc, LOW);
    }
    if(cont3==t2&&automatico==1){
      automatico=0;
      EEPROM.write(0, automatico);
      Serial.print("Modo automatico Desactivado: ");
      Serial.println(automatico);
      cont3=0;
      digitalWrite(boc, HIGH);
    delay(t/2);
    digitalWrite(boc, LOW);
    delay(t/2);
    digitalWrite(boc, HIGH);
    delay(t/2);
    digitalWrite(boc, LOW);
    delay(t/2);
    digitalWrite(boc, HIGH);
    delay(t/2);
    digitalWrite(boc, LOW);
    }
    Serial.println(cont3);
    
  }
cont2=0;
  while(digitalRead(control[12])==HIGH){//bloquea el control con el boton 12 del control remoto
    cont2++;
    if(cont2==t2){
      hold=1;
      cont2=0;
      Serial.println("Control Bloqueado");
    }
    while(hold>=1){
      if(hold==1){
  digitalWrite(boc, HIGH);
  delay(t/2);
  digitalWrite(boc, LOW);
  delay(t/2);
  digitalWrite(boc, HIGH);
  delay(t/2);
  digitalWrite(boc, LOW);
  delay(t/2);
  digitalWrite(boc, HIGH);
  delay(t/2);
  digitalWrite(boc, LOW);
  hold=2;
      }
      while(digitalRead(control[12])==HIGH){
        cont2++;
      if(cont2==t2){
      hold=0;
      cont2=0;
      Serial.println("Control Desbloqueado");
      digitalWrite(boc, HIGH);
      delay(t*2);
      digitalWrite(boc, LOW);
    }
    Serial.println(cont2);
    }
    }
    Serial.println(cont2);
  }
}

void candado2(){
  cont=0;
    subir=0;
    bajar=0;
    incli=0;
    decli=0;
    apch=0;
    cpch=0;
    apg=0;
    cpg=0;
    for(int i=1; i<9; i++){         //Apaga Salidas digitales, Relevadores
    digitalWrite(rele[i], HIGH);
  }
}
