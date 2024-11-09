#define led_blue 10
#define led 13 // pin de conexión del led

String stringDeEntrada = ""; // string donde se almacenaran los datos de entrada

bool stringCompleto = false;  // bandera para comprobar si la cadena de caracteres esta completa

void setup() {
  Serial.begin(9600);
  // declaramos a led como salida
  pinMode(led, OUTPUT);
  pinMode(led_blue, OUTPUT);
  // reservamos 200 bytes para el stringDeEntrada:
  stringDeEntrada.reserve(200);

}

void loop() {

  if (stringCompleto) {

    // le quitamos el ultimo valor al string de entrada
    stringDeEntrada.remove(stringDeEntrada.length() - 1);

    /* comprobamos: si el string de entada es igual a "encender"
      entonces, se enciende el led.Si el string de entada es igual a "apagar"
      entonces, el led se apaga */

    if (stringDeEntrada.equals("ON")) {
      digitalWrite(led_blue, HIGH);
      digitalWrite(led, HIGH);

    } else if (stringDeEntrada.equals("OFF")) {
      digitalWrite(led_blue, LOW);
      digitalWrite(led, LOW);
    }
    //limpiamos el string
    stringDeEntrada = "";
    stringCompleto = false;
  }
}
/*
  SerialEvent ocurre cada vez que llega
  un nuevo dato en el hardware serial RX.
  Esta rutina se ejecuta cada vez que se
  ejecuta void loop(), por lo que el uso de
  pausas dentro del void loop puede retrasar la respuesta.
  Pueden estar disponibles varios bytes de datos.
*/
void serialEvent() {
  while (Serial.available()) {
    // obtenemos el nuevo byte:
    char caracterDeEntrada = (char)Serial.read();
    // añadimos ese dato a stringDeEntrada:
    stringDeEntrada += caracterDeEntrada;

    /* si el carácter entrante es una nueva línea,
      establecemos una bandera para que el ciclo principal
      pueda hacer algo al respecto: */

    if (caracterDeEntrada == '\n') {
      stringCompleto = true;
    }
  }
}