
const int MAX_GAMMA = 255;

void calculate_gammas(double gamma) {
  for (int n=0; n<=64; n++) {
    gamma_table[n] = 255-pow(n/64.0, gamma) * MAX_GAMMA;
  }
}
