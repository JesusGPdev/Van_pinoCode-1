void contador(){
  //------------------------------------Inclinar Declinar-----------

  if(digitalRead(control[9])==HIGH){
    cont=0;
    Serial.print("inclinando cont:  ");
    Serial.println(cont);
  }
  
  //------------------------------------Subir Bajar-----------
  if(bajar==1&&subir==0){
    cont++;
    if(cont%10){
      Serial.print("cont:  ");
      Serial.println(cont);
    }
    if(cont>14800){
      digitalWrite(rele[1], HIGH);
      digitalWrite(rele[2], HIGH);
      subir=0;
      bajar=0;
      cont=0;
    }
  }

  if(subir==1&&bajar==0){
    cont++;
    if(cont%10){
      Serial.print("Subiendo cont:  ");
      Serial.println(cont);
    }
    if(cont>2600){
      digitalWrite(rele[1], HIGH);
      digitalWrite(rele[2], HIGH);
      subir=0;
      bajar=0;
      cont=0;
  }
  }
  if((apch==1 && digitalRead(s1)==HIGH)||(cpch==1 && digitalRead(s2)==HIGH)){    //puerta chica abierta || Puerta chica cerrada
    contpch++;
    Serial.print("pch abierta contpch:  ");
    Serial.println(contpch);
  }

  if((apg==1 && digitalRead(s3)==HIGH)||(cpg==1 && digitalRead(s4)==HIGH)){     //puerta grande abierta || Puerta grande cerrada
    contpg++;
    Serial.print("pg abierta contpg:  ");
      Serial.println(contpg);
  }
  
}
