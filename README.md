# Semantic-Lexical-Syntax-Parser-Compiler
A C-based compiler project for a simplified Pascal language, implementing lexical, syntax, and semantic analysis based on grammar rules. Includes examples and a step-by-step guide to execution

# Pascal Analyser - A Simplified Pascal Compiler

## Introduction
This project implements a compiler for a subset of the Pascal language, designed for educational purposes. It demonstrates key concepts of lexical analysis, syntax parsing, and semantic analysis, all based on a predefined grammar.

## Features
- **Lexical Analysis**: Tokenizes the source code of a simplified Pascal program.
- **Syntax and Semantic Parsing**: Checks the structure and meaning of the program against defined grammar rules.
- **Error Handling**: Displays errors for invalid syntax or semantics.
- **Test Case Example**: Includes a sample Pascal program to test the compiler.

---

## Getting Started

### Prerequisites
- A C compiler (e.g., GCC or Clang)
- Basic knowledge of the Pascal language

### Compilation
1. Open a terminal in the project directory.
2. Compile the program using:
   ```bash
   gcc -o PascalAnalyser main.c AnalyseurLexical.c AnalyseurSemantique.c
### Execution
- Ensure the program.txt file is in the same directory as the compiled program.
- Run the program with:
- ./PascalAnalyser

### Output
- The program will:

- Perform lexical analysis and display tokens.
- Parse the program using syntax and semantic rules.
- Display any errors found in the source file.
