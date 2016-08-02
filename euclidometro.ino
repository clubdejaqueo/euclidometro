#include <PlainENCi.h>

const int max_steps = 16;

int ledPin[] = {10, 9, 11};
int selectedLed = 0;
int16_t pwmValues[] = {0, 0, 0};
int16_t counter;
int16_t _maxCounts = max_steps;
int16_t _minCounts = 1;
byte gamma_table[65];


void setup() {
  Serial.begin (115200);
  calculate_gammas(2.5);
  ENC.InitializeENC(0, 1, 2, &PORTC, ENC_ONE_DET_PER_PULSE);
  ENC.SetBooster(50, 3);
  ENC.SetCounter(pwmValues[selectedLed], _minCounts, _maxCounts);
  counter = ENC.GetCounter();
  Serial.println(counter, DEC);
}

void loop() {
  static int16_t lastCount = 0;
  if (ENC.PushButtonState() == ENC_BTN_UP) {
    selectedLed = (++selectedLed) % 2;

    if (selectedLed == 1) {
      // k nunca puede superar n
      _minCounts = 0;
      _maxCounts = pwmValues[0];
    }

    if (selectedLed == 0) {
      _minCounts = 1;
      _maxCounts = max_steps;
      // n achica k si este lo supera
      if (pwmValues[1] > pwmValues[0]) {
        pwmValues[1] = pwmValues[0];
      }
    }

    ENC.SetCounter(pwmValues[selectedLed], _minCounts, _maxCounts);
    lastCount = 256;
    for (int n = 0; n < 3; n++) {
      int val = (selectedLed == n) ? 0 : 255;
      analogWrite(ledPin[n], val);
    }
    while (ENC.PushButtonState() == ENC_BTN_UP) {
    }
  }
  counter = ENC.GetCounter();

  if (lastCount != counter) {
    pwmValues[selectedLed] = counter;
    for (int n = 0; n < 3; n++) {
      int val = (selectedLed == n) ? gamma_table[pwmValues[n]] : 255;
      analogWrite(ledPin[n], val);
    }
    compute_bitmap (pwmValues[0], pwmValues[1]);
    debug_bjorklund_grilla ();
    Serial.println();
    debug_numeros ();
    debug_bjorklund_linea ();

    lastCount = counter;
  }
}
