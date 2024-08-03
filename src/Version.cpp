#include "src/Version.h"

#include <Windows.h>

#include "src/Pe.h"

namespace hitman_randomizer {

GameVersion getVersion() {
    auto timestamp = PE::getTimestamp();
    if(timestamp == 0x666298F6)
        return GameVersion::H3DX12_EGS_WOA;
    if(timestamp == 0x667E6CAA)
        return GameVersion::H3DX12_STEAM_WOA;
    if(timestamp == 0x667E69CF)
        return GameVersion::H3DX12_STEAM_WOA_VARIANT;

    return GameVersion::UNK;
}

}
