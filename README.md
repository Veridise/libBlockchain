# libBlockchain
libBlockchain provides user with information about the runtime environment and the high level structure of the project
being analyzed so that analyses can be built to be chain-agnostic. It does so by providing a generic interface to users
that they can query for specific information about the execution environment. In addition, libBlockchain allows reads
"summary files" of the project being analyzed, allowing analyses to receive higher level information about the project
in question.

## Dependencies
 * RapidJSON (Provided)
 * LLVM 13
 * CMake

## Build
To build, please execute the following commands. 

```bash
export LLVM_HOME=<home_llvm_dir>
mkdir build && cd build
cmake -G "Unix Makefiles" ..
make
```

## Testing
To test libBlockchain, we have a llvm pass that will take a summary and the llvm bytecode of the project, then will
check the summary against the provided bytecode. It can be executed as follows:

```bash
opt --load=build/lib/libBlockchainTest.dylib -enable-new-pm=0 --libBlockchain-test --summary=<summary> <llvm bytecode> -o /dev/null
```
