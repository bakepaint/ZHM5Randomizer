#ifndef __ZHM5RANDOMIZER_SRC_VERSION_H__
#define __ZHM5RANDOMIZER_SRC_VERSION_H__

namespace hitman_randomizer {

enum class GameVersion { H2DX11, H2DX12, H3DX12_EGS, H3DX12_STEAM, UNK };

GameVersion getVersion();

}

#endif // __ZHM5RANDOMIZER_SRC_VERSION_H__
