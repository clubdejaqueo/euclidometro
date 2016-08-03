int RCLK1_Pin = A5;  //pin 12 on the 75HC595
int RCLK2_Pin = 3; //pin 12 on the other 75HC595

//How many of the shift registers - change this
#define number_of_74hc595s 1

//do not touch
#define numOfRegisterPins number_of_74hc595s * 8

boolean registers[numOfRegisterPins];

void matrix_setup() {
  pinMode(SER_Pin, OUTPUT);
  pinMode(RCLK1_Pin, OUTPUT);
  pinMode(RCLK2_Pin, OUTPUT);
  pinMode(SRCLK_Pin, OUTPUT);

  for (int x = 5; x <= 13; x++) {
    pinMode(x, OUTPUT);
  }

  clearRegisters();
  writeRegisters(true);
  writeRegisters(false);
}

void clearRegisters() {
  for (int i = numOfRegisterPins - 1; i >=  0; i--) {
    registers[i] = LOW;
  }
}

void writeRegisters(bool red) {
  int RCLK_Pin;

  if (red) {
    RCLK_Pin = RCLK1_Pin;
  } else {
    RCLK_Pin = RCLK2_Pin;
  }

  digitalWrite(RCLK_Pin, LOW);
  for (int i = numOfRegisterPins - 1; i >=  0; i--) {
    digitalWrite(SRCLK_Pin, LOW);
    int val = registers[i];
    digitalWrite(SER_Pin, val);
    digitalWrite(SRCLK_Pin, HIGH);
  }
  digitalWrite(RCLK_Pin, HIGH);

  if (!red) {
    RCLK_Pin = RCLK1_Pin;
  } else {
    RCLK_Pin = RCLK2_Pin;
  }

  digitalWrite(RCLK_Pin, LOW);
  for (int i = numOfRegisterPins - 1; i >=  0; i--) {
    digitalWrite(SRCLK_Pin, LOW);
    int val = LOW;
    digitalWrite(SER_Pin, val);
    digitalWrite(SRCLK_Pin, HIGH);
  }
  digitalWrite(RCLK_Pin, HIGH);
}

void setRegisterPin(int index, int value) {
  registers[index] = value;
}

int line_pins[] = { 5, 6, 13, 8, 9, 10, 11, 12 };

int matrix_value;
int matrix_color;

void matrix_set(int value, int color) {
  matrix_value = value;
  matrix_color = color;
}

void matrix_loop() {
  for (int x = 0; x < 8; x++) {
    clearRegisters();

    writeRegisters(true);
    writeRegisters(false);

    for (int j = 0; j < 8; j++) {
      digitalWrite(line_pins[j], (x == j) ? HIGH : LOW);
    }
    byte b = get_numero(matrix_value, x);
    for (int y = 0; y < 8; y++) {
      setRegisterPin(y, bitRead(b, y));
    }
    if (matrix_color != 2) {
      writeRegisters(false);
    }
    if (matrix_color != 0) {
      writeRegisters(true);
    }
  }

}
