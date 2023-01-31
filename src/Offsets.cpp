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
    case GameVersion::H3DX12_STEAM_WOA: {
        // Hitman 3 3.140.0 EGS offsets
        offsets.pPushItem0 = reinterpret_cast<void*>(0x140db07f0);
        offsets.pPushItem1 = reinterpret_cast<void*>(0x140db0de0);
        offsets.pPushHeroInventoryDetour = reinterpret_cast<void*>(0x1407d0eb3);
        offsets.pPushNPCInventoryDetour = reinterpret_cast<void*>(0x1400dfc01);
        offsets.pPushStashInventoryDetour = reinterpret_cast<void*>(0x1402370d4);
        offsets.pPushWorldInventoryDetour = reinterpret_cast<void*>(0x140daae1a);
        offsets.pZEntitySceneContext_LoadScene = reinterpret_cast<void**>(0x141d810e8);
    } break;
    case GameVersion::H3DX12_EGS_WOA: {
        // Hitman 3 3.140.0 EGS offsets
        offsets.pPushItem0 = reinterpret_cast<void*>(0x140db0250);
        offsets.pPushItem1 = reinterpret_cast<void*>(0x140db0840);
        offsets.pPushHeroInventoryDetour = reinterpret_cast<void*>(0x1407d0f13);
        offsets.pPushNPCInventoryDetour = reinterpret_cast<void*>(0x1400dfc71);
        offsets.pPushStashInventoryDetour = reinterpret_cast<void*>(0x140237134);
        offsets.pPushWorldInventoryDetour = reinterpret_cast<void*>(0x140daa87a);
        offsets.pZEntitySceneContext_LoadScene = reinterpret_cast<void**>(0x141d7acd8);
    } break;

    default:
        MessageBoxA(NULL,
                    std::format("The Randomizer Mod does not recognize this version of Hitman with PE timestamp {:X}.\n"
                                "Supported versions are:\n\n"
                                "- Hitman 3 Steam 3.140.0 (0x63C7E952)\n"
                                "- Hitman 3 EGS 3.140.0 (0x63C6130E)\n",
                                PE::getTimestamp())
                    .c_str(),
                    "Randomizer Mod Failure", NULL);
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