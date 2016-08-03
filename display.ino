int SER_Pin = 4;   //pin 14 on the 75HC595
int RCLK3_Pin = A4;  //pin 12 on the 75HC595
int SRCLK_Pin = 2; //pin 11 on the 75HC595

void display_setup() {
  pinMode(SER_Pin, OUTPUT);
  pinMode(RCLK3_Pin, OUTPUT);
  pinMode(SRCLK_Pin, OUTPUT);
}

void display_pattern(Pattern& bits) {
  digitalWrite(RCLK3_Pin, LOW);
  for ( auto bit : bits ) {
    digitalWrite(SRCLK_Pin, LOW);
    digitalWrite(SER_Pin, bit ? HIGH : LOW);
    digitalWrite(SRCLK_Pin, HIGH);
  }
  digitalWrite(RCLK3_Pin, HIGH);
}
