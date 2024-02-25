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
                                  const DebugLoc &DL) 
{   

    // // mov x0, x30    
    // // mov x1, sp
    // // bl _ZN7QARMA6414verify_pointerEyy
    // // mov x30, x0    

    MachineFunction *MF = MBB.getParent();    
    if(MF->getName().str() == "main" || MF->getName().str() == "_GLOBAL__sub_I_pa_test.cpp" || MF->getName().str() == "_GLOBAL__sub_I_main.cpp" || MF->getName().str() == "__cxx_global_var_init"){
        return;
    }


    // get Machine instruction object
    auto MIi = (MBBI != MBB.end() ? &*MBBI : nullptr);
    std::cout << "Intrumenting epilogue : " << MF->getName().str() << std::endl;

    // insert function call to verify pointer
    if (MIi == nullptr) {  
        BuildMI(&MBB, DL, TII->get(AArch64::STRXpre), AArch64::SP)
            .addReg(AArch64::X0)
            .addReg(AArch64::SP)
            .addImm(-16);            
        BuildMI(&MBB, DL, TII->get(AArch64::STRXpre), AArch64::SP)
            .addReg(AArch64::X1)
            .addReg(AArch64::SP)
            .addImm(-16);            
        BuildMI(&MBB, DL, TII->get(AArch64::STRXpre), AArch64::SP)
            .addReg(AArch64::X2)
            .addReg(AArch64::SP)
            .addImm(-16);                          
        BuildMI(&MBB, DL, TII->get(AArch64::STRXpre), AArch64::SP)
            .addReg(AArch64::X3)
            .addReg(AArch64::SP)
            .addImm(-16);                
        BuildMI(&MBB, DL, TII->get(AArch64::STRXpre), AArch64::SP)
            .addReg(AArch64::X4)
            .addReg(AArch64::SP)
            .addImm(-16);            
        BuildMI(&MBB, DL, TII->get(AArch64::STRXpre), AArch64::SP)
            .addReg(AArch64::X5)
            .addReg(AArch64::SP)
            .addImm(-16);            
        BuildMI(&MBB, DL, TII->get(AArch64::STRXpre), AArch64::SP)
            .addReg(AArch64::X6)
            .addReg(AArch64::SP)
            .addImm(-16);                          
        BuildMI(&MBB, DL, TII->get(AArch64::STRXpre), AArch64::SP)
            .addReg(AArch64::X7)
            .addReg(AArch64::SP)
            .addImm(-16);      
        BuildMI(&MBB, DL, TII->get(AArch64::STRXpre), AArch64::SP)
            .addReg(AArch64::X8)
            .addReg(AArch64::SP)
            .addImm(-16);            
        BuildMI(&MBB, DL, TII->get(AArch64::STRXpre), AArch64::SP)
            .addReg(AArch64::X9)
            .addReg(AArch64::SP)
            .addImm(-16);            
        BuildMI(&MBB, DL, TII->get(AArch64::STRXpre), AArch64::SP)
            .addReg(AArch64::X10)
            .addReg(AArch64::SP)
            .addImm(-16);                          
        BuildMI(&MBB, DL, TII->get(AArch64::STRXpre), AArch64::SP)
            .addReg(AArch64::X11)
            .addReg(AArch64::SP)
            .addImm(-16);                
        BuildMI(&MBB, DL, TII->get(AArch64::STRXpre), AArch64::SP)
            .addReg(AArch64::X12)
            .addReg(AArch64::SP)
            .addImm(-16);            
        BuildMI(&MBB, DL, TII->get(AArch64::STRXpre), AArch64::SP)
            .addReg(AArch64::X13)
            .addReg(AArch64::SP)
            .addImm(-16);            
        BuildMI(&MBB, DL, TII->get(AArch64::STRXpre), AArch64::SP)
            .addReg(AArch64::X14)
            .addReg(AArch64::SP)
            .addImm(-16);                          
        BuildMI(&MBB, DL, TII->get(AArch64::STRXpre), AArch64::SP)
            .addReg(AArch64::X15)
            .addReg(AArch64::SP)
            .addImm(-16);       
        BuildMI(&MBB, DL, TII->get(AArch64::STRXpre), AArch64::SP)
            .addReg(AArch64::X16)
            .addReg(AArch64::SP)
            .addImm(-16);            
        BuildMI(&MBB, DL, TII->get(AArch64::STRXpre), AArch64::SP)
            .addReg(AArch64::X17)
            .addReg(AArch64::SP)
            .addImm(-16);            
        BuildMI(&MBB, DL, TII->get(AArch64::STRXpre), AArch64::SP)
            .addReg(AArch64::X18)
            .addReg(AArch64::SP)
            .addImm(-16);                                 
        BuildMI(&MBB, DL, TII->get(AArch64::ADDXri), AArch64::X0)
            .addReg(AArch64::LR)
            .addImm(0)
            .addImm(0);                    
        BuildMI(&MBB, DL, TII->get(AArch64::ADDXri), AArch64::X1)
            .addReg(AArch64::SP)
            .addImm(0)
            .addImm(0);   
        BuildMI(&MBB, DL, TII->get(AArch64::ADDXri), AArch64::X2)
            .addReg(AArch64::X27)
            .addImm(0)
            .addImm(0);   
        BuildMI(&MBB, DL, TII->get(AArch64::ADDXri), AArch64::X3)
            .addReg(AArch64::X28)
            .addImm(0)
            .addImm(0);                        
        BuildMI(&MBB, DL, TII->get(AArch64::BL)).addExternalSymbol("_ZN7QARMA6414verify_pointerEyyyy");
        BuildMI(&MBB, DL, TII->get(AArch64::ADDXri), AArch64::LR)
            .addReg(AArch64::X0)
            .addImm(0)
            .addImm(0);  
        BuildMI(&MBB, DL, TII->get(AArch64::LDRXpost), AArch64::SP)
            .addReg(AArch64::X18)
            .addReg(AArch64::SP)
            .addImm(16);            
        BuildMI(&MBB, DL, TII->get(AArch64::LDRXpost), AArch64::SP)
            .addReg(AArch64::X17)
            .addReg(AArch64::SP)
            .addImm(16);            
        BuildMI(&MBB, DL, TII->get(AArch64::LDRXpost), AArch64::SP)
            .addReg(AArch64::X16)
            .addReg(AArch64::SP)
            .addImm(16);                          
        BuildMI(&MBB, DL, TII->get(AArch64::LDRXpost), AArch64::SP)
            .addReg(AArch64::X15)
            .addReg(AArch64::SP)
            .addImm(16);                
        BuildMI(&MBB, DL, TII->get(AArch64::LDRXpost), AArch64::SP)
            .addReg(AArch64::X14)
            .addReg(AArch64::SP)
            .addImm(16);            
        BuildMI(&MBB, DL, TII->get(AArch64::LDRXpost), AArch64::SP)
            .addReg(AArch64::X13)
            .addReg(AArch64::SP)
            .addImm(16);            
        BuildMI(&MBB, DL, TII->get(AArch64::LDRXpost), AArch64::SP)
            .addReg(AArch64::X12)
            .addReg(AArch64::SP)
            .addImm(16);                          
        BuildMI(&MBB, DL, TII->get(AArch64::LDRXpost), AArch64::SP)
            .addReg(AArch64::X11)
            .addReg(AArch64::SP)
            .addImm(16);      
        BuildMI(&MBB, DL, TII->get(AArch64::LDRXpost), AArch64::SP)
            .addReg(AArch64::X10)
            .addReg(AArch64::SP)
            .addImm(16);            
        BuildMI(&MBB, DL, TII->get(AArch64::LDRXpost), AArch64::SP)
            .addReg(AArch64::X9)
            .addReg(AArch64::SP)
            .addImm(16);            
        BuildMI(&MBB, DL, TII->get(AArch64::LDRXpost), AArch64::SP)
            .addReg(AArch64::X8)
            .addReg(AArch64::SP)
            .addImm(16);                          
        BuildMI(&MBB, DL, TII->get(AArch64::LDRXpost), AArch64::SP)
            .addReg(AArch64::X7)
            .addReg(AArch64::SP)
            .addImm(16);                
        BuildMI(&MBB, DL, TII->get(AArch64::LDRXpost), AArch64::SP)
            .addReg(AArch64::X6)
            .addReg(AArch64::SP)
            .addImm(16);            
        BuildMI(&MBB, DL, TII->get(AArch64::LDRXpost), AArch64::SP)
            .addReg(AArch64::X5)
            .addReg(AArch64::SP)
            .addImm(16);            
        BuildMI(&MBB, DL, TII->get(AArch64::LDRXpost), AArch64::SP)
            .addReg(AArch64::X4)
            .addReg(AArch64::SP)
            .addImm(16);                          
        BuildMI(&MBB, DL, TII->get(AArch64::LDRXpost), AArch64::SP)
            .addReg(AArch64::X3)
            .addReg(AArch64::SP)
            .addImm(16);       
        BuildMI(&MBB, DL, TII->get(AArch64::LDRXpost), AArch64::SP)
            .addReg(AArch64::X2)
            .addReg(AArch64::SP)
            .addImm(16);            
        BuildMI(&MBB, DL, TII->get(AArch64::LDRXpost), AArch64::SP)
            .addReg(AArch64::X1)
            .addReg(AArch64::SP)
            .addImm(16);            
        BuildMI(&MBB, DL, TII->get(AArch64::LDRXpost), AArch64::SP)
            .addReg(AArch64::X0)
            .addReg(AArch64::SP)
            .addImm(16);                     
    } else {    
        BuildMI(MBB, MIi, DL, TII->get(AArch64::STRXpre), AArch64::SP)
            .addReg(AArch64::X0)
            .addReg(AArch64::SP)
            .addImm(-16);            
        BuildMI(MBB, MIi, DL, TII->get(AArch64::STRXpre), AArch64::SP)
            .addReg(AArch64::X1)
            .addReg(AArch64::SP)
            .addImm(-16);            
        BuildMI(MBB, MIi, DL, TII->get(AArch64::STRXpre), AArch64::SP)
            .addReg(AArch64::X2)
            .addReg(AArch64::SP)
            .addImm(-16);                          
        BuildMI(MBB, MIi, DL, TII->get(AArch64::STRXpre), AArch64::SP)
            .addReg(AArch64::X3)
            .addReg(AArch64::SP)
            .addImm(-16);                
        BuildMI(MBB, MIi, DL, TII->get(AArch64::STRXpre), AArch64::SP)
            .addReg(AArch64::X4)
            .addReg(AArch64::SP)
            .addImm(-16);            
        BuildMI(MBB, MIi, DL, TII->get(AArch64::STRXpre), AArch64::SP)
            .addReg(AArch64::X5)
            .addReg(AArch64::SP)
            .addImm(-16);            
        BuildMI(MBB, MIi, DL, TII->get(AArch64::STRXpre), AArch64::SP)
            .addReg(AArch64::X6)
            .addReg(AArch64::SP)
            .addImm(-16);                          
        BuildMI(MBB, MIi, DL, TII->get(AArch64::STRXpre), AArch64::SP)
            .addReg(AArch64::X7)
            .addReg(AArch64::SP)
            .addImm(-16);      
        BuildMI(MBB, MIi, DL, TII->get(AArch64::STRXpre), AArch64::SP)
            .addReg(AArch64::X8)
            .addReg(AArch64::SP)
            .addImm(-16);            
        BuildMI(MBB, MIi, DL, TII->get(AArch64::STRXpre), AArch64::SP)
            .addReg(AArch64::X9)
            .addReg(AArch64::SP)
            .addImm(-16);            
        BuildMI(MBB, MIi, DL, TII->get(AArch64::STRXpre), AArch64::SP)
            .addReg(AArch64::X10)
            .addReg(AArch64::SP)
            .addImm(-16);                          
        BuildMI(MBB, MIi, DL, TII->get(AArch64::STRXpre), AArch64::SP)
            .addReg(AArch64::X11)
            .addReg(AArch64::SP)
            .addImm(-16);                
        BuildMI(MBB, MIi, DL, TII->get(AArch64::STRXpre), AArch64::SP)
            .addReg(AArch64::X12)
            .addReg(AArch64::SP)
            .addImm(-16);            
        BuildMI(MBB, MIi, DL, TII->get(AArch64::STRXpre), AArch64::SP)
            .addReg(AArch64::X13)
            .addReg(AArch64::SP)
            .addImm(-16);            
        BuildMI(MBB, MIi, DL, TII->get(AArch64::STRXpre), AArch64::SP)
            .addReg(AArch64::X14)
            .addReg(AArch64::SP)
            .addImm(-16);                          
        BuildMI(MBB, MIi, DL, TII->get(AArch64::STRXpre), AArch64::SP)
            .addReg(AArch64::X15)
            .addReg(AArch64::SP)
            .addImm(-16);       
        BuildMI(MBB, MIi, DL, TII->get(AArch64::STRXpre), AArch64::SP)
            .addReg(AArch64::X16)
            .addReg(AArch64::SP)
            .addImm(-16);            
        BuildMI(MBB, MIi, DL, TII->get(AArch64::STRXpre), AArch64::SP)
            .addReg(AArch64::X17)
            .addReg(AArch64::SP)
            .addImm(-16);            
        BuildMI(MBB, MIi, DL, TII->get(AArch64::STRXpre), AArch64::SP)
            .addReg(AArch64::X18)
            .addReg(AArch64::SP)
            .addImm(-16);                             
        BuildMI(MBB, MIi, DL, TII->get(AArch64::ADDXri), AArch64::X0)
            .addReg(AArch64::LR)
            .addImm(0)
            .addImm(0);                    
        BuildMI(MBB, MIi, DL, TII->get(AArch64::ADDXri), AArch64::X1)
            .addReg(AArch64::SP)
            .addImm(0)
            .addImm(0);      
        BuildMI(MBB, MIi, DL, TII->get(AArch64::ADDXri), AArch64::X2)
            .addReg(AArch64::X27)
            .addImm(0)
            .addImm(0);   
        BuildMI(MBB, MIi, DL, TII->get(AArch64::ADDXri), AArch64::X3)
            .addReg(AArch64::X28)
            .addImm(0)
            .addImm(0);            
        BuildMI(MBB, MIi, DL, TII->get(AArch64::BL)).addExternalSymbol("_ZN7QARMA6414verify_pointerEyyyy");        
        BuildMI(MBB, MIi, DL, TII->get(AArch64::ADDXri), AArch64::LR)
            .addReg(AArch64::X0)
            .addImm(0)
            .addImm(0); 
        BuildMI(MBB, MIi, DL, TII->get(AArch64::LDRXpost), AArch64::SP)
            .addReg(AArch64::X18)
            .addReg(AArch64::SP)
            .addImm(16);            
        BuildMI(MBB, MIi, DL, TII->get(AArch64::LDRXpost), AArch64::SP)
            .addReg(AArch64::X17)
            .addReg(AArch64::SP)
            .addImm(16);            
        BuildMI(MBB, MIi, DL, TII->get(AArch64::LDRXpost), AArch64::SP)
            .addReg(AArch64::X16)
            .addReg(AArch64::SP)
            .addImm(16);                          
        BuildMI(MBB, MIi, DL, TII->get(AArch64::LDRXpost), AArch64::SP)
            .addReg(AArch64::X15)
            .addReg(AArch64::SP)
            .addImm(16);                
        BuildMI(MBB, MIi, DL, TII->get(AArch64::LDRXpost), AArch64::SP)
            .addReg(AArch64::X14)
            .addReg(AArch64::SP)
            .addImm(16);            
        BuildMI(MBB, MIi, DL, TII->get(AArch64::LDRXpost), AArch64::SP)
            .addReg(AArch64::X13)
            .addReg(AArch64::SP)
            .addImm(16);            
        BuildMI(MBB, MIi, DL, TII->get(AArch64::LDRXpost), AArch64::SP)
            .addReg(AArch64::X12)
            .addReg(AArch64::SP)
            .addImm(16);                          
        BuildMI(MBB, MIi, DL, TII->get(AArch64::LDRXpost), AArch64::SP)
            .addReg(AArch64::X11)
            .addReg(AArch64::SP)
            .addImm(16);      
        BuildMI(MBB, MIi, DL, TII->get(AArch64::LDRXpost), AArch64::SP)
            .addReg(AArch64::X10)
            .addReg(AArch64::SP)
            .addImm(16);            
        BuildMI(MBB, MIi, DL, TII->get(AArch64::LDRXpost), AArch64::SP)
            .addReg(AArch64::X9)
            .addReg(AArch64::SP)
            .addImm(16);            
        BuildMI(MBB, MIi, DL, TII->get(AArch64::LDRXpost), AArch64::SP)
            .addReg(AArch64::X8)
            .addReg(AArch64::SP)
            .addImm(16);                          
        BuildMI(MBB, MIi, DL, TII->get(AArch64::LDRXpost), AArch64::SP)
            .addReg(AArch64::X7)
            .addReg(AArch64::SP)
            .addImm(16);                
        BuildMI(MBB, MIi, DL, TII->get(AArch64::LDRXpost), AArch64::SP)
            .addReg(AArch64::X6)
            .addReg(AArch64::SP)
            .addImm(16);            
        BuildMI(MBB, MIi, DL, TII->get(AArch64::LDRXpost), AArch64::SP)
            .addReg(AArch64::X5)
            .addReg(AArch64::SP)
            .addImm(16);            
        BuildMI(MBB, MIi, DL, TII->get(AArch64::LDRXpost), AArch64::SP)
            .addReg(AArch64::X4)
            .addReg(AArch64::SP)
            .addImm(16);                          
        BuildMI(MBB, MIi, DL, TII->get(AArch64::LDRXpost), AArch64::SP)
            .addReg(AArch64::X3)
            .addReg(AArch64::SP)
            .addImm(16);       
        BuildMI(MBB, MIi, DL, TII->get(AArch64::LDRXpost), AArch64::SP)
            .addReg(AArch64::X2)
            .addReg(AArch64::SP)
            .addImm(16);            
        BuildMI(MBB, MIi, DL, TII->get(AArch64::LDRXpost), AArch64::SP)
            .addReg(AArch64::X1)
            .addReg(AArch64::SP)
            .addImm(16);            
        BuildMI(MBB, MIi, DL, TII->get(AArch64::LDRXpost), AArch64::SP)
            .addReg(AArch64::X0)
            .addReg(AArch64::SP)
            .addImm(16);                                  
    }
}

void pointerAuthEmuFrameLowering::instrumentPrologue(const TargetInstrInfo *TII, const TargetRegisterInfo *TRI,
                                            MachineBasicBlock &MBB, MachineBasicBlock::iterator &MBBI,
                                            const DebugLoc &DL) 
{

    // // mov x0, x30
    // // mov x1, sp
    // // bl _ZN7QARMA6412sign_pointerEyy
    // // mov x30, x0
    
    MachineFunction *MF = MBB.getParent();
    if(MF->getName().str() == "main" || MF->getName().str() == "_GLOBAL__sub_I_pa_test.cpp" || MF->getName().str() == "_GLOBAL__sub_I_main.cpp" || MF->getName().str() == "__cxx_global_var_init"){
        return;
    }

    std::cout << "Intrumenting prologue : " << MF->getName().str() << std::endl;

    // get Machine instruction object
    auto MIi = (MBBI != MBB.end() ? &*MBBI : nullptr);

    // insert function call to sign pointer
    if (MIi == nullptr) {            
        BuildMI(&MBB, DL, TII->get(AArch64::STRXpre), AArch64::SP)
            .addReg(AArch64::X0)
            .addReg(AArch64::SP)
            .addImm(-16);            
        BuildMI(&MBB, DL, TII->get(AArch64::STRXpre), AArch64::SP)
            .addReg(AArch64::X1)
            .addReg(AArch64::SP)
            .addImm(-16);            
        BuildMI(&MBB, DL, TII->get(AArch64::STRXpre), AArch64::SP)
            .addReg(AArch64::X2)
            .addReg(AArch64::SP)
            .addImm(-16);                          
        BuildMI(&MBB, DL, TII->get(AArch64::STRXpre), AArch64::SP)
            .addReg(AArch64::X3)
            .addReg(AArch64::SP)
            .addImm(-16);                
        BuildMI(&MBB, DL, TII->get(AArch64::STRXpre), AArch64::SP)
            .addReg(AArch64::X4)
            .addReg(AArch64::SP)
            .addImm(-16);            
        BuildMI(&MBB, DL, TII->get(AArch64::STRXpre), AArch64::SP)
            .addReg(AArch64::X5)
            .addReg(AArch64::SP)
            .addImm(-16);            
        BuildMI(&MBB, DL, TII->get(AArch64::STRXpre), AArch64::SP)
            .addReg(AArch64::X6)
            .addReg(AArch64::SP)
            .addImm(-16);                          
        BuildMI(&MBB, DL, TII->get(AArch64::STRXpre), AArch64::SP)
            .addReg(AArch64::X7)
            .addReg(AArch64::SP)
            .addImm(-16);      
        BuildMI(&MBB, DL, TII->get(AArch64::STRXpre), AArch64::SP)
            .addReg(AArch64::X8)
            .addReg(AArch64::SP)
            .addImm(-16);            
        BuildMI(&MBB, DL, TII->get(AArch64::STRXpre), AArch64::SP)
            .addReg(AArch64::X9)
            .addReg(AArch64::SP)
            .addImm(-16);            
        BuildMI(&MBB, DL, TII->get(AArch64::STRXpre), AArch64::SP)
            .addReg(AArch64::X10)
            .addReg(AArch64::SP)
            .addImm(-16);                          
        BuildMI(&MBB, DL, TII->get(AArch64::STRXpre), AArch64::SP)
            .addReg(AArch64::X11)
            .addReg(AArch64::SP)
            .addImm(-16);                
        BuildMI(&MBB, DL, TII->get(AArch64::STRXpre), AArch64::SP)
            .addReg(AArch64::X12)
            .addReg(AArch64::SP)
            .addImm(-16);            
        BuildMI(&MBB, DL, TII->get(AArch64::STRXpre), AArch64::SP)
            .addReg(AArch64::X13)
            .addReg(AArch64::SP)
            .addImm(-16);            
        BuildMI(&MBB, DL, TII->get(AArch64::STRXpre), AArch64::SP)
            .addReg(AArch64::X14)
            .addReg(AArch64::SP)
            .addImm(-16);                          
        BuildMI(&MBB, DL, TII->get(AArch64::STRXpre), AArch64::SP)
            .addReg(AArch64::X15)
            .addReg(AArch64::SP)
            .addImm(-16);       
        BuildMI(&MBB, DL, TII->get(AArch64::STRXpre), AArch64::SP)
            .addReg(AArch64::X16)
            .addReg(AArch64::SP)
            .addImm(-16);            
        BuildMI(&MBB, DL, TII->get(AArch64::STRXpre), AArch64::SP)
            .addReg(AArch64::X17)
            .addReg(AArch64::SP)
            .addImm(-16);            
        BuildMI(&MBB, DL, TII->get(AArch64::STRXpre), AArch64::SP)
            .addReg(AArch64::X18)
            .addReg(AArch64::SP)
            .addImm(-16);             ;
        BuildMI(&MBB, DL, TII->get(AArch64::ADDXri), AArch64::X0)
            .addReg(AArch64::LR)
            .addImm(0)
            .addImm(0);                    
        BuildMI(&MBB, DL, TII->get(AArch64::ADDXri), AArch64::X1)
            .addReg(AArch64::SP)
            .addImm(0)
            .addImm(0); 
        BuildMI(&MBB, DL, TII->get(AArch64::ADDXri), AArch64::X2)
            .addReg(AArch64::X27)
            .addImm(0)
            .addImm(0);   
        BuildMI(&MBB, DL, TII->get(AArch64::ADDXri), AArch64::X3)
            .addReg(AArch64::X28)
            .addImm(0)
            .addImm(0);                  
        BuildMI(&MBB, DL, TII->get(AArch64::BL)).addExternalSymbol("_ZN7QARMA6412sign_pointerEyyyy");        
        BuildMI(&MBB, DL, TII->get(AArch64::ADDXri), AArch64::LR)
            .addReg(AArch64::X0)
            .addImm(0);     
        BuildMI(&MBB, DL, TII->get(AArch64::LDRXpost), AArch64::SP)
            .addReg(AArch64::X18)
            .addReg(AArch64::SP)
            .addImm(16);            
        BuildMI(&MBB, DL, TII->get(AArch64::LDRXpost), AArch64::SP)
            .addReg(AArch64::X17)
            .addReg(AArch64::SP)
            .addImm(16);            
        BuildMI(&MBB, DL, TII->get(AArch64::LDRXpost), AArch64::SP)
            .addReg(AArch64::X16)
            .addReg(AArch64::SP)
            .addImm(16);                          
        BuildMI(&MBB, DL, TII->get(AArch64::LDRXpost), AArch64::SP)
            .addReg(AArch64::X15)
            .addReg(AArch64::SP)
            .addImm(16);                
        BuildMI(&MBB, DL, TII->get(AArch64::LDRXpost), AArch64::SP)
            .addReg(AArch64::X14)
            .addReg(AArch64::SP)
            .addImm(16);            
        BuildMI(&MBB, DL, TII->get(AArch64::LDRXpost), AArch64::SP)
            .addReg(AArch64::X13)
            .addReg(AArch64::SP)
            .addImm(16);            
        BuildMI(&MBB, DL, TII->get(AArch64::LDRXpost), AArch64::SP)
            .addReg(AArch64::X12)
            .addReg(AArch64::SP)
            .addImm(16);                          
        BuildMI(&MBB, DL, TII->get(AArch64::LDRXpost), AArch64::SP)
            .addReg(AArch64::X11)
            .addReg(AArch64::SP)
            .addImm(16);      
        BuildMI(&MBB, DL, TII->get(AArch64::LDRXpost), AArch64::SP)
            .addReg(AArch64::X10)
            .addReg(AArch64::SP)
            .addImm(16);            
        BuildMI(&MBB, DL, TII->get(AArch64::LDRXpost), AArch64::SP)
            .addReg(AArch64::X9)
            .addReg(AArch64::SP)
            .addImm(16);            
        BuildMI(&MBB, DL, TII->get(AArch64::LDRXpost), AArch64::SP)
            .addReg(AArch64::X8)
            .addReg(AArch64::SP)
            .addImm(16);                          
        BuildMI(&MBB, DL, TII->get(AArch64::LDRXpost), AArch64::SP)
            .addReg(AArch64::X7)
            .addReg(AArch64::SP)
            .addImm(16);                
        BuildMI(&MBB, DL, TII->get(AArch64::LDRXpost), AArch64::SP)
            .addReg(AArch64::X6)
            .addReg(AArch64::SP)
            .addImm(16);            
        BuildMI(&MBB, DL, TII->get(AArch64::LDRXpost), AArch64::SP)
            .addReg(AArch64::X5)
            .addReg(AArch64::SP)
            .addImm(16);            
        BuildMI(&MBB, DL, TII->get(AArch64::LDRXpost), AArch64::SP)
            .addReg(AArch64::X4)
            .addReg(AArch64::SP)
            .addImm(16);                          
        BuildMI(&MBB, DL, TII->get(AArch64::LDRXpost), AArch64::SP)
            .addReg(AArch64::X3)
            .addReg(AArch64::SP)
            .addImm(16);       
        BuildMI(&MBB, DL, TII->get(AArch64::LDRXpost), AArch64::SP)
            .addReg(AArch64::X2)
            .addReg(AArch64::SP)
            .addImm(16);            
        BuildMI(&MBB, DL, TII->get(AArch64::LDRXpost), AArch64::SP)
            .addReg(AArch64::X1)
            .addReg(AArch64::SP)
            .addImm(16);            
        BuildMI(&MBB, DL, TII->get(AArch64::LDRXpost), AArch64::SP)
            .addReg(AArch64::X0)
            .addReg(AArch64::SP)
            .addImm(16);             
    } else {      
                BuildMI(MBB, MIi, DL, TII->get(AArch64::STRXpre), AArch64::SP)
            .addReg(AArch64::X0)
            .addReg(AArch64::SP)
            .addImm(-16);            
        BuildMI(MBB, MIi, DL, TII->get(AArch64::STRXpre), AArch64::SP)
            .addReg(AArch64::X1)
            .addReg(AArch64::SP)
            .addImm(-16);            
        BuildMI(MBB, MIi, DL, TII->get(AArch64::STRXpre), AArch64::SP)
            .addReg(AArch64::X2)
            .addReg(AArch64::SP)
            .addImm(-16);                          
        BuildMI(MBB, MIi, DL, TII->get(AArch64::STRXpre), AArch64::SP)
            .addReg(AArch64::X3)
            .addReg(AArch64::SP)
            .addImm(-16);                
        BuildMI(MBB, MIi, DL, TII->get(AArch64::STRXpre), AArch64::SP)
            .addReg(AArch64::X4)
            .addReg(AArch64::SP)
            .addImm(-16);            
        BuildMI(MBB, MIi, DL, TII->get(AArch64::STRXpre), AArch64::SP)
            .addReg(AArch64::X5)
            .addReg(AArch64::SP)
            .addImm(-16);            
        BuildMI(MBB, MIi, DL, TII->get(AArch64::STRXpre), AArch64::SP)
            .addReg(AArch64::X6)
            .addReg(AArch64::SP)
            .addImm(-16);                          
        BuildMI(MBB, MIi, DL, TII->get(AArch64::STRXpre), AArch64::SP)
            .addReg(AArch64::X7)
            .addReg(AArch64::SP)
            .addImm(-16);      
        BuildMI(MBB, MIi, DL, TII->get(AArch64::STRXpre), AArch64::SP)
            .addReg(AArch64::X8)
            .addReg(AArch64::SP)
            .addImm(-16);            
        BuildMI(MBB, MIi, DL, TII->get(AArch64::STRXpre), AArch64::SP)
            .addReg(AArch64::X9)
            .addReg(AArch64::SP)
            .addImm(-16);            
        BuildMI(MBB, MIi, DL, TII->get(AArch64::STRXpre), AArch64::SP)
            .addReg(AArch64::X10)
            .addReg(AArch64::SP)
            .addImm(-16);                          
        BuildMI(MBB, MIi, DL, TII->get(AArch64::STRXpre), AArch64::SP)
            .addReg(AArch64::X11)
            .addReg(AArch64::SP)
            .addImm(-16);                
        BuildMI(MBB, MIi, DL, TII->get(AArch64::STRXpre), AArch64::SP)
            .addReg(AArch64::X12)
            .addReg(AArch64::SP)
            .addImm(-16);            
        BuildMI(MBB, MIi, DL, TII->get(AArch64::STRXpre), AArch64::SP)
            .addReg(AArch64::X13)
            .addReg(AArch64::SP)
            .addImm(-16);            
        BuildMI(MBB, MIi, DL, TII->get(AArch64::STRXpre), AArch64::SP)
            .addReg(AArch64::X14)
            .addReg(AArch64::SP)
            .addImm(-16);                          
        BuildMI(MBB, MIi, DL, TII->get(AArch64::STRXpre), AArch64::SP)
            .addReg(AArch64::X15)
            .addReg(AArch64::SP)
            .addImm(-16);       
        BuildMI(MBB, MIi, DL, TII->get(AArch64::STRXpre), AArch64::SP)
            .addReg(AArch64::X16)
            .addReg(AArch64::SP)
            .addImm(-16);            
        BuildMI(MBB, MIi, DL, TII->get(AArch64::STRXpre), AArch64::SP)
            .addReg(AArch64::X17)
            .addReg(AArch64::SP)
            .addImm(-16);            
        BuildMI(MBB, MIi, DL, TII->get(AArch64::STRXpre), AArch64::SP)
            .addReg(AArch64::X18)
            .addReg(AArch64::SP)
            .addImm(-16);            
        BuildMI(MBB, MIi, DL, TII->get(AArch64::ADDXri), AArch64::X0)
            .addReg(AArch64::LR)
            .addImm(0)
            .addImm(0);                    
        BuildMI(MBB, MIi, DL, TII->get(AArch64::ADDXri), AArch64::X1)
            .addReg(AArch64::SP)
            .addImm(0)
            .addImm(0);            
        BuildMI(MBB, MIi, DL, TII->get(AArch64::ADDXri), AArch64::X2)
            .addReg(AArch64::X27)
            .addImm(0)
            .addImm(0);   
        BuildMI(MBB, MIi, DL, TII->get(AArch64::ADDXri), AArch64::X3)
            .addReg(AArch64::X28)
            .addImm(0)
            .addImm(0);      
        BuildMI(MBB, MIi, DL, TII->get(AArch64::BL)).addExternalSymbol("_ZN7QARMA6412sign_pointerEyyyy");        
        BuildMI(MBB, MIi, DL, TII->get(AArch64::ADDXri), AArch64::LR)
            .addReg(AArch64::X0)
            .addImm(0)
            .addImm(0); 
        BuildMI(MBB, MIi, DL, TII->get(AArch64::LDRXpost), AArch64::SP)
            .addReg(AArch64::X18)
            .addReg(AArch64::SP)
            .addImm(16);            
        BuildMI(MBB, MIi, DL, TII->get(AArch64::LDRXpost), AArch64::SP)
            .addReg(AArch64::X17)
            .addReg(AArch64::SP)
            .addImm(16);            
        BuildMI(MBB, MIi, DL, TII->get(AArch64::LDRXpost), AArch64::SP)
            .addReg(AArch64::X16)
            .addReg(AArch64::SP)
            .addImm(16);                          
        BuildMI(MBB, MIi, DL, TII->get(AArch64::LDRXpost), AArch64::SP)
            .addReg(AArch64::X15)
            .addReg(AArch64::SP)
            .addImm(16);                
        BuildMI(MBB, MIi, DL, TII->get(AArch64::LDRXpost), AArch64::SP)
            .addReg(AArch64::X14)
            .addReg(AArch64::SP)
            .addImm(16);            
        BuildMI(MBB, MIi, DL, TII->get(AArch64::LDRXpost), AArch64::SP)
            .addReg(AArch64::X13)
            .addReg(AArch64::SP)
            .addImm(16);            
        BuildMI(MBB, MIi, DL, TII->get(AArch64::LDRXpost), AArch64::SP)
            .addReg(AArch64::X12)
            .addReg(AArch64::SP)
            .addImm(16);                          
        BuildMI(MBB, MIi, DL, TII->get(AArch64::LDRXpost), AArch64::SP)
            .addReg(AArch64::X11)
            .addReg(AArch64::SP)
            .addImm(16);      
        BuildMI(MBB, MIi, DL, TII->get(AArch64::LDRXpost), AArch64::SP)
            .addReg(AArch64::X10)
            .addReg(AArch64::SP)
            .addImm(16);            
        BuildMI(MBB, MIi, DL, TII->get(AArch64::LDRXpost), AArch64::SP)
            .addReg(AArch64::X9)
            .addReg(AArch64::SP)
            .addImm(16);            
        BuildMI(MBB, MIi, DL, TII->get(AArch64::LDRXpost), AArch64::SP)
            .addReg(AArch64::X8)
            .addReg(AArch64::SP)
            .addImm(16);                          
        BuildMI(MBB, MIi, DL, TII->get(AArch64::LDRXpost), AArch64::SP)
            .addReg(AArch64::X7)
            .addReg(AArch64::SP)
            .addImm(16);                
        BuildMI(MBB, MIi, DL, TII->get(AArch64::LDRXpost), AArch64::SP)
            .addReg(AArch64::X6)
            .addReg(AArch64::SP)
            .addImm(16);            
        BuildMI(MBB, MIi, DL, TII->get(AArch64::LDRXpost), AArch64::SP)
            .addReg(AArch64::X5)
            .addReg(AArch64::SP)
            .addImm(16);            
        BuildMI(MBB, MIi, DL, TII->get(AArch64::LDRXpost), AArch64::SP)
            .addReg(AArch64::X4)
            .addReg(AArch64::SP)
            .addImm(16);                          
        BuildMI(MBB, MIi, DL, TII->get(AArch64::LDRXpost), AArch64::SP)
            .addReg(AArch64::X3)
            .addReg(AArch64::SP)
            .addImm(16);       
        BuildMI(MBB, MIi, DL, TII->get(AArch64::LDRXpost), AArch64::SP)
            .addReg(AArch64::X2)
            .addReg(AArch64::SP)
            .addImm(16);            
        BuildMI(MBB, MIi, DL, TII->get(AArch64::LDRXpost), AArch64::SP)
            .addReg(AArch64::X1)
            .addReg(AArch64::SP)
            .addImm(16);            
        BuildMI(MBB, MIi, DL, TII->get(AArch64::LDRXpost), AArch64::SP)
            .addReg(AArch64::X0)
            .addReg(AArch64::SP)
            .addImm(16);                
    }
}