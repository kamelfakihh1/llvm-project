#ifndef PA_AUTH_EMU_FRAME_LOWERING_H
#define PA_AUTH_EMU_FRAME_LOWERING_H

#include "llvm/CodeGen/MachineBasicBlock.h"
#include "llvm/CodeGen/MachineModuleInfo.h"
#include "AArch64InstrInfo.h"

namespace llvm {

    namespace pointerAuthEmuFrameLowering {
        
    void instrumentEpilogue(const TargetInstrInfo *TII, 
                        MachineBasicBlock &MBB, MachineBasicBlock::iterator &MBBI,
                        const DebugLoc &DL);

    void instrumentPrologue(const TargetInstrInfo *TII, 
                            MachineBasicBlock &MBB, MachineBasicBlock::iterator &MBBI,
                            const DebugLoc &DL);    
    
    }
}


#endif