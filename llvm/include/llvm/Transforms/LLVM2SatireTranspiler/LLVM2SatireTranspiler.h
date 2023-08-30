#ifndef LLVM_LLVM2SATIRETRANSPILER_H
#define LLVM_LLVM2SATIRETRANSPILER_H

#include "llvm/IR/PassManager.h"

namespace llvm {

class LLVM2SatirePass : public PassInfoMixin<LLVM2SatirePass> {
public:
  PreservedAnalyses run(Module &M, ModuleAnalysisManager &AM);


};

} // end namespace llvm

#endif // LLVM_LLVM2SATIRETRANSPILER_H
