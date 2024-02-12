#include "llvm/Pass.h"
#include "llvm/CodeGen/MachineFunctionPass.h"
#include "llvm/Target/TargetIntrinsicInfo.h"
#include "llvm/Target/TargetMachine.h"
#include "llvm/Target/TargetOptions.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/CodeGen/MachineModuleInfo.h"
#include "llvm/IR/ValueSymbolTable.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/PaEmu/PaEmu.h"
#include "AArch64RegisterInfo.h"
#include "AArch64InstrInfo.h"
// #include "../ARM/ARMRegisterInfo.h"
// #include "../ARM/ARMInstrInfo.h"
#include "pointerAuthKeyInit.h"
#include <iostream>

using namespace llvm;

char PointerAuthKeyInit::ID = 0;

static cl::opt<bool> EnablePAEmu("pa-emu", cl::Hidden,
                                      cl::desc("Pointer authentication emulation pass"),
                                      cl::init(false));

bool llvm::PaEmu::usePaEmu() {
  return EnablePAEmu;
}

INITIALIZE_PASS_BEGIN(PointerAuthKeyInit, "pointerAuth key", "pointerAuth key pass", false, false)
INITIALIZE_PASS_END(PointerAuthKeyInit, "pointerAuth key", "pointerAuth key pass", false, false)

FunctionPass *llvm::createPointerAuthKeyInit() { return new PointerAuthKeyInit(); }

bool PointerAuthKeyInit::runOnMachineFunction(MachineFunction &MF) {        

    if(!PaEmu::usePaEmu()){
        return false;
    }

    std::cout << MF.getName().str() << std::endl;

    const TargetInstrInfo *TII = MF.getSubtarget().getInstrInfo();

    if(MF.getName().str() == "main"){
        std::cout << "initializing PA key"<< std::endl;
        for(auto &MBB : MF){
            if(MBB.isEntryBlock()){
                MachineBasicBlock::iterator MBBI = MBB.begin();
                // MachineBasicBlock::iterator MBBI = MBB.getLastNonDebugInstr();                        

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