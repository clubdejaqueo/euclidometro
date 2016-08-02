/*Bjorklund Working!

  Arduino sketch to run Bjorklund's algorithm based on input of x steps and y pulses.
  The time taken for the function to run will be measured and displayed.

  Based on : https://ics-web.sns.ornl.gov/timing/Rep-Rate%20Tech%20Note.pdf
  and: http://aatpm.com/banff.pdf

  NoisyLittleBugger - October 18 2014
  From my project to build a Bjorklundian sequencer :P
  https://stimresp.wordpress.com/bjorklund/

*/

#include <Arduino.h>
#include "channel.h"

byte remainder[64]; //Seems to conflict with TeensyArduino when declared globally. However it's location does not interfere with operations. Move it inside the function if it misbehaves.
byte count[64];
int level;
int stepstatus = 0;

void Channel::clock() {
  tick = (tick + 1) % values[DIVISOR];
  if (tick == 0) {
    step = (step + 1) % values[STEPS];
  }
}

void Channel::debug_linea() {
  for (int i = 0; i < values[STEPS]; i++) {
    if (i == step) {
      Serial.print(pattern[i] ? "+" : "O");
    } else {
      Serial.print(pattern[i] ? "-" : "o");
    }
  }

  Serial.print(" n=");
  Serial.print(values[STEPS]);
  Serial.print(", k=");
  Serial.print(values[PULSES]);
  Serial.print(", div=");
  Serial.print(values[DIVISOR]);
  Serial.println("         ");
}

void Channel::debug_grilla() {
  for (int i = 0; i < values[STEPS]; i++) {
    Serial.print(pattern[i] ? "-" : "O");
    if ((i % 8) == 0) {
      Serial.println();
    }
  }

  Serial.print(" n=");
  Serial.print(values[STEPS]);
  Serial.print(", k=");
  Serial.print(values[PULSES]);
  Serial.print(", div=");
  Serial.print(values[DIVISOR]);
  Serial.println("         ");
}


//Bjorklund accessory function to build the output..
void Channel::build_string (int level)  {
  if (level == -1) {
    pattern[values[STEPS] - 1 - stepstatus] = true; //insert 0 into array
    stepstatus = stepstatus + 1;  //move to next
  }
  else if (level == -2)  {
    pattern[values[STEPS] - 1 - stepstatus] = false; //insert 1 into array
    stepstatus = stepstatus + 1;  //move to next
  }
  else {
    for (int i = 0; i < count[level]; i++)
      build_string(level - 1);
    if (remainder[level] != 0)
      build_string(level - 2);
  }
}

//Here's where the magic happens...
void Channel::values_changed()  {
  int num_slots = values[STEPS];
  int num_pulses = values[PULSES];
  if (num_pulses > num_slots) {
    num_pulses = num_slots;
  }
  int divisor = num_slots - num_pulses;
  values[STEPS] = num_slots;
  values[PULSES] = num_pulses;
  remainder[0] = num_pulses;
  level = 0;
  do {
    count[level] = divisor / remainder[level];
    remainder[level + 1] = divisor % remainder[level];
    divisor = remainder[level];
    level = level + 1;
  }
  while (remainder[level] > 1);

  count[level] = divisor;
  stepstatus = 0;
  build_string (level);
}


void Control::tick() {
  for (int c = 0; c < num_channels; c++) {
    channels[c].clock();
  }
}

