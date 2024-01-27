#include <iostream>
#include "pointerAuthEmuFrameLowering.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/CodeGen/MachineModuleInfo.h"
#include "llvm/IR/ValueSymbolTable.h"
#include "AArch64RegisterInfo.h"
#include "AArch64InstrInfo.h"

using namespace llvm;

void pointerAuthEmuFrameLowering::instrumentEpilogue(const TargetInstrInfo *TII, const TargetRegisterInfo *TRI,
                                  MachineBasicBlock &MBB, MachineBasicBlock::iterator &MBBI,
                                  const DebugLoc &DL, MachineModuleInfo &MMI) 
{   

    // // mov x0, x30    
    // // mov x1, sp
    // // bl _ZN7QARMA6414verify_pointerEyy
    // // mov x30, x0

    // get Machine instruction object
    auto MIi = (MBBI != MBB.end() ? &*MBBI : nullptr);

    // insert function call to verify pointer
    if (MIi == nullptr) {                
        BuildMI(&MBB, DL, TII->get(AArch64::ADDXri), AArch64::X0)
            .addReg(AArch64::LR)
            .addImm(0)
            .addImm(0);                    
        BuildMI(&MBB, DL, TII->get(AArch64::ADDXri), AArch64::X1)
            .addReg(AArch64::SP)
            .addImm(0)
            .addImm(0);            
        BuildMI(&MBB, DL, TII->get(AArch64::BL)).addExternalSymbol("_ZN7QARMA6414verify_pointerEyy");        
        BuildMI(&MBB, DL, TII->get(AArch64::ADDXri), AArch64::LR)
            .addReg(AArch64::X0)
            .addImm(0)
            .addImm(0);              
    } else {     
        BuildMI(MBB, MIi, DL, TII->get(AArch64::ADDXri), AArch64::X0)
            .addReg(AArch64::LR)
            .addImm(0)
            .addImm(0);                    
        BuildMI(MBB, MIi, DL, TII->get(AArch64::ADDXri), AArch64::X1)
            .addReg(AArch64::SP)
            .addImm(0)
            .addImm(0);            
        BuildMI(MBB, MIi, DL, TII->get(AArch64::BL)).addExternalSymbol("_ZN7QARMA6414verify_pointerEyy");        
        BuildMI(MBB, MIi, DL, TII->get(AArch64::ADDXri), AArch64::LR)
            .addReg(AArch64::X0)
            .addImm(0)
            .addImm(0);              
    }
}

void pointerAuthEmuFrameLowering::instrumentPrologue(const TargetInstrInfo *TII, const TargetRegisterInfo *TRI,
                                            MachineBasicBlock &MBB, MachineBasicBlock::iterator &MBBI,
                                            const DebugLoc &DL, MachineModuleInfo &MMI) 
{

    // // mov x0, x30
    // // mov x1, sp
    // // bl _ZN7QARMA6412sign_pointerEyy
    // // mov x30, x0
    
    // get Machine instruction object
    auto MIi = (MBBI != MBB.end() ? &*MBBI : nullptr);

    // insert function call to sign pointer
    if (MIi == nullptr) {                    
        BuildMI(&MBB, DL, TII->get(AArch64::ADDXri), AArch64::X0)
            .addReg(AArch64::LR)
            .addImm(0)
            .addImm(0);                    
        BuildMI(&MBB, DL, TII->get(AArch64::ADDXri), AArch64::X1)
            .addReg(AArch64::SP)
            .addImm(0)
            .addImm(0);            
        BuildMI(&MBB, DL, TII->get(AArch64::BL)).addExternalSymbol("_ZN7QARMA6412sign_pointerEyy");        
        BuildMI(&MBB, DL, TII->get(AArch64::ADDXri), AArch64::LR)
            .addReg(AArch64::X0)
            .addImm(0)
            .addImm(0);                  
    } else {
        BuildMI(MBB, MIi, DL, TII->get(AArch64::ADDXri), AArch64::X0)
            .addReg(AArch64::LR)
            .addImm(0)
            .addImm(0);                    
        BuildMI(MBB, MIi, DL, TII->get(AArch64::ADDXri), AArch64::X1)
            .addReg(AArch64::SP)
            .addImm(0)
            .addImm(0);            
        BuildMI(MBB, MIi, DL, TII->get(AArch64::BL)).addExternalSymbol("_ZN7QARMA6412sign_pointerEyy");        
        BuildMI(MBB, MIi, DL, TII->get(AArch64::ADDXri), AArch64::LR)
            .addReg(AArch64::X0)
            .addImm(0)
            .addImm(0);      
    }
}