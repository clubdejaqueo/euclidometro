/*Bjorklund Working!

  Arduino sketch to run Bjorklund's algorithm based on input of x steps and y pulses.
  The time taken for the function to run will be measured and displayed.

  Based on : https://ics-web.sns.ornl.gov/timing/Rep-Rate%20Tech%20Note.pdf
  and: http://aatpm.com/banff.pdf

  NoisyLittleBugger - October 18 2014
  From my project to build a Bjorklundian sequencer :P
  https://stimresp.wordpress.com/bjorklund/

*/

//Enter the steps/pulses here:

byte remainder[64]; //Seems to conflict with TeensyArduino when declared globally. However it's location does not interfere with operations. Move it inside the function if it misbehaves.
byte count[64];
int level;
bool pattern[64];
int stepstatus = 0;
int steps, pulses;

//2D array to hold the output of Bjorklund's Algo
bool trackArray[64];

void debug_bjorklund_linea() {
      for (int i = steps - 1; i >= 0 ; i--) {
        Serial.print(trackArray[i] ? "." : "X");
      }
      
      Serial.print(" n=");
      Serial.print(steps);
      Serial.print(", k=");
      Serial.print(pulses);
      Serial.println();
}

void debug_bjorklund_grilla() {
      Serial.write("\n\n\n\n\n\n\n\n\n\n");

      // Read from the TARGET array to confirm it has been populated correctly. Output is reversed to align with Toussaint's paper.
      for (int i = steps - 1; i >= 0 ; i--) {
        Serial.print(trackArray[i] ? "." : "X");
        if ((i%8) == 0) {
          Serial.println();
        }
      }
      
      Serial.print(" n=");
      Serial.print(steps);
      Serial.print(", k=");
      Serial.print(pulses);
      Serial.println();

}

//Here's where the magic happens...
void compute_bitmap (int num_slots, int num_pulses)  {
  if (num_pulses > num_slots) {
    num_pulses = num_slots;
  }
  int divisor = num_slots - num_pulses;
  steps = num_slots; pulses = num_pulses;
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

//Bjorklund accessory function to build the output..
void build_string (int level)  {
  if (level == -1) {

    //Serial.println('0'); // Debug
    trackArray[stepstatus] = true; //insert 0 into array
    stepstatus = stepstatus + 1;  //move to next
  }
  else if (level == -2)  {

    //Serial.println('1');  // Debug
    trackArray[stepstatus] = false; //insert 1 into array
    stepstatus = stepstatus + 1;  //move to next
  }
  else {
    for (int i = 0; i < count[level]; i++)
      build_string(level - 1);
    if (remainder[level] != 0)
      build_string(level - 2);
  }

}


