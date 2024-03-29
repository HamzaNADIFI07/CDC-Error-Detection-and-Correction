#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "lib/channel.h"

int main(int argc, char **argv) {
  int byte;
  float proba;
  char *endptr;
  if (argc < 2) {
    fprintf(stderr, "Usage: %s proba\n\nproba: Probability of error (between 0 and 1)\n", argv[0]);
    exit(1);
  }
  srand(time(NULL));

  proba = strtod(argv[1], &endptr);
  if (*endptr!=0 || proba < 0 || proba > 1) {
    fprintf(stderr, "ERROR: the argument must be a probability (between 0 and 1).\n       Note that the decimal separator is the dot.\n");
    exit(1);
  }

  while ((byte = getchar()) != EOF) {
    putchar(cbssm(byte, proba));
  }

  return 0;
}
