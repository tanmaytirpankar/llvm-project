# This component is called LLVMLLVM2SatireTranspiler because the PassBuilder
# removes the first LLVM from the name when adding the dependency to the CMakelists.txt.
# Unfortunately the target is now registered as LLVMLLVM2SatireTranspiler.
add_llvm_component_library(LLVMLLVM2SatireTranspiler
    LLVM2SatireTranspiler.cpp

    ADDITIONAL_HEADER_DIRS
    ${LLVM_MAIN_INCLUDE_DIR}/llvm/Transforms
    ${LLVM_MAIN_INCLUDE_DIR}/llvm/Transforms/LLVM2SatireTranspiler
)