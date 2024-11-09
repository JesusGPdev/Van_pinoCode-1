void bocina(){
  if(apch>=1 || cpch>=1 || apg>=1 || cpg>=1){
    if(cont5==0 || cont5%t_bocina==0){
      intermitente=!intermitente;
      digitalWrite(boc, intermitente);
      }

    cont5++;
    Serial.print("cont5----");
    Serial.println(cont5);
    Serial.println("----------------------");
    delay(50);
  } else{
      digitalWrite(boc, LOW);
      cont5=0;
  }

  if(cont>t4){                                             //-----Apaga la rampa por tiempo de uso
    Serial.println("RAMPA apagada por tiempo de uso");
    //cont5=0;
    cont=0;
    incli=0;
    decli=0;
    subir=0;
    bajar=0;
    for(int i=1; i<9; i++){         //Salidas digitales, Relevadores y shields motores
      digitalWrite(rele[i], HIGH);
  }
  }
  }
