#include "ZHM5Randomizer/src/Version.h"

#include <Windows.h>

#include "ZHM5Randomizer/src/Pe.h"

namespace hitman_randomizer {

GameVersion getVersion() {
    auto timestamp = PE::getTimestamp();
    if(timestamp == 0x63C6130E)
        return GameVersion::H3DX12_EGS_WOA;
    if(timestamp == 0x63C7E952)
        return GameVersion::H3DX12_STEAM_WOA;
    return GameVersion::UNK;
}

}
