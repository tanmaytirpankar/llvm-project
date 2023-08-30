#include "llvm/Transforms/LLVM2SatireTranspiler/LLVM2SatireTranspiler.h"

using namespace llvm;

PreservedAnalyses LLVM2SatirePass::run(Module &M, ModuleAnalysisManager &AM) {
  errs() << M.getName() << "\n";

  for (auto &F : M) {
    errs() << "\tFunction " << F.getName() << " has " << F.size() << " basic blocks.\n";
    for (auto &BB : F) {
      errs() << "\t\tBasic block " << BB.getName() << " has " << BB.size() << " instructions.\n";
      for (auto &I : BB) {
        errs() << "\t\t\tInstruction " << I.getOpcodeName() << "\n";
      }
    }
  }

  return PreservedAnalyses::all();
}