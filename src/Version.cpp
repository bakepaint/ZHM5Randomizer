#include "src/Version.h"

#include <Windows.h>

#include "src/Pe.h"

namespace hitman_randomizer {

GameVersion getVersion() {
    auto timestamp = PE::getTimestamp();
    if(timestamp == 0x65D43ACA)
        return GameVersion::H3DX12_EGS_WOA;
    return GameVersion::UNK;
}

}
