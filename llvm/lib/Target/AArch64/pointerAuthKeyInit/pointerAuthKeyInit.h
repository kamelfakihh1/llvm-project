#ifndef POINTER_AUTH_KEY_INIT_H
#define POINTER_AUTH_KEY_INIT_H

#include "llvm/Pass.h"
#include "llvm/CodeGen/MachineFunctionPass.h"
#include "llvm/Target/TargetIntrinsicInfo.h"
#include "llvm/Target/TargetMachine.h"
#include "llvm/Target/TargetOptions.h"

using namespace llvm;

namespace llvm {
  FunctionPass *createPointerAuthKeyInit();
  void initializePointerAuthKeyInitPass(PassRegistry &);
} // namespace llvm

namespace {
  struct PointerAuthKeyInit : public MachineFunctionPass {

    static char ID; // Pass identification, replacement for typeid

    PointerAuthKeyInit() : MachineFunctionPass(ID) {
      initializePointerAuthKeyInitPass(*PassRegistry::getPassRegistry());
    }
    StringRef getPassName() const override { return "pointerAuth key pass"; }

    virtual bool runOnMachineFunction(MachineFunction &MF) override;
  };
} // namespace

#endif