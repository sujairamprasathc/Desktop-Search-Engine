#include "hash.h"

unsigned long long int power(unsigned long long int x, unsigned long long int y,
                             unsigned long long int p) {
  unsigned long long int value = 1;
  x = x % p;
  while (y > 0) {
    if (y & 1) {
      value = (value * x) % p;
    }

    y >>= 1;
    x = (x * x) % p;
  }
  return value;
}

namespace indexer {

unsigned int hash(std::string str) {
  size_t hash_value = 0, prime = 1000000007;

  for (unsigned int i = 0; i < str.length(); ++i) {
    hash_value += (str[i] * power(128, i, prime)) % prime;
  }

  return hash_value % prime;
}

}  // namespace indexer
