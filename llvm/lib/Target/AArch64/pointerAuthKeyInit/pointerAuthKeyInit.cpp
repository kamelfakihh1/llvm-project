#include "llvm/Pass.h"
#include "llvm/CodeGen/MachineFunctionPass.h"
#include "llvm/Target/TargetIntrinsicInfo.h"
#include "llvm/Target/TargetMachine.h"
#include "llvm/Target/TargetOptions.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/CodeGen/MachineModuleInfo.h"
#include "llvm/IR/ValueSymbolTable.h"
#include "AArch64RegisterInfo.h"
#include "AArch64InstrInfo.h"
// #include "../ARM/ARMRegisterInfo.h"
// #include "../ARM/ARMInstrInfo.h"
#include "pointerAuthKeyInit.h"
#include <iostream>

using namespace llvm;

char PointerAuthKeyInit::ID = 0;

INITIALIZE_PASS_BEGIN(PointerAuthKeyInit, "pointerAuth key", "pointerAuth key pass", false, false)
INITIALIZE_PASS_END(PointerAuthKeyInit, "pointerAuth key", "pointerAuth key pass", false, false)

FunctionPass *llvm::createPointerAuthKeyInit() { return new PointerAuthKeyInit(); }

bool PointerAuthKeyInit::runOnMachineFunction(MachineFunction &MF) {        

    std::cout << MF.getName().str() << std::endl;

    const TargetInstrInfo *TII = MF.getSubtarget().getInstrInfo();

    if(MF.getName().str() == "main"){
        std::cout << "initializing PA key"<< std::endl;
        for(auto &MBB : MF){
            if(MBB.isEntryBlock()){
                MachineBasicBlock::iterator MBBI = MBB.begin();
                // MachineBasicBlock::iterator MBBI = MBB.getLastNonDebugInstr();        

                // // generate a random key                                    

                // stp x29, x30, [sp, -32]! 
                // BuildMI(MBB, MBBI, DebugLoc(), TII->get(AArch64::STPXpre))
                //     .addReg(AArch64::SP)
                //     .addReg(AArch64::FP)
                //     .addReg(AArch64::LR)
                //     .addReg(AArch64::SP)
                //     .addImm(-32)
                //     .setMIFlag(MachineInstr::FrameSetup);

                // // add x29, sp, 0
                // BuildMI(MBB, MBBI, DebugLoc(), TII->get(AArch64::ADDXri), AArch64::FP)
                //     .addReg(AArch64::SP)
                //     .addImm(0)
                //     .addImm(0); 

                // // add x0, sp, 0
                // BuildMI(MBB, MBBI, DebugLoc(), TII->get(AArch64::ADDXri), AArch64::X0)
                //     .addReg(AArch64::SP)
                //     .addImm(0)
                //     .addImm(0); 

                // BuildMI(MBB, MBBI, DebugLoc(), TII->get(AArch64::EORXrr), AArch64::X9)
                //     .addReg(AArch64::X9)
                //     .addReg(AArch64::X9)
                //     .addImm(0)
                //     .addImm(0); 

                // // add x1, x9, #8 
                // BuildMI(MBB, MBBI, DebugLoc(), TII->get(AArch64::ADDXri), AArch64::X1)
                //     .addReg(AArch64::X9)
                //     .addImm(8)
                //     .addImm(0); 

                // // add x2, x9, #0
                // BuildMI(MBB, MBBI, DebugLoc(), TII->get(AArch64::ADDXri), AArch64::X2)
                //     .addReg(AArch64::X9)
                //     .addImm(0)
                //     .addImm(0); 

                // BuildMI(MBB, MBBI, DebugLoc(), TII->get(AArch64::ADDXri), AArch64::X8)
                //     .addReg(AArch64::X9)
                //     .addImm(278)
                //     .addImm(0); 

                // // svc 0
                // BuildMI(MBB, MBBI, DebugLoc(), TII->get(ARM::SWI))                                        
                //     .addImm(0); 

                // // ldr x0, [sp]                  
                // BuildMI(MBB, MBBI, DebugLoc(), TII->get(AArch64::LDRXpost))
                //     .addReg(AArch64::SP)
                //     .addReg(AArch64::X27)                    
                //     .addReg(AArch64::SP)
                //     .addImm(0);


                // // ldp x29, x30, [sp], 32                  
                // BuildMI(MBB, MBBI, DebugLoc(), TII->get(AArch64::LDPXpost))
                //     .addReg(AArch64::SP)
                //     .addReg(AArch64::FP)
                //     .addReg(AArch64::LR)
                //     .addReg(AArch64::SP)
                //     .addImm(32);             

                // _ZN7QARMA6412generate_keyEv
                BuildMI(MBB, MBBI, DebugLoc(), TII->get(AArch64::BL)).addExternalSymbol("_ZN7QARMA6412generate_keyEv");                                                                                         
                                                                                         
                BuildMI(MBB, MBBI, DebugLoc(), TII->get(AArch64::ADDXri), AArch64::X27)
                    .addReg(AArch64::X0)
                    .addImm(0)
                    .addImm(0);        

                BuildMI(MBB, MBBI, DebugLoc(), TII->get(AArch64::ADDXri), AArch64::X28)
                    .addReg(AArch64::X1)
                    .addImm(0)
                    .addImm(0);                 
            }
        }
    }
    
    return true;
}