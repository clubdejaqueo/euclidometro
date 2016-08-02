const byte PROGMEM numeros[] = {
  0xEE, 0xAA, 0xAA, 0xAA, 0xEE,
  0x8E, 0x8A, 0x8A, 0x8A, 0x8E,
  0xEE, 0x8A, 0xEA, 0x2A, 0xEE,
  0xEE, 0x8A, 0xEA, 0x8A, 0xEE,
  0xAE, 0xAA, 0xEA, 0x8A, 0x8E,
  0xEE, 0x2A, 0xEA, 0x8A, 0xEE,
  0xEE, 0x2A, 0xEA, 0xAA, 0xEE,
  0xEE, 0x8A, 0x8A, 0x8A, 0x8E,
  0xEE, 0xAA, 0xEA, 0xAA, 0xEE,
  0xEE, 0xAA, 0xEA, 0x8A, 0x8E,
  0xE8, 0xA8, 0xA8, 0xA8, 0xE8,
  0x88, 0x88, 0x88, 0x88, 0x88,
  0xE8, 0x88, 0xE8, 0x28, 0xE8,
  0xE8, 0x88, 0xE8, 0x88, 0xE8,
  0xA8, 0xA8, 0xE8, 0x88, 0x88,
  0xE8, 0x28, 0xE8, 0x88, 0xE8,
  0xE8, 0x28, 0xE8, 0xA8, 0xE8,
  0xE8, 0x88, 0x88, 0x88, 0x88,
  0xE8, 0xA8, 0xE8, 0xA8, 0xE8,
  0xE8, 0xA8, 0xE8, 0x88, 0x88,
  0xEE, 0xA8, 0xAE, 0xA2, 0xEE,
  0x8E, 0x88, 0x8E, 0x82, 0x8E,
  0xEE, 0x88, 0xEE, 0x22, 0xEE,
  0xEE, 0x88, 0xEE, 0x82, 0xEE,
  0xAE, 0xA8, 0xEE, 0x82, 0x8E,
  0xEE, 0x28, 0xEE, 0x82, 0xEE,
  0xEE, 0x28, 0xEE, 0xA2, 0xEE,
  0xEE, 0x88, 0x8E, 0x82, 0x8E,
  0xEE, 0xA8, 0xEE, 0xA2, 0xEE,
  0xEE, 0xA8, 0xEE, 0x82, 0x8E,
  0xEE, 0xA8, 0xAE, 0xA8, 0xEE,
  0x8E, 0x88, 0x8E, 0x88, 0x8E,
  0xEE, 0x88, 0xEE, 0x28, 0xEE,
  0xEE, 0x88, 0xEE, 0x88, 0xEE,
  0xAE, 0xA8, 0xEE, 0x88, 0x8E,
  0xEE, 0x28, 0xEE, 0x88, 0xEE,
  0xEE, 0x28, 0xEE, 0xA8, 0xEE,
  0xEE, 0x88, 0x8E, 0x88, 0x8E,
  0xEE, 0xA8, 0xEE, 0xA8, 0xEE,
  0xEE, 0xA8, 0xEE, 0x88, 0x8E,
  0xEA, 0xAA, 0xAE, 0xA8, 0xE8,
  0x8A, 0x8A, 0x8E, 0x88, 0x88,
  0xEA, 0x8A, 0xEE, 0x28, 0xE8,
  0xEA, 0x8A, 0xEE, 0x88, 0xE8,
  0xAA, 0xAA, 0xEE, 0x88, 0x88,
  0xEA, 0x2A, 0xEE, 0x88, 0xE8,
  0xEA, 0x2A, 0xEE, 0xA8, 0xE8,
  0xEA, 0x8A, 0x8E, 0x88, 0x88,
  0xEA, 0xAA, 0xEE, 0xA8, 0xE8,
  0xEA, 0xAA, 0xEE, 0x88, 0x88,
  0xEE, 0xA2, 0xAE, 0xA8, 0xEE,
  0x8E, 0x82, 0x8E, 0x88, 0x8E,
  0xEE, 0x82, 0xEE, 0x28, 0xEE,
  0xEE, 0x82, 0xEE, 0x88, 0xEE,
  0xAE, 0xA2, 0xEE, 0x88, 0x8E,
  0xEE, 0x22, 0xEE, 0x88, 0xEE,
  0xEE, 0x22, 0xEE, 0xA8, 0xEE,
  0xEE, 0x82, 0x8E, 0x88, 0x8E,
  0xEE, 0xA2, 0xEE, 0xA8, 0xEE,
  0xEE, 0xA2, 0xEE, 0x88, 0x8E,
  0xEE, 0xA2, 0xAE, 0xAA, 0xEE,
  0x8E, 0x82, 0x8E, 0x8A, 0x8E,
  0xEE, 0x82, 0xEE, 0x2A, 0xEE,
  0xEE, 0x82, 0xEE, 0x8A, 0xEE,
  0xAE, 0xA2, 0xEE, 0x8A, 0x8E,
};

void debug_numeros () {
  for (int i = 0; i < 5; i++) {
    byte q = pgm_read_byte(numeros + steps * 5 + i);
    for (int b = 0; b < 8; b++) {
      Serial.print(bitRead(q, b) ? "O" : " ");
    }
    Serial.print("    ");
    q = pgm_read_byte(numeros + pulses * 5 + i);
    for (int b = 0; b < 8; b++) {
      Serial.print(bitRead(q, b) ? "O" : " ");
    }
    Serial.println();
  }
}
