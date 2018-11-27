# Noveen's compiler for decaf

## Description
The project combines the `flex` scanner generator and `bison` parser using scaffolding C++ code in `class.cpp`. During parsing, the Abstract Syntax Tree (AST) is constructed.
The use of C++ allows for design patters such as the visitor pattern to pass over the AST for debugging and code generations purposes.

## File Structure
- `class.cpp` : Contains the implementation of all AST structure classes
- `class_definition.h` : Contains the definitions of AST structure classes
- `codegen.cpp` : Contains the implementation of LLVM-IR generation for all AST structure classes
- `colormod.h` : Contains the class for printing on stdout on terminal
- `decaf` : Executable for the compiler
- `flag_parsed_correct.h` : Global variables declarations
- `parser.y` : Grammar definition
- `scanner.l` : Tokenizer/Lexor
- `test_programs` : Directory containing some sample test programs

## Run
1. `make clean` - optional
2. `make`
3. `./decaf < test_programs/test_compile.dcf 2> llvm_ir.txt` - redirect generated code from `stderr` to `llvm_ir.txt` file
4. `lli-6.0 llvm_ir.txt` - Runs the generated code

## Dependencies

- `llvm-config-6.0`
- `g++-14`
- `lli-6.0`
