#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/InstrTypes.h"


#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"
#include "llvm/IR/DebugInfo.h"
#include <string>
#include <iostream>
#include <sstream>


using namespace llvm;
namespace {
    struct printLineInfo:public FunctionPass { // operate on a funcction at a time
    static char ID;
    printLineInfo() : FunctionPass(ID) {}
    bool runOnFunction(Function &F) override {
        for (auto &B : F) {
            for (auto &I : B) {
                if (isa<BinaryOperator>(&I)) {
                    if(DILocation *Loc = (&I)->getDebugLoc())
                    {
                        unsigned Line = Loc->getLine();
                        StringRef File = Loc->getFilename();
                        StringRef Dir = Loc->getDirectory();
                        bool ImplicitCode = Loc->isImplicitCode();
                        errs() << "File name is: " << File << "\n";
                        errs() << "Line number is: " << Line << "\n";
                        errs() << "Dir name is: " << Dir<< "\n";
                        errs() << "Is implicite code?  " << ImplicitCode << "\n";

                    }
                    else {
                        errs() << "No debug info" << "\n";
                    }
                }
            }
        }
        return false;// We didn't modify the code.
        }

};

char printLineInfo::ID = 1; //LLVM uses ID’s address to identify a pass, so initialization value is not important.

static RegisterPass<printLineInfo> T("printLineInfo", "Print the name of variable Pass",false, false);

static RegisterStandardPasses S(
    PassManagerBuilder::EP_EarlyAsPossible,
    [](const PassManagerBuilder &Builder,
       legacy::PassManagerBase &PM) { PM.add(new printLineInfo()); });

}