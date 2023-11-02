#ifndef __ZHM5RANDOMIZER_SRC_RANDOMIZERS_H__
#define __ZHM5RANDOMIZER_SRC_RANDOMIZERS_H__

#include <queue>
#include <random>
#include <type_traits>
#include <unordered_map>
#include <vector>

#include "src/Config.h"
#include "src/RNG.h"
#include "src/Repository.h"
#include "src/Scenario.h"
#include "src/randomizers/Randomizer.h"
#include "src/randomizers/world/default.h"

namespace hitman_randomizer {

template<typename Iter, typename RandomGenerator>
Iter select_randomly(Iter start, Iter end, RandomGenerator& g) {
    std::uniform_int_distribution<> dis(0, std::distance(start, end) - 1);
    std::advance(start, dis(g));
    return start;
}

template<typename Iter>
Iter select_randomly(Iter start, Iter end) {
    return select_randomly(start, end, *RNG::inst().getEngine());
}

}  // namespace hitman_randomizer

#endif  // __ZHM5RANDOMIZER_SRC_RANDOMIZERS_H__