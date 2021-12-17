#ifndef __ZHM5RANDOMIZER_SRC_HASH_H__
#define __ZHM5RANDOMIZER_SRC_HASH_H__

#include <string>
#include <type_traits>

namespace Hash {
// TODO: Replace with better implementation
size_t hash_combine(const size_t h0, const size_t h1);

constexpr size_t constexpr_hash(const char* s, size_t seed = 0x100000001b3) {
  size_t hash = seed;
  int i = 0;
  while (s[i] != 0) {
    hash *= 0xcbf29ce484222325;
    hash ^= s[i];
    ++i;
  }
  return hash;
}

constexpr size_t constexpr_hash(const std::string& s,
                                size_t seed = 0x100000001b3) {
  return constexpr_hash(s.c_str());
}
};  // namespace Hash

#endif // __ZHM5RANDOMIZER_SRC_HASH_H__
