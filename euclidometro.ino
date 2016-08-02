#include <BitBool.h>
#include <PlainENCi.h>
#include "Channel.h"

int ledPin[] = {10, 9, 11};

/*
  int selectedLed = 0;
  int16_t pwmValues[] = {0, 0, 0};
  int16_t counter;
*/
int16_t _maxCounts = MAX_STEPS;
int16_t _minCounts = 1;
int16_t lastCount = 0;
byte gamma_table[65];

const int NUM_CHANNELS = 6;
Channel channels[NUM_CHANNELS];
Control control(channels, NUM_CHANNELS);


class Clock {
    unsigned long tick;
    unsigned long last_tick;
    void (*clock_handler)(void);
  public:
    Clock(int bpm) {
      tick = (60L * 1000L * 1000L) / bpm;
      last_tick = micros();
      clock_handler = NULL;
    }

    void setHandleClock(void(*fptr)(void)) {
      clock_handler = fptr;
    }

    void loop() {
      unsigned long now = micros();
      if ((now - last_tick) > tick) {
        last_tick = now;
        if (clock_handler) {
          clock_handler();
        }
      }
    }
};

Clock clock(120 * 24);

void tick() {
  control.tick();

  Serial.write(27);
  Serial.print("[H");     // cursor to home command

  control.debug_numeros();
  control.debug_lineas();
}

void serialEvent() {
  while (Serial.available()) {
    char inChar = (char)Serial.read();
    if (inChar >= '1' && inChar <= '6') {
      control.channel_selected(inChar - '1');
    }
  }
}

void setup() {
  clock.setHandleClock(tick);
  Serial.begin (115200);
  Serial.write(27);       // ESC command
  Serial.print("[2J");    // clear screen command
  calculate_gammas(2.5);
  ENC.InitializeENC(0, 1, 2, &PORTC, ENC_ONE_DET_PER_PULSE);
  ENC.SetBooster(50, 3);
  control.channel_selected(0);
}

void Control::channel_selected(int new_channel) {
  current_channel = new_channel;
  encoder_focus = 0;
  ENC.SetCounter(channels[current_channel].get_steps(), 1, MAX_STEPS);
}

void Control::button_pushed() {
  int _minCounts, _maxCounts;
  
  encoder_focus = (++encoder_focus) % NUM_VALUES;

  if (encoder_focus == 0) {
    _minCounts = 1;
    _maxCounts = MAX_STEPS;
    // n achica k si este lo supera
    /* FIXME
    if (pwmValues[1] > pwmValues[0]) {
      pwmValues[1] = pwmValues[0];
    }*/
  }

  if (encoder_focus == 1) {
    // k nunca puede superar n
    _minCounts = 0;
    _maxCounts = channels[current_channel].get_steps();
  }

  if (encoder_focus == 2) {
    // divisor de velocidad
    _minCounts = 1;
    _maxCounts = 24;
  }
  int val = channels[current_channel].get_value(encoder_focus);
  ENC.SetCounter(val, _minCounts, _maxCounts);
  Serial.println(val);
  
  lastCount = 256;
  /*
  for (int n = 0; n < 3; n++) {
    int val = (selectedLed == n) ? 0 : 255;
    analogWrite(ledPin[n], val);
  }
  */
}

void Control::encoder_changed(int value) {
  channels[current_channel].set_value(encoder_focus, value);
  control.values_changed();
}

void loop() {

  clock.loop();

  if (ENC.PushButtonState() == ENC_BTN_UP) {
    control.button_pushed();
    while (ENC.PushButtonState() == ENC_BTN_UP) {
    }
  }

  int counter = ENC.GetCounter();
  if (lastCount != counter) {
    control.encoder_changed(counter);
    lastCount = counter;
  }
}
