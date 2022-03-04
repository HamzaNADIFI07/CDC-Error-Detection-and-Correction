#include <stdio.h>

#include "repeat.h"
#include "../tests/tests.h"

void encode_repeat() {
  int byte;
  while ((byte = getchar()) != EOF) {
    putchar(byte);
    putchar(byte);
    putchar(byte);
  }
}

unsigned char decode_three_bytes(unsigned char bytes[3]) {
  /* A COMPLETER ET MODIFIER */
  return 0;
}

void decode_repeat() {
  unsigned char bytes[3];
  int byte;
  int fini = 0;
  int i;
  while (! fini) {
    for (i = 0; i < 3 && ! fini; i++) {
      byte = getchar();
      if (byte == EOF)
        fini = 1;
      else
        bytes[i] = byte;
    }
    if (! fini) {
      putchar(decode_three_bytes(bytes));
    }
  }
}
