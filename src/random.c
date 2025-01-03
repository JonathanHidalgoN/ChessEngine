#include "../include/random.h"
#include <stdint.h>
/*
 * Pseudo random number generator for magics
 * source :
 * https://www.youtube.com/watch?v=JjFYmkUhLN4&list=PLmN0neTso3Jxh8ZIylk74JpwfiWNI76Cs&index=13
 */
unsigned int state = 1804289383;
static unsigned int getRandom32UNumber() {
  unsigned int number = state;
  number ^= number << 13;
  number ^= number >> 17;
  number ^= number << 5;
  state = number;
  return number;
}

static uint64_t getRandom64UNumberMagic() {
  uint64_t n1, n2, n3, n4;
  n1 = (uint64_t)(getRandom32UNumber()) & 0xFFFF;
  n2 = (uint64_t)(getRandom32UNumber()) & 0xFFFF;
  n3 = (uint64_t)(getRandom32UNumber()) & 0xFFFF;
  n4 = (uint64_t)(getRandom32UNumber()) & 0xFFFF;
  return n1 | (n2 << 16) | (n3 << 32) | (n4 << 48);
}

uint64_t getMagicNumberCandidate() {
  return getRandom64UNumberMagic() & getRandom64UNumberMagic() &
         getRandom64UNumberMagic();
}

uint64_t getRandom64UNumber(uint64_t *state) {
  uint64_t x = state[0];
  uint64_t const y = state[1];
  state[0] = y;
  x ^= x << 23;
  x ^= x >> 17;
  x ^= y ^ (y >> 26);
  state[1] = x;
  return x + y;
}
