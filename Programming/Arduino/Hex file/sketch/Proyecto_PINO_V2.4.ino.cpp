#include <Arduino.h>
#line 1 "C:\\Users\\Administrador\\Desktop\\SAICON_PC\\PROYECTOS\\Puerta automatica_PINO\\Van\\2022\\Programación_PINO\\Proyecto_PINO_V2.4\\Proyecto_PINO_V2.4.ino"
#line 1 "C:\\Users\\Administrador\\Desktop\\SAICON_PC\\PROYECTOS\\Puerta automatica_PINO\\Van\\2022\\Programación_PINO\\Proyecto_PINO_V2.4\\Proyecto_PINO_V2.4.ino"
#include <EEPROM.h>

int control[13]={75,20,21,22,23,25,24,26,27,28,29,30,31}; //Entradas de control remoto
int rele[9]={74,9,8,7,6,2,3,4,5};   //Salidas a Relevdores
int s1=14; int s2=15; int s3=16; int s4=17; //Sensores de puertas
int s5=18; int s6=19;                       //Sensores rampa
int pch=10;//variable para velocidad de motor de puerta chica
int pg=11; //variable para velocidad de motor de puerta grande
int apg=0; //variable de Abrir puerta grande 
int cpg=0; //variable de Cerrar puerta grande
int apch=0; //variable de Abrir puerta chica 
int cpch=0; //variable de Cerrar puerta chica
int incli=0;//variable de inclinacion de rampa
int decli=0;//variable de declinacion de rampa
int subir=0;//variable para subir rampa
int bajar=0;//variable para bajar rampa
int t=500;// tiempo de espera de control
int t2=300;//Tiempo para bloquear todo
int t3=500;//Tiempo para la seguridad de los motores
int t4=200; //tiempo para apagar la inclinacion o declinacion de rampa
int tspch=50; //Tiempo espera cuando el motor de la pch llega a los extremos
int contpch=0; //contador de tiempo para la variable tspch
int tspg=50; //Tiempo espera cuando el motor de la pg llega a los extremos
int contpg=0; //contador de tiempo para la variable tspg
int cont=0;// contador de inclinacion declinacion de rampa
int cont2=0;// contador de subir y bajar rampa
int cont3=0; //contador para cambiar el modo automatico
int cont4=0; //Contador para abrir/Cerrar puertas en modo automatico
int cont5=0; //Contador de seguridad para evitar que se quemen a la verga los motores

int automatico=0;//Determina cuando el modo automatico esta activo
int boc=12; //salida pin digital bocina
int t_bocina=2; //tiempo de intermitencia de bocina
int hold=0;//candado
boolean intermitente=LOW;
//----------------------------Medidor de corriente---------------------------------------------------------
float amplimitpch=50; //0.7 
float amplimitpg=50;  //0.9
float SENSIBILITY = 0.185;   // Modelo 5A
int SAMPLESNUMBER = 200;

float currentpg=0;          //Piston Pg
float currentRMS=0;       //Piston Pg
float power=0;            //Piston Pg
float corrientepg=0;        //Piston Pg

float currentpch=0;          //Piston Pch
float currentRMSpg=0;       //Piston Pch
float powerpg=0;            //Piston Pch
float corrientepch=0;        //Piston Pch
//-------------------------------------------------------------------------------------

