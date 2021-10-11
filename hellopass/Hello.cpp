#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/raw_ostream.h"

#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"

using namespace llvm;
namespace {
    struct Hello:public FunctionPass { // operate on a funcction at a time
        static char ID;
        Hello(): FunctionPass(ID) {} //This declares pass identifier used by LLVM to identify pass. 
                                     //This allows LLVM to avoid using expensive C++ runtime information.
        bool runOnFunction(Function &F) override { // Override `runOnFunction` inherited from Function Pass
            errs() << "Hello: ";
            errs().write_escaped(F.getName()) << '\n';
            return false;
        }
};

char Hello::ID = 0; //LLVM uses ID’s address to identify a pass, so initialization value is not important.

static RegisterPass<Hello> X("hello", "Hello World Pass",false, false);

static RegisterStandardPasses Y(
    PassManagerBuilder::EP_EarlyAsPossible,
    [](const PassManagerBuilder &Builder,
       legacy::PassManagerBase &PM) { PM.add(new Hello()); });

}