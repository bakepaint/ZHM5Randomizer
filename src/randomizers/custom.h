#ifndef __ZHM5RANDOMIZER_SRC_RANDOMIZERS_H__
#define __ZHM5RANDOMIZER_SRC_RANDOMIZERS_H__

#include <queue>
#include <random>
#include <type_traits>
#include <unordered_map>
#include <vector>

#include "ZHM5Randomizer/src/Config.h"
#include "ZHM5Randomizer/src/RNG.h"
#include "ZHM5Randomizer/src/Repository.h"
#include "ZHM5Randomizer/src/Scenario.h"
#include "ZHM5Randomizer/src/randomizers/Randomizer.h"
#include "ZHM5Randomizer/src/randomizers/world/default.h"

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