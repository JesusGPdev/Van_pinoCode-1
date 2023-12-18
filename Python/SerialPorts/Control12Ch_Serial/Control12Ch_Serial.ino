String input_String;
int outputs[13] = {150, A4, A3, A2, A1, 5, 6, 7, 8, 9, 10, 11, 12};

void setup() {
  Serial.begin(115200);
  for (int out = 1; out <= 12; out++) {
    pinMode(outputs[out], OUTPUT);
  }
}

void loop() {
  delay(100);
  Serial_Event();
}

void Serial_Event() {
  int number_extracted = 255;
  String btn_pressed = "BTN_";
  int time_button = 500;

  while (Serial.available()) {
    char inputChar = Serial.read();
    input_String += inputChar;
    number_extracted = extractNumber(input_String.c_str());
  }
  Serial.println(number_extracted);
  digitalWrite(outputs[number_extracted], HIGH);
  delay(time_button);
  digitalWrite(outputs[number_extracted], LOW);
  // for(int i=1; i<=12 ; i++){
  // // Check for button presses
  //   String btn_off = "BTN_OFF_" + String(i);

  //   if (input_String.indexOf(btn_pressed) >= 0) {
  //     Serial.println(number_extracted);
  //     digitalWrite(outputs[number_extracted], HIGH);
  //     delay(time_button);
  //     digitalWrite(outputs[number_extracted], LOW);
  //   }
  // }

  input_String = "";
}

int extractNumber(const char *str) {
  int result = 0;
  while (*str) {
    if (isdigit(*str)) {
      result = result * 10 + (*str - '0');  // Convert character to integer
    }
    str++;
  }
  return result;
}
