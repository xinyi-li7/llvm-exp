#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/InstrTypes.h"
#include "llvm/IR/IntrinsicInst.h"
#include "llvm/IR/DebugInfoMetadata.h"




#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"
#include "llvm/IR/DebugInfo.h"
#include <string>
#include <iostream>
#include <sstream>


using namespace llvm;
namespace {
    struct printDireName:public FunctionPass { // operate on a funcction at a time
        static char ID;
        printDireName() : FunctionPass(ID) {}
        bool runOnFunction(Function &F) override {
            for (auto &B : F) {
                for (auto &I : B) {
                    //if (isa<BinaryOperator>(&I)) {
                    if (const DbgDeclareInst* DbgDeclare = dyn_cast<DbgDeclareInst>(&I)) 
                    {
                        DILocalVariable* DILocalV = DbgDeclare->getVariable();
                        errs() << "In DbgDeclare, and the variable is: " << DILocalV->getName() << "\n"; 
                    } 
                    else if (const DbgValueInst* DbgValue = dyn_cast<DbgValueInst>(&I)) 
                    {
                        DILocalVariable* DILocalV = DbgValue->getVariable();
                        errs() << "In DbgValue, and the variable is: " << DILocalV->getName() << "\n"; 
                    }
                }
                    //}
            }
        return false;// We didn't modify the code.
        }
    };

char printDireName::ID = 2; //LLVM uses ID’s address to identify a pass, so initialization value is not important.

static RegisterPass<printDireName> T("printDireName", "Print the direct name of variable in the definition",false, false);

static RegisterStandardPasses S(
    PassManagerBuilder::EP_EarlyAsPossible,
    [](const PassManagerBuilder &Builder,
       legacy::PassManagerBase &PM) { PM.add(new printDireName()); });

}