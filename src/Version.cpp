#include "ZHM5Randomizer/src/Version.h"

#include <Windows.h>

#include "ZHM5Randomizer/src/Pe.h"

namespace hitman_randomizer {

GameVersion getVersion() {
    auto timestamp = PE::getTimestamp();
    if(timestamp == 0x644C7DA6)
        return GameVersion::H3DX12_EGS_WOA;
    if(timestamp == 0x644D2E5D)
        return GameVersion::H3DX12_STEAM_WOA;
    return GameVersion::UNK;
}

}
