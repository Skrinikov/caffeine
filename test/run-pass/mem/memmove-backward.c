
#include "caffeine.h"
#include <stdlib.h>
#include <string.h>

char reference[] = "01012345678923456789";
char data[] = "01234567890123456789";

void test(void) {
  memmove(data + 2, data, 10);

  char sym[sizeof(data)];
  caffeine_make_symbolic(sym, sizeof(sym), "data");

  for (size_t i = 0; i < sizeof(data); ++i) {
    caffeine_assume(sym[i] == data[i]);
  }

  for (size_t i = 0; i < sizeof(data); ++i) {
    caffeine_assert(reference[i] == data[i]);
  }
}
