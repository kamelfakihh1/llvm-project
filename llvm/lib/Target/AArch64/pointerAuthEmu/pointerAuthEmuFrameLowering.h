#ifndef PA_AUTH_EMU_FRAME_LOWERING_H
#define PA_AUTH_EMU_FRAME_LOWERING_H

#include "llvm/CodeGen/MachineBasicBlock.h"
#include "llvm/CodeGen/MachineModuleInfo.h"
#include "AArch64InstrInfo.h"

namespace llvm {

    namespace pointerAuthEmuFrameLowering {

    const StringRef signAddressFuncName = StringRef("_Z4signv");
    const StringRef verifyAddressFuncName = StringRef("_Z6verifyv");

    void instrumentEpilogue(const TargetInstrInfo *TII, const TargetRegisterInfo *TRI,
                        MachineBasicBlock &MBB, MachineBasicBlock::iterator &MBBI,
                        const DebugLoc &DL, MachineModuleInfo &MMI);

    void instrumentPrologue(const TargetInstrInfo *TII, const TargetRegisterInfo *TRI,
                            MachineBasicBlock &MBB, MachineBasicBlock::iterator &MBBI,
                            const DebugLoc &DL, MachineModuleInfo &MMI);
    
    void addFunctionCall(const TargetInstrInfo *TII, MachineBasicBlock &MBB, MachineInstr &MI,
                                    const DebugLoc &DL, Function *func);
    
    }
}


#endif