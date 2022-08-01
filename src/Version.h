#ifndef __ZHM5RANDOMIZER_SRC_VERSION_H__
#define __ZHM5RANDOMIZER_SRC_VERSION_H__

namespace hitman_randomizer {

enum class GameVersion {
    H2DX11,
    H2DX12,
    H3DX12_EGS,
    H3DX12_STEAM,
    // No idea who gets this one versus the one above but so far the offsets
    // seem to be exactly the same
    H3DX12_STEAM_ALT,
    UNK
};

GameVersion getVersion();

}

#endif // __ZHM5RANDOMIZER_SRC_VERSION_H__
