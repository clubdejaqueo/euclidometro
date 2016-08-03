#include <BitBool.h>

const int MAX_STEPS = 16;

const int NUM_VALUES = 3;
const int STEPS = 0;
const int PULSES = 1;
const int DIVISOR = 2;

typedef BitBool<MAX_STEPS> Pattern;

class Channel {
    void build_string(int level);
    int values[3] = {MAX_STEPS,0,1};
    int step;
    int tick;
    //array to hold the output of Bjorklund's Algo
    Pattern pattern;

  public:
    Channel() : tick(0) {
      values_changed();
    }

    bool value() {
      return pattern[step];
    }

    int get_steps() { return values[STEPS]; }
    void clock();
    void set_value(int n, int new_value) {
      values[n] = new_value;
    }

    int get_value(int n) {
      return values[n];
    }

    Pattern& get_pattern() {
      return pattern; 
    }

    void values_changed();

    void debug_grilla();
    void debug_linea();
    void debug_numeros();
};

class Control {
    Channel* channels;
    int num_channels;
    int current_channel;
    int encoder_focus;
  public:
    Control(Channel* channels, int num_channels) : channels(channels), num_channels(num_channels), current_channel(0), encoder_focus(0) {
    }

    void channel_selected(int new_channel);

    void tick();
    void values_changed() {
      get_selected().values_changed();
    }

    void debug_numeros() {
      get_selected().debug_numeros();
    }

    void debug_lineas() {
      for (int c = 0; c < num_channels; c++) {
        channels[c].debug_linea();
      }
    }
    void encoder_changed(int value);

    void button_pushed();
    
    Channel& get_selected() {
      return channels[current_channel];
    }
};
