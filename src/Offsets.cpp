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
        // Hitman 3 3.120.0 EGS offsets
        offsets.pPushItem0 = reinterpret_cast<void*>(0x140d9c6d0);
        offsets.pPushItem1 = reinterpret_cast<void*>(0x140d9ccc0);
        offsets.pPushHeroInventoryDetour = reinterpret_cast<void*>(0x1407cee63);
        offsets.pPushNPCInventoryDetour = reinterpret_cast<void*>(0x1400dd9b1);
        offsets.pPushStashInventoryDetour = reinterpret_cast<void*>(0x140234384);
        offsets.pPushWorldInventoryDetour = reinterpret_cast<void*>(0x140d96cfa);
        offsets.pZEntitySceneContext_LoadScene = reinterpret_cast<void**>(0x141d604a0);
    } break;
    case GameVersion::H3DX12_STEAM: {
        // Hitman 3 3.110.1 Steam offsets
        offsets.pPushItem0 = reinterpret_cast<void*>(0x140d9b7d0);
        offsets.pPushItem1 = reinterpret_cast<void*>(0x140d9bdc0);
        offsets.pPushHeroInventoryDetour = reinterpret_cast<void*>(0x1407ceb93);
        offsets.pPushNPCInventoryDetour = reinterpret_cast<void*>(0x1400dd6f1);
        offsets.pPushStashInventoryDetour = reinterpret_cast<void*>(0x1402340c4);
        offsets.pPushWorldInventoryDetour = reinterpret_cast<void*>(0x140d95dfa);
        offsets.pZEntitySceneContext_LoadScene = reinterpret_cast<void**>(0x141d658b0);
    } break;    

    case GameVersion::H2DX12:
    case GameVersion::H2DX11:
        // TODO: H2 Specific error message
    default:
        MessageBoxA(NULL,
                    std::format("The Randomizer Mod does not recognize this version of Hitman with PE timestamp {:X}.\n"
                                "Supported versions are:\n\n"
                                "- Hitman 3 EGS 3.120.0 (0x62C641F4)\n"
                                "- Hitman 3 Steam 3.120.0 (0x62C6418B)\n",
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