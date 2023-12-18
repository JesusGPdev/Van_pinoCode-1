#include <EEPROM.h>
//--------- Setup
int control[13]={75,32,33,22,23,25,24,26,27,28,29,30,31}; //Entradas de control remoto
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
int tspch=10; //Tiempo espera cuando el motor de la pch llega a los extremos
int contpch=0; //contador de tiempo para la variable tspch
int tspg=10; //Tiempo espera cuando el motor de la pg llega a los extremos
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
// //----------------------------Medidor de corriente---------------------------------------------------------
// float amplimitpch=50; //0.7 
// float amplimitpg=50;  //0.9
// float SENSIBILITY = 0.185;   // Modelo 5A
// int SAMPLESNUMBER = 200;

// float currentpg=0;          //Piston Pg
// float currentRMS=0;       //Piston Pg
// float power=0;            //Piston Pg
// float corrientepg=0;        //Piston Pg

// float currentpch=0;          //Piston Pch
// float currentRMSpg=0;       //Piston Pch
// float powerpg=0;            //Piston Pch
// float corrientepch=0;        //Piston Pch
//-------------------------------------------------------------------------------------

void setup(){
  Serial.begin(115200);
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
    delay(t);
    digitalWrite(boc, LOW);
    delay(t);
    digitalWrite(boc, HIGH);
    delay(t);
    digitalWrite(boc, LOW);
  }

  if(automatico==0){            //Si el sistema esta en manual hace esto
    Serial.print("Automatico Desactivado: "); Serial.println(EEPROM.read(0));
    digitalWrite(boc, HIGH);
    delay(t);
    digitalWrite(boc, LOW);
    delay(t);
    digitalWrite(boc, HIGH);
    delay(t);
    digitalWrite(boc, LOW);
    delay(t);
    digitalWrite(boc, HIGH);
    delay(t);
    digitalWrite(boc, LOW);
  }
}
 
 
void loop(){

  // corriente_m(); //Verifica la corriente de los motores en todo momento
  
  if(automatico==0){
    puertaG();//abre y cierra la puerta grande en manual
    puertaCH();//abre y cierra la puerta chicha en manual
  } 

  if(automatico==1){
    pch_Auto(); //abre y cierra la puerta chicha en automatico
    pg_Auto(); //abre y cierra la puerta grande en automatico
  }
  if((digitalRead(s1)==HIGH && digitalRead(s3)==HIGH) || bajar==1 || subir==1 || incli==1 || decli==1){//Rampa
    inclinacion_elevacion();//Rampa
  }
  contador();//si se quedan encendidos se apagan solos
  bocina(); //enciende bocina
  candado();
}
