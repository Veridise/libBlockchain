# libBlockchain

libBlockchain provides user with information about the runtime environment and the high level structure of the project
being analyzed so that analyses can be built to be chain-agnostic. It does so by providing a generic interface to users
that they can query for specific information about the execution environment. In addition, libBlockchain allows reads
"summary files" of the project being analyzed, allowing analyses to receive higher level information about the project
in question.

- [How to Build](#how-to-build)
- [Testing](#testing)

## How to Install

libBlockchain has the following depencies:
 * RapidJSON (Provided)
 * LLVM (Version 13.0.01)
 * CMake (Version 3.22.3)

To build, simply execute the following commands. 

```bash
export LLVM_HOME=<LLVM_HOME_DIR>
mkdir build && cd build
cmake -G "Unix Makefiles" ..
make
```

## Testing
To test libBlockchain, we have a llvm pass that will take a summary and the llvm bytecode of the project, then will
check the summary against the provided bytecode. It can be executed as follows:

```bash
opt --load=<PATH_TO_LIBBLOCKCHAIN> -enable-new-pm=0 --libBlockchain-test --summary=<CONTRACT_SUMMARY> <PATH_TO_LLVM_BYTECODE> -o /dev/null
```
where `<PATH_TO_LIBBLOCKCHAIN>` is the path to the vanguard `.dylib`/`.so` file (so, if running from the libBlockchain folder, this should be `build/lib/libBlockchainTest.dylib`). `<CONTRACT_SUMMARY>` is a `JSON` file specifying contract specific information; summaries can be generated for Solidity and Rust contracts using the following tools respectively: [SolidityPreprocessor](https://github.com/Veridise/SolidityPreprocessor) and [RustPreprocessor](https://github.com/Veridise/RustPreprocessor). Finally, `<PATH_TO_LLVM_BYTECODE>` is the path to the `.bc` file to be analyzed.
