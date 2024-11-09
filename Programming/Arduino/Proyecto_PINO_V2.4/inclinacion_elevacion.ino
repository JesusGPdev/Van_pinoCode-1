void inclinacion_elevacion(){
  if(digitalRead(control[5])==HIGH && incli==0 && decli==0 && subir ==0 && bajar==0 && digitalRead(s5)==HIGH){//Inclina la rampa
    digitalWrite(rele[4], LOW);
    incli=1;
    delay(t);
  }
  if(digitalRead(control[5])==HIGH && incli==1 && decli==0 && subir ==0 && bajar==0){// detiene Inclinacion de la rampa
    digitalWrite(rele[4], HIGH);
    incli=0;
    cont5=0;// seguridad de los motores
    delay(t);
  }

  if(digitalRead(control[5])==HIGH && incli==0 && digitalRead(s5)==LOW && digitalRead(s6)==LOW){// Continua Inclinacion de la rampa
    digitalWrite(rele[4], LOW);
    incli=1;
    delay(t);
  }

  if(digitalRead(s6)==HIGH && incli==1){    //Se inclina por completo la rampa
    digitalWrite(rele[4], HIGH);
    incli=0;
    cont5=0;// seguridad de los motores
    delay(t);
  }

  if(digitalRead(control[6])==HIGH && incli==0 && decli==0 && subir ==0 && bajar==0 && digitalRead(s6)==HIGH){//Declina la rampa
    digitalWrite(rele[3], LOW);
    decli=1;
    delay(t);
  }
  if(digitalRead(control[6])==HIGH&&decli==1){// detiene Declinacion de la rampa
    digitalWrite(rele[3], HIGH);
    decli=0;
    cont5=0;// seguridad de los motores
    delay(t);
  }

  if(digitalRead(control[6])==HIGH && decli==0 && digitalRead(s6)==LOW && digitalRead(s5)==LOW){// continua Declinacion de la rampa
    digitalWrite(rele[3], LOW);
    decli=1;
    delay(t);
  }

  if(digitalRead(s5)==HIGH && decli==1){    //Se declina por completo la rampa
    digitalWrite(rele[3], HIGH);
    decli=0;
    cont5=0;// seguridad de los motores
    
    delay(t);
  }
//--------------------------Subida y bajada de rampa---------------------------------------------------
if(digitalRead(control[7])==HIGH && incli==0 && decli==0 && subir ==0 && bajar==0 && digitalRead(s5)==HIGH){//Baja la rampa
    digitalWrite(rele[2], LOW);
    bajar=1;
    delay(t);
  }
  if(digitalRead(control[7])==HIGH && bajar==1 && digitalRead(s5)==HIGH){// detiene bajada de la rampa
    digitalWrite(rele[2], HIGH);
    bajar=0;
    //cont5=0;// seguridad de los motores
    delay(t);
  }

  if(digitalRead(control[8])==HIGH && incli==0 && decli==0 && subir ==0 && bajar==0 && digitalRead(s5)==HIGH){//sube la rampa
    digitalWrite(rele[1], LOW);
    subir=1;
    delay(t);
  }
  if(digitalRead(control[8])==HIGH && subir==1 && digitalRead(s5)==HIGH){// detiene Subida de la rampa
    digitalWrite(rele[1], HIGH);
    Serial.println("Rampa Subida a tope");
    subir=0;
    cont=0;
    bajar=0;
    //cont5=0;// seguridad de los motores
    delay(t);
  }

  if(subir==1&&digitalRead(s5)==HIGH){
    candado2();
    Serial.println("Paso por aqui");
  }
  
}