#line 53 "C:\\Users\\Administrador\\Desktop\\SAICON_PC\\PROYECTOS\\Puerta automatica_PINO\\Van\\2022\\Programación_PINO\\Proyecto_PINO_V2.4\\Proyecto_PINO_V2.4.ino"
void setup();
#line 104 "C:\\Users\\Administrador\\Desktop\\SAICON_PC\\PROYECTOS\\Puerta automatica_PINO\\Van\\2022\\Programación_PINO\\Proyecto_PINO_V2.4\\Proyecto_PINO_V2.4.ino"
void loop();
#line 1 "C:\\Users\\Administrador\\Desktop\\SAICON_PC\\PROYECTOS\\Puerta automatica_PINO\\Van\\2022\\Programación_PINO\\Proyecto_PINO_V2.4\\Candado_y_automatico.ino"
void candado();
#line 102 "C:\\Users\\Administrador\\Desktop\\SAICON_PC\\PROYECTOS\\Puerta automatica_PINO\\Van\\2022\\Programación_PINO\\Proyecto_PINO_V2.4\\Candado_y_automatico.ino"
void candado2();
#line 1 "C:\\Users\\Administrador\\Desktop\\SAICON_PC\\PROYECTOS\\Puerta automatica_PINO\\Van\\2022\\Programación_PINO\\Proyecto_PINO_V2.4\\Corriente_M.ino"
void corriente_m();
#line 19 "C:\\Users\\Administrador\\Desktop\\SAICON_PC\\PROYECTOS\\Puerta automatica_PINO\\Van\\2022\\Programación_PINO\\Proyecto_PINO_V2.4\\Corriente_M.ino"
float getCorrientepg(int samplesNumber);
#line 31 "C:\\Users\\Administrador\\Desktop\\SAICON_PC\\PROYECTOS\\Puerta automatica_PINO\\Van\\2022\\Programación_PINO\\Proyecto_PINO_V2.4\\Corriente_M.ino"
float getCorrientepch(int samplesNumber);
#line 1 "C:\\Users\\Administrador\\Desktop\\SAICON_PC\\PROYECTOS\\Puerta automatica_PINO\\Van\\2022\\Programación_PINO\\Proyecto_PINO_V2.4\\Pch_Man.ino"
void puertaCH();
#line 1 "C:\\Users\\Administrador\\Desktop\\SAICON_PC\\PROYECTOS\\Puerta automatica_PINO\\Van\\2022\\Programación_PINO\\Proyecto_PINO_V2.4\\Pg_Man.ino"
void puertaG();
#line 1 "C:\\Users\\Administrador\\Desktop\\SAICON_PC\\PROYECTOS\\Puerta automatica_PINO\\Van\\2022\\Programación_PINO\\Proyecto_PINO_V2.4\\bocina_seguridad.ino"
void bocina();
#line 1 "C:\\Users\\Administrador\\Desktop\\SAICON_PC\\PROYECTOS\\Puerta automatica_PINO\\Van\\2022\\Programación_PINO\\Proyecto_PINO_V2.4\\contador.ino"
void contador();
#line 1 "C:\\Users\\Administrador\\Desktop\\SAICON_PC\\PROYECTOS\\Puerta automatica_PINO\\Van\\2022\\Programación_PINO\\Proyecto_PINO_V2.4\\inclinacion_elevacion.ino"
void inclinacion_elevacion();
#line 1 "C:\\Users\\Administrador\\Desktop\\SAICON_PC\\PROYECTOS\\Puerta automatica_PINO\\Van\\2022\\Programación_PINO\\Proyecto_PINO_V2.4\\pch_Auto.ino"
void pch_Auto();
#line 1 "C:\\Users\\Administrador\\Desktop\\SAICON_PC\\PROYECTOS\\Puerta automatica_PINO\\Van\\2022\\Programación_PINO\\Proyecto_PINO_V2.4\\pg_Auto.ino"
void pg_Auto();
#line 53 "C:\\Users\\Administrador\\Desktop\\SAICON_PC\\PROYECTOS\\Puerta automatica_PINO\\Van\\2022\\Programación_PINO\\Proyecto_PINO_V2.4\\Proyecto_PINO_V2.4.ino"
void setup(){
  Serial.begin(9600);
  for(int i=1; i<14; i++){        //Entradas digitales, Control
    pinMode(control[i], INPUT);
  }

  for(int i=1; i<9; i++){         //Salidas digitales, Relevadores
    pinMode(rele[i], OUTPUT);
    digitalWrite(rele[i], HIGH);
  }

  analogWrite(pch, 80);      //Velocidad motor Puerta Chica
  analogWrite(pg, 255);        //Velocidad motor Puerta Granda

  pinMode(s1, INPUT); //sensor 1 de puerta pch
  pinMode(s2, INPUT); //sensor 2 de puerta pch
  pinMode(s3, INPUT); //sensor 3 de puerta pg
  pinMode(s4, INPUT); //sensor 4 de puerta pg
  pinMode(s5, INPUT); //sensor 5 rampa declinada
  pinMode(s6, INPUT); //sensor 6 rampa inclinada
  pinMode(boc, OUTPUT);//bocina 

  automatico=EEPROM.read(0);
  if(automatico==1){            //Si el sistema esta en automatico hace esto
    Serial.print("Automatico activado: "); Serial.println(EEPROM.read(0));
    digitalWrite(boc, HIGH);
  delay(t/2);
  digitalWrite(boc, LOW);
  delay(t/2);
  digitalWrite(boc, HIGH);
  delay(t/2);
  digitalWrite(boc, LOW);
  }

  if(automatico==0){            //Si el sistema esta en manual hace esto
    Serial.print("Automatico Desactivado: "); Serial.println(EEPROM.read(0));
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
}
 
 
void loop(){

  corriente_m(); //Verifica la corriente de los motores en todo momento
  
  if(automatico==0){
  puertaG();//abre y cierra la puerta grande en manual
  puertaCH();//abre y cierra la puerta chicha en manual
  } 

  if(automatico==1){
    pch_Auto(); //abre y cierra la puerta chicha en automatico
    pg_Auto(); //abre y cierra la puerta grande en automatico
  }
 // Serial.println(corrientepg);
  if((digitalRead(s1)==HIGH && digitalRead(s3)==HIGH) || bajar==1 || subir==1 || incli==1 || decli==1){//Rampa
  inclinacion_elevacion();//Rampa
  }
  contador();//si se quedan encendidos se apagan solos
  bocina(); //enciende bocina
  candado();
}

#line 1 "C:\\Users\\Administrador\\Desktop\\SAICON_PC\\PROYECTOS\\Puerta automatica_PINO\\Van\\2022\\Programación_PINO\\Proyecto_PINO_V2.4\\Candado_y_automatico.ino"
void candado(){
  if((digitalRead(control[11])==HIGH&&cont3<50) || corrientepch>=amplimitpch || corrientepg>=amplimitpg){// apaga todo y pone todo en cero
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


#line 1 "C:\\Users\\Administrador\\Desktop\\SAICON_PC\\PROYECTOS\\Puerta automatica_PINO\\Van\\2022\\Programación_PINO\\Proyecto_PINO_V2.4\\Corriente_M.ino"
void corriente_m(){
  currentpg = getCorrientepg(SAMPLESNUMBER);
   currentRMS = 0.707 * currentpg;
   power = 230.0 * currentRMS;
   corrientepg=(currentRMS+currentpg)/2; //Corriente puerta grande
   
   currentpch = getCorrientepch(SAMPLESNUMBER);
   currentRMSpg = 0.707 * currentpch;
   powerpg = 230.0 * currentRMSpg;
   corrientepch=(currentRMSpg+currentpch)/2; //Corriente puerta chica
   
  /* Serial.println("----------------------");   
   Serial.print(corrientepg);
   Serial.print("      ");
   Serial.println(corrientepch); 
   delay(50);*/
}

float getCorrientepg(int samplesNumber)
{
   float voltage;
   float corrienteSum = 0;
   for (int i = 0; i < samplesNumber; i++)
   {
      voltage = analogRead(A0) * 5.0 / 1023.0;
      corrienteSum += (voltage - 2.5) / SENSIBILITY;
   }
   return(corrienteSum / samplesNumber);
}

float getCorrientepch(int samplesNumber)
{
   float voltagepg;
   float corrienteSumpg = 0;
   for (int i = 0; i < samplesNumber; i++)
   {
      voltagepg = analogRead(A1) * 5.0 / 1023.0;
      corrienteSumpg += (voltagepg - 2.5) / SENSIBILITY;
   }
   return(corrienteSumpg / samplesNumber);
}

#line 1 "C:\\Users\\Administrador\\Desktop\\SAICON_PC\\PROYECTOS\\Puerta automatica_PINO\\Van\\2022\\Programación_PINO\\Proyecto_PINO_V2.4\\Pch_Man.ino"
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
  if(apch==1 && digitalRead(s1)==HIGH&&contpch==tspch){//Llega al fin de apertura ch S3
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

#line 1 "C:\\Users\\Administrador\\Desktop\\SAICON_PC\\PROYECTOS\\Puerta automatica_PINO\\Van\\2022\\Programación_PINO\\Proyecto_PINO_V2.4\\Pg_Man.ino"
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

#line 1 "C:\\Users\\Administrador\\Desktop\\SAICON_PC\\PROYECTOS\\Puerta automatica_PINO\\Van\\2022\\Programación_PINO\\Proyecto_PINO_V2.4\\bocina_seguridad.ino"
void bocina(){
  //if(incli>=1 || decli>=1 || subir>=1 || bajar>=1 || apch>=1 || cpch>=1 || apg>=1 || cpg>=1){
  if(apch>=1 || cpch>=1 || apg>=1 || cpg>=1){
    if(cont5==0 || cont5%t_bocina==0){
      intermitente=!intermitente; 
      digitalWrite(boc, intermitente);
      }
      
    cont5++;
    Serial.print("cont5----");
    Serial.println(cont5);
    Serial.println("----------------------");   
   Serial.print(corrientepg);
   Serial.print("      ");
   Serial.println(corrientepch); 
   delay(50);
    /*Serial.print("   ");
    Serial.print(cont5%t_bocina);
    Serial.print("   ");
    Serial.print(intermitente);
    Serial.println("----");*/
  } else{
    digitalWrite(boc, LOW);
    cont5=0;
  }

  /*if(cont5>t3){
    Serial.println("MOTORES apagados por tiempo de uso");
    cont5=0;
    apch=0;
    cpch=0;
    apg=0;
    cpg=0;
    for(int i=1; i<9; i++){         //Salidas digitales, Relevadores y shields motores
    digitalWrite(rele[i], HIGH);
  }
  }*/

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

#line 1 "C:\\Users\\Administrador\\Desktop\\SAICON_PC\\PROYECTOS\\Puerta automatica_PINO\\Van\\2022\\Programación_PINO\\Proyecto_PINO_V2.4\\contador.ino"
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

#line 1 "C:\\Users\\Administrador\\Desktop\\SAICON_PC\\PROYECTOS\\Puerta automatica_PINO\\Van\\2022\\Programación_PINO\\Proyecto_PINO_V2.4\\inclinacion_elevacion.ino"
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

#line 1 "C:\\Users\\Administrador\\Desktop\\SAICON_PC\\PROYECTOS\\Puerta automatica_PINO\\Van\\2022\\Programación_PINO\\Proyecto_PINO_V2.4\\pch_Auto.ino"
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

#line 1 "C:\\Users\\Administrador\\Desktop\\SAICON_PC\\PROYECTOS\\Puerta automatica_PINO\\Van\\2022\\Programación_PINO\\Proyecto_PINO_V2.4\\pg_Auto.ino"
void pg_Auto(){
  //-----*-*-*-*-*-*-------------Apertura de puerta grande---------*-*-*-*-*-*------------------*-*-*-*-*--------
  if(digitalRead(control[1])==HIGH && apg==0 && apch==0 && cpg==0 && digitalRead(s4)==HIGH){ //comienza apertura de pg
    digitalWrite(rele[8],LOW); //Enciende apertura motor PG
    apg=1;
    Serial.println("Comienza pertura de puerta");
    delay(t);
  }

  if(digitalRead(control[1])==HIGH && apg==1 && digitalRead(s3)==LOW && digitalRead(s4)==LOW){ //detiene apertura de puerta
    digitalWrite(rele[8],HIGH); //Apaga apertura motor PG
    apg=0;
    cont5=0;// seguridad de los motores
    Serial.println("detiene apertura de puerta");
    delay(t);
  }
  if(digitalRead(control[1])==HIGH && apg==0 && apch==0 && cpg==0 && digitalRead(s3)==LOW && digitalRead(s4)==LOW){ //continua con apertura de puerta
    digitalWrite(rele[8],LOW); //Enciende apertura motor PG
    apg=1;
    Serial.println("continua con apertura de pg");
    delay(t);
  }
  if(apg==1 && digitalRead(s3)==HIGH){//Llega al fin de apertura pg S3
    apg=0;
    cpg=0;
    cont5=0;// seguridad de los motores
    digitalWrite(rele[8], HIGH);
    Serial.println("puerta abierta, s3");
    delay(t);
  }
//-----*-*-*-*-*-*-------------Cierre de puerta grande---------*-*-*-*-*-*------------------*-*-*-*-*--------

  if(cpch==1 && digitalRead(s4)==LOW && digitalRead(s1)==LOW && cpg==0 && apg==0 && digitalRead(s6)==HIGH){// Comienza cierre de pg
    digitalWrite(rele[7],LOW); //Apaga apertura motor PG
    cpg=1;
    Serial.println("Comienza cierre de puerta");
    delay(t);
  }

  if(digitalRead(control[2])==HIGH && digitalRead(s2)==HIGH && cpch==0 && cpg==3 && digitalRead(s4)==LOW){
    digitalWrite(rele[7],HIGH); //Apaga cierre motor PG
    Serial.println("detiene cierre de puerta");
    delay(t);
  }
    
  if(cpch==0 && cpg==1 && digitalRead(s3)==LOW && digitalRead(s4)==LOW){ //detiene cierre de puerta grande
    digitalWrite(rele[7],HIGH); //Apaga cierre motor PG
    cpg=0;
    cont5=0;// seguridad de los motores
    Serial.println("detiene cierre de puerta");
    delay(t);
  }

  if(cpch==1 && apg==0 && cpg==0 && digitalRead(s3)==LOW && digitalRead(s4)==LOW && digitalRead(s6)==HIGH){ //continua con cierre de puerta grande
    digitalWrite(rele[7],LOW); //Enciende cierre motor PG
    cpg=1;
    Serial.println("continua con cierre de puerta");
    delay(t);
  }
  
  if(digitalRead(control[2])==HIGH && cpch==0 && cpg==0 && apg==0 && digitalRead(s2)==HIGH && digitalRead(s4)==LOW && digitalRead(s6)==HIGH){ //continua con cierre de puerta grande
    digitalWrite(rele[7],LOW); //Enciende cierre motor PG
    cpg=3;
    Serial.println("continua con cierre de puerta");
    delay(t);
  }
  
  if(cpg==3 && digitalRead(s4)==HIGH){//Llega al fin de cierre pg S4
    apg=0;
    cpg=0;
    cont5=0;// seguridad de los motores
    digitalWrite(rele[7], HIGH);
    Serial.println("puerta g cerrada, s4");
    delay(t);
  }
  
  if(apg==1){
    cont4++;
    Serial.println(cont4);
  }
}

