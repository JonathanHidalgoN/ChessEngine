#include "../include/random.h"
#include <stdint.h>
/*
 * Pseudo random number generator
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

uint64_t getRandom64UNumber() {
  static const uint64_t multiplier = 6364136223846793005ULL;
  static const uint64_t increment = 1442695040888963407ULL;
  static uint64_t seed = 0x5555555555555555ULL; // Starting seed

  seed = seed * multiplier + increment;
  return seed;
}
