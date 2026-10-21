#include <unistd.h>
#include <string>
#include <iostream>
#include "../KittyMemoryEx/KittyMemoryMgr.hpp"

KittyMemoryMgr kittyMemMgr;

int main()
{
    std::string procName = "./test";

    pid_t procID = KittyMemoryEx::getProcessID(procName);

    if(!procID){
        KITTY_LOGE("pid not found '%s'",procName.c_str());
        return 1;
    }
    KITTY_LOGI("pid found %d", procID);

    if(!kittyMemMgr.initialize(procID, EK_MEM_OP_SYSCALL, true)){
        KITTY_LOGE("memory or permition error");
        return 1;
    }
    KITTY_LOGI("memory initialize succesful");

    ElfScanner elf{};
    do{
        sleep(1);
        elf = kittyMemMgr.elfScanner.findElf("test");
    } while (!elf.isValid());
    
    KITTY_LOGI("memory found succesful");

    uintptr_t getScore = elf.base() + 0x2476;

    uintptr_t getHelth = elf.base() + 0x30a0;

    uintptr_t isAdmin = elf.base() + 0x2497;

    uintptr_t isPlayer = elf.base() + 0x24a6;

    uintptr_t nameptch = elf.base() + 0x3008;

    MemoryPatch name = kittyMemMgr.memPatch.createWithHex(
        nameptch,
        "68 61 63 6B 65 64" // its str
    );

    MemoryPatch Helth = kittyMemMgr.memPatch.createWithHex(
        getScore,
        "b8 a0 86 01 00" // its int
    );

    MemoryPatch Score = kittyMemMgr.memPatch.createWithHex(
        getHelth,
        "00 50 C3 47" // its float
    );

    MemoryPatch Admin = kittyMemMgr.memPatch.createWithHex(
        isAdmin,
        "b8 01 00 00 00" // its bool
    );

    MemoryPatch Player = kittyMemMgr.memPatch.createWithHex(
        isPlayer,
        "b8 00 00 00 00" // its bool
    );


    if (Helth.Modify() && Score.Modify() && Player.Modify() && Admin.Modify() && name.Modify()) {
        KITTY_LOGI("Patched successfully! Check the target terminal.");;
    } else {
        KITTY_LOGE("Patch failed.");
    }

    sleep(10);

    if(Helth.Restore() && Score.Restore() && Player.Restore() && Admin.Restore() && name.Restore() ){
        KITTY_LOGI("patch restore successfully!");
    }else{
        KITTY_LOGE("restore failed");
    }


    return 0;
}