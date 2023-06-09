#ifndef __ZHM5RANDOMIZER_SRC_VERSION_H__
#define __ZHM5RANDOMIZER_SRC_VERSION_H__

namespace hitman_randomizer {

enum class GameVersion {
    H3DX12_EGS_WOA,
    H3DX12_STEAM_WOA,
    H3DX12_STEAM_WOA_VARIANT,
    UNK
};

GameVersion getVersion();

}

#endif // __ZHM5RANDOMIZER_SRC_VERSION_H__
