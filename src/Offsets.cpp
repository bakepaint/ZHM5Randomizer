#include "ZHM5Randomizer/src/Offsets.h"

#include <Windows.h>

#include <filesystem>
#include <format>

#include "ZHM5Randomizer/src/Pe.h"
#include "ZHM5Randomizer/src/SigScanner.h"
#include "ZHM5Randomizer/src/Signatures.h"

namespace hitman_randomizer {

[[noreturn]] void offsetSearchFailed() {
    MessageBoxA(NULL, "Signature scanning failed. The current game version might not be supported.", "", NULL);
    ExitProcess(0);
}

void* getOffsetByName(const std::string& name) {
    SigScanner scanner;
    auto off = scanner.find(Signatures::locators[name].signature) + Signatures::locators[name].offset;
    if(off < 0)
        offsetSearchFailed();
    return reinterpret_cast<void*>(off);
}

// TODO: Reintroduce signature scanning here. It was previously removed because of major
// signature changed introduced with Hitman update 3.30. (Inlining, NPC/WorldItem spawn
// merge). If the new layout turns out to be stable, sig scanning should be reintroduced.
GameOffsets::GameOffsets() {
    switch(getVersion()) {
    case GameVersion::H3DX12_EGS: {
        // Hitman 3 3.110.1 EGS offsets
        offsets.pPushItem0 = reinterpret_cast<void*>(0x140dd69a0);
        offsets.pPushItem1 = reinterpret_cast<void*>(0x140dd6f90);
        offsets.pPushHeroInventoryDetour = reinterpret_cast<void*>(0x14080b2b3);
        offsets.pPushNPCInventoryDetour = reinterpret_cast<void*>(0x140119e41);
        offsets.pPushStashInventoryDetour = reinterpret_cast<void*>(0x140270974);
        offsets.pPushWorldInventoryDetour = reinterpret_cast<void*>(0x140dd0fca);
        offsets.pZEntitySceneContext_LoadScene = reinterpret_cast<void**>(0x141d5da90);
    } break;
    case GameVersion::H3DX12_STEAM: {
        // Hitman 3 3.110.1 Steam offsets
        offsets.pPushItem0 = reinterpret_cast<void*>(0x140dd5a90);
        offsets.pPushItem1 = reinterpret_cast<void*>(0x140dd6080);
        offsets.pPushHeroInventoryDetour = reinterpret_cast<void*>(0x14080afe3);
        offsets.pPushNPCInventoryDetour = reinterpret_cast<void*>(0x140119b81);
        offsets.pPushStashInventoryDetour = reinterpret_cast<void*>(0x1402706b4);
        offsets.pPushWorldInventoryDetour = reinterpret_cast<void*>(0x140dd00ba);
        offsets.pZEntitySceneContext_LoadScene = reinterpret_cast<void**>(0x141d62de0);
    } break;    

    case GameVersion::H2DX12:
    case GameVersion::H2DX11:
        // TODO: H2 Specific error message
    default:
        MessageBoxA(NULL,
                    std::format("Incompatible client version detected. Please update to the latest "
                                "client release.\n\nPE timestamp: {:X}",
                                PE::getTimestamp())
                    .c_str(),
                    "Incompatible Client Version", NULL);
        ExitProcess(0);
    }
}

const GameOffsets* GameOffsets::instance() {
    static GameOffsets instance;
    return &instance;
}

void* GameOffsets::getPushItem0() const {
    return offsets.pPushItem0;
}
void* GameOffsets::getPushItem1() const {
    return offsets.pPushItem1;
}
void* GameOffsets::getPushWorldInventoryDetour() const {
    return offsets.pPushWorldInventoryDetour;
}
void* GameOffsets::getPushNPCInventoryDetour() const {
    return offsets.pPushNPCInventoryDetour;
}
void* GameOffsets::getPushHeroInventoryDetour() const {
    return offsets.pPushHeroInventoryDetour;
}
void* GameOffsets::getPushStashInventoryDetour() const {
    return offsets.pPushStashInventoryDetour;
}
void** GameOffsets::getZEntitySceneContext_LoadScene() const {
    return offsets.pZEntitySceneContext_LoadScene;
}

}