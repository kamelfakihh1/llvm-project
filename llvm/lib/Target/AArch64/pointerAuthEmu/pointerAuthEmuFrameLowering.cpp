#include "pointerAuthEmuFrameLowering.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/CodeGen/MachineModuleInfo.h"
#include "llvm/IR/ValueSymbolTable.h"
#include "AArch64RegisterInfo.h"
#include "AArch64InstrInfo.h"

using namespace llvm;

void pointerAuthEmuFrameLowering::instrumentEpilogue(const TargetInstrInfo *TII,
                                  MachineBasicBlock &MBB, MachineBasicBlock::iterator &MBBI,
                                  const DebugLoc &DL) 
{       
    // these functions are skipped cause they're called before key generation
    MachineFunction *MF = MBB.getParent();    
    if(MF->getName().str() == "main" || MF->getName().str() == "_GLOBAL__sub_I_main.cpp" || MF->getName().str() == "__cxx_global_var_init"){
        return;
    }

    // get Machine instruction object
    auto MIi = (MBBI != MBB.end() ? &*MBBI : nullptr);    

    // insert function call to verify pointer
    if (MIi == nullptr) {  

        // save general purpose registers (X0-X7) to the stack 
        // verify_pointer is not expected to reserve the values of these registers 
        // if an of the register values are modified inside verify_pointer 
        // the called function (of which we are instrumenting the prologue)
        // will receive invalid arguments. The same applies for Epilogues
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

        // call verify_pointer()
        // mov x0, x30
        // mov x1, sp
        // bl _ZN7QARMA6414verify_pointerEyyyy
        // mov x30, x0                                  
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

        // save restored pointer in LR
        BuildMI(&MBB, DL, TII->get(AArch64::ADDXri), AArch64::LR)
            .addReg(AArch64::X0)
            .addImm(0)
            .addImm(0);             

        // restore general purpose registers (X0-X7)                 
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

        // save general purpose registers (X0-X7) to the stack 
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

        // call verify_pointer()
        // mov x0, x30
        // mov x1, sp
        // bl _ZN7QARMA6414verify_pointerEyyyy
        // mov x30, x0               
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

        // save restored register in LR
        BuildMI(MBB, MIi, DL, TII->get(AArch64::ADDXri), AArch64::LR)
            .addReg(AArch64::X0)
            .addImm(0)
            .addImm(0);          

        // restore general purpose registers (X0-X7)                                         
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

void pointerAuthEmuFrameLowering::instrumentPrologue(const TargetInstrInfo *TII,
                                            MachineBasicBlock &MBB, MachineBasicBlock::iterator &MBBI,
                                            const DebugLoc &DL) 
{

    MachineFunction *MF = MBB.getParent();
    if(MF->getName().str() == "main"|| MF->getName().str() == "_GLOBAL__sub_I_main.cpp" || MF->getName().str() == "__cxx_global_var_init"){
        return;
    }    

    // get Machine instruction object
    auto MIi = (MBBI != MBB.end() ? &*MBBI : nullptr);

    // insert function call to sign pointer
    if (MIi == nullptr) {    

        // save general purpose registers (X0-X7) to the stack         
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

        // call sign_pointer()
        // mov x0, x30
        // mov x1, sp
        // bl _ZN7QARMA6412sign_pointerEyyyy
        // mov x30, x0   
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

        // save signed pointer in LR
        BuildMI(&MBB, DL, TII->get(AArch64::ADDXri), AArch64::LR)
            .addReg(AArch64::X0)
            .addImm(0);        

        // restore general purpose registers (X0-X7)                                  
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

        // save general purpose registers (X0-X7) to the stack 
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

        // call sign_pointer()
        // mov x0, x30
        // mov x1, sp
        // bl _ZN7QARMA6412sign_pointerEyyyy
        // mov x30, x0            
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

        // save signed pointer in LR
        BuildMI(MBB, MIi, DL, TII->get(AArch64::ADDXri), AArch64::LR)
            .addReg(AArch64::X0)
            .addImm(0)
            .addImm(0);      

        // restore general purpose registers (X0-X7)                 
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