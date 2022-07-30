#include "ZHM5Randomizer/src/Version.h"

#include <Windows.h>

#include "ZHM5Randomizer/src/Pe.h"

namespace hitman_randomizer {

GameVersion getVersion() {
    auto timestamp = PE::getTimestamp();
    if(timestamp == 0x62C641F4)
        return GameVersion::H3DX12_EGS;
    if(timestamp == 0x62C6418B)
        return GameVersion::H3DX12_STEAM;
    return GameVersion::UNK;
}

}
