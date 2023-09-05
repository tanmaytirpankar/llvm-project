#include "llvm/Transforms/LLVM2SatireTranspiler/LLVM2SatireTranspiler.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/Constants.h"
#include <fstream>
#include <regex>

using namespace llvm;

PreservedAnalyses LLVM2SatirePass::run(Module &M, ModuleAnalysisManager &AM) {
  std::string FuncName;
  std::ofstream Outfile;

  //------------------------------ INPUTS --------------------------------------


  for (auto &G : M.globals()) {
    // Store Function name in a variable and create a file
    if(G.getName() == "func") {
      // Copy value from global variable
      FuncName = dyn_cast<ConstantDataArray>(G.getInitializer())->getAsCString().str();
      // Create a .txt file with FuncName as the name
      Outfile.open(FuncName + ".txt");

      Outfile << "INPUTS {\n";
    }
  }

  // Loop through and list the global variables in the module
  for (GlobalVariable &G : M.globals()) {
    // Store Function name in a variable and create a file
    if(G.isConstant() && G.getValueType()->isArrayTy()
        && G.getValueType()->getArrayElementType()->isFloatingPointTy()) {
      //      errs() << *G.getInitializer() << "\n";
      Outfile << "\t" << G.getName().str();

      if(G.getValueType()->getArrayElementType()->isHalfTy())
        Outfile << " fl16 : (";
      else if(G.getValueType()->getArrayElementType()->isFloatTy())
        Outfile << " fl32 : (";
      else if(G.getValueType()->getArrayElementType()->isDoubleTy())
        Outfile << " fl64 : (";
      else
        errs() << "ERROR: Unsupported floating point type\n";

      unsigned int I = 0;
      // Satire currently supports half, float and double

      Outfile << dyn_cast<ConstantFP>(G.getInitializer()->getAggregateElement(I))->getValue().convertToDouble();
      Outfile << ", ";

      I = 1;
      Outfile << dyn_cast<ConstantFP>(G.getInitializer()->getAggregateElement(I))->getValue().convertToDouble();
      Outfile << ");\n";
    }

//    errs() << FuncName;
//    errs() << "\tGlobal variable " << G.getName() << "\n";
  }
  Outfile << "}\n";

  //----------------------------------------------------------------------------

  //----------------------------- OUTPUTS -------------------------------------

  // Write the following in outfile replacing output variable with the global variable
  // with null pointer value
  //  OUTPUTS {
  //    output_variable;
  //  }
  Outfile << "OUTPUTS {\n";
  for (GlobalVariable &G : M.globals()) {
    if(G.getInitializer()->isNullValue()) {
      Outfile << "\t" << G.getName().str() << ";\n";
    }
  }
  Outfile << "}\n";

  //---------------------------------------------------------------------------

  //----------------------------- EXPRS -------------------------------------

  // Write and EXPRS block in outfile containing expressions in Satire DSL
  Outfile << "EXPRS {\n";
  for (auto &F : M) {
    if (F.getName().str().find(FuncName) != std::string::npos) {
      for (auto &BB : F) {
        std::cmatch Cm;

        for (auto &I : BB) {
          // Handle arithmetic operations
          if(I.getOpcode() == Instruction::FAdd) {
            Outfile << "\t" << I.getName().str() << " = "
                    << I.getOperand(0)->getName().str() << " + "
                    << I.getOperand(1)->getName().str() << ";\n";
          }
          else if(I.getOpcode() == Instruction::FSub) {
            Outfile << "\t" << I.getName().str() << " = "
                    << I.getOperand(0)->getName().str() << " - "
                    << I.getOperand(1)->getName().str() << ";\n";
          }
          else if(I.getOpcode() == Instruction::FMul) {
            Outfile << "\t" << I.getName().str() << " = "
                    << I.getOperand(0)->getName().str() << " * "
                    << I.getOperand(1)->getName().str() << ";\n";
          }
          else if(I.getOpcode() == Instruction::FDiv) {
            Outfile << "\t" << I.getName().str() << " = "
                    << I.getOperand(0)->getName().str() << " / "
                    << I.getOperand(1)->getName().str() << ";\n";
          }
          else if(I.getOpcode() == Instruction::FRem) {
            errs() << "ERROR: Satire does not support remainder operation\n";
          }
          // If the instruction is an llvm intrinsic function call to llvm.sin
          else if(I.getOpcode() == Instruction::Call){
            std::string Str;
            llvm::raw_string_ostream(Str) << I;
            if(std::regex_search(Str.c_str(), Cm,
                                  std::regex("s*sinh*"))) {
              Outfile << "\t" << I.getName().str() << " = "
                      << "sinh(" << I.getOperand(0)->getName().str() << ");\n";
            } else if(std::regex_search(Str.c_str(), Cm,
                                         std::regex("s*cosh*"))) {
              Outfile << "\t" << I.getName().str() << " = "
                      << "cosh(" << I.getOperand(0)->getName().str() << ");\n";
            } else if(std::regex_search(Str.c_str(), Cm,
                   std::regex("s*sin*"))) {
              Outfile << "\t" << I.getName().str() << " = "
                      << "sin(" << I.getOperand(0)->getName().str() << ");\n";
            } else if(std::regex_search(Str.c_str(), Cm,
                                         std::regex("s*cos*"))) {
              Outfile << "\t" << I.getName().str() << " = "
                      << "cos(" << I.getOperand(0)->getName().str() << ");\n";
            } else if(std::regex_search(Str.c_str(), Cm,
                                         std::regex("s*tan*"))) {
              Outfile << "\t" << I.getName().str() << " = "
                      << "tan(" << I.getOperand(0)->getName().str() << ");\n";
            } else if(std::regex_search(Str.c_str(), Cm,
                                         std::regex("s*cot*"))) {
              Outfile << "\t" << I.getName().str() << " = "
                      << "cot(" << I.getOperand(0)->getName().str() << ");\n";
            } else if(std::regex_search(Str.c_str(), Cm,
                                         std::regex("s*asin*"))) {
              Outfile << "\t" << I.getName().str() << " = "
                      << "asin(" << I.getOperand(0)->getName().str() << ");\n";
            } else if(std::regex_search(Str.c_str(), Cm,
                                         std::regex("s*sqrt*"))) {
              Outfile << "\t" << I.getName().str() << " = "
                      << "sqrt(" << I.getOperand(0)->getName().str() << ");\n";
            } else if(std::regex_search(Str.c_str(), Cm,
                                         std::regex("s*log*"))) {
              Outfile << "\t" << I.getName().str() << " = "
                      << "log(" << I.getOperand(0)->getName().str() << ");\n";
            } else if(std::regex_search(Str.c_str(), Cm,
                                         std::regex("s*exp*"))) {
              Outfile << "\t" << I.getName().str() << " = "
                      << "exp(" << I.getOperand(0)->getName().str() << ");\n";
            }
          }
        }

      }
    }
  }
  Outfile << "}\n";
  Outfile.close();

  //-------------------------------------------------------------------------
//  errs() << "\n" << M.getName() << "\n";
//
//  for (auto &F : M) {
//    if (F.getName().str().find(FuncName) != std::string::npos) {
//      errs()<< "Found function " << F.getName() << "\n";
//    }
//    errs() << "\tFunction " << F.getName() << " has " << F.size() << " basic blocks.\n";
//    for (auto &BB : F) {
//      errs() << "\t\tBasic block " << BB.getName() << " has " << BB.size() << " instructions.\n";
//      for (auto &I : BB) {
//        errs() << "\t\t\tInstruction " << I.getOpcodeName() << "\n";
//      }
//    }
//  }



  return PreservedAnalyses::all();
}


