#include "llvm/Pass.h"
#include "llvm/CodeGen/MachineFunctionPass.h"
#include "llvm/Target/TargetIntrinsicInfo.h"
#include "llvm/Target/TargetMachine.h"
#include "llvm/Target/TargetOptions.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/CodeGen/MachineModuleInfo.h"
#include "llvm/IR/ValueSymbolTable.h"
#include "llvm/Support/CommandLine.h"
#include "AArch64RegisterInfo.h"
#include "AArch64InstrInfo.h"
#include "pointerAuthKeyInit.h"
#include "llvm/PaEmu/PaEmu.h"

using namespace llvm;

char PointerAuthKeyInit::ID = 0;

// create command line option -pa-emu
// the plugin is disabled by default
static cl::opt<bool> EnablePAEmu("pa-emu", cl::Hidden,
                                      cl::desc("Pointer authentication emulation pass"),
                                      cl::init(false));

// returns true if the plugin is enabled 
bool llvm::PaEmu::usePaEmu() {
  return EnablePAEmu;
}

INITIALIZE_PASS_BEGIN(PointerAuthKeyInit, "pointerAuth key", "pointerAuth key pass", false, false)
INITIALIZE_PASS_END(PointerAuthKeyInit, "pointerAuth key", "pointerAuth key pass", false, false)

FunctionPass *llvm::createPointerAuthKeyInit() { return new PointerAuthKeyInit(); }

bool PointerAuthKeyInit::runOnMachineFunction(MachineFunction &MF) {        

    // don't instrument function if the pass is not enabled
    if(!PaEmu::usePaEmu()){
        return false;
    }    

    // get instruction info to use in building instructions
    const TargetInstrInfo *TII = MF.getSubtarget().getInstrInfo();    

    // search for main() function
    if(MF.getName().str() == "main"){        
        for(auto &MBB : MF){
            
            // insert key generation function at the start of main             
            if(MBB.isEntryBlock()){
                MachineBasicBlock::iterator MBBI = MBB.begin();

                // save general purpose registers to the stack
                BuildMI(MBB, MBBI, DebugLoc(), TII->get(AArch64::STRXpre), AArch64::SP)
                    .addReg(AArch64::X0)
                    .addReg(AArch64::SP)
                    .addImm(-16);            
                BuildMI(MBB, MBBI, DebugLoc(), TII->get(AArch64::STRXpre), AArch64::SP)
                    .addReg(AArch64::X1)
                    .addReg(AArch64::SP)
                    .addImm(-16);            
                BuildMI(MBB, MBBI, DebugLoc(), TII->get(AArch64::STRXpre), AArch64::SP)
                    .addReg(AArch64::X2)
                    .addReg(AArch64::SP)
                    .addImm(-16);                          
                BuildMI(MBB, MBBI, DebugLoc(), TII->get(AArch64::STRXpre), AArch64::SP)
                    .addReg(AArch64::X3)
                    .addReg(AArch64::SP)
                    .addImm(-16);                
                BuildMI(MBB, MBBI, DebugLoc(), TII->get(AArch64::STRXpre), AArch64::SP)
                    .addReg(AArch64::X4)
                    .addReg(AArch64::SP)
                    .addImm(-16);            
                BuildMI(MBB, MBBI, DebugLoc(), TII->get(AArch64::STRXpre), AArch64::SP)
                    .addReg(AArch64::X5)
                    .addReg(AArch64::SP)
                    .addImm(-16);            
                BuildMI(MBB, MBBI, DebugLoc(), TII->get(AArch64::STRXpre), AArch64::SP)
                    .addReg(AArch64::X6)
                    .addReg(AArch64::SP)
                    .addImm(-16);                          
                BuildMI(MBB, MBBI, DebugLoc(), TII->get(AArch64::STRXpre), AArch64::SP)
                    .addReg(AArch64::X7)
                    .addReg(AArch64::SP)
                    .addImm(-16);                                
                
                // call generate_key() function
                BuildMI(MBB, MBBI, DebugLoc(), TII->get(AArch64::BL)).addExternalSymbol("_ZN7QARMA6412generate_keyEv");                                                                                         

                // save the key in registers X27 and X28                                          
                BuildMI(MBB, MBBI, DebugLoc(), TII->get(AArch64::ADDXri), AArch64::X27)
                    .addReg(AArch64::X0)
                    .addImm(0)
                    .addImm(0);        

                BuildMI(MBB, MBBI, DebugLoc(), TII->get(AArch64::ADDXri), AArch64::X28)
                    .addReg(AArch64::X1)
                    .addImm(0)
                    .addImm(0);    

                // restore general purpose registers from the stack 
                BuildMI(MBB, MBBI, DebugLoc(), TII->get(AArch64::LDRXpost), AArch64::SP)
                    .addReg(AArch64::X7)
                    .addReg(AArch64::SP)
                    .addImm(16);                
                BuildMI(MBB, MBBI, DebugLoc(), TII->get(AArch64::LDRXpost), AArch64::SP)
                    .addReg(AArch64::X6)
                    .addReg(AArch64::SP)
                    .addImm(16);            
                BuildMI(MBB, MBBI, DebugLoc(), TII->get(AArch64::LDRXpost), AArch64::SP)
                    .addReg(AArch64::X5)
                    .addReg(AArch64::SP)
                    .addImm(16);            
                BuildMI(MBB, MBBI, DebugLoc(), TII->get(AArch64::LDRXpost), AArch64::SP)
                    .addReg(AArch64::X4)
                    .addReg(AArch64::SP)
                    .addImm(16);                          
                BuildMI(MBB, MBBI, DebugLoc(), TII->get(AArch64::LDRXpost), AArch64::SP)
                    .addReg(AArch64::X3)
                    .addReg(AArch64::SP)
                    .addImm(16);       
                BuildMI(MBB, MBBI, DebugLoc(), TII->get(AArch64::LDRXpost), AArch64::SP)
                    .addReg(AArch64::X2)
                    .addReg(AArch64::SP)
                    .addImm(16);            
                BuildMI(MBB, MBBI, DebugLoc(), TII->get(AArch64::LDRXpost), AArch64::SP)
                    .addReg(AArch64::X1)
                    .addReg(AArch64::SP)
                    .addImm(16);            
                BuildMI(MBB, MBBI, DebugLoc(), TII->get(AArch64::LDRXpost), AArch64::SP)
                    .addReg(AArch64::X0)
                    .addReg(AArch64::SP)
                    .addImm(16);    
             
            }
        }
    }
    
    return true;
}