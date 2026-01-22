# BanglaLang Interpreter

A custom-built interpreter for a toy programming language written in **C++**, inspired by Bengali keywords.  
This project demonstrates the **core internals of an interpreter**: Lexical Analysis, Parsing with AST generation and Execution.

Designed for learning **compiler design, language implementation and AST-based evaluation**.

---

## 🚀 Features
- **Data Types**: `integer`, `float`
- **Keywords**:
  - `te` – assignment / value declaration
  - `dekhao` – print to console
  - `jodi` / `nahole` – if–else control flow
- **Operations**:
  - Arithmetic: `+`, `-`, `*`, `/`
  - Comparison: `>`
- Lexer, Parser, AST, and Interpreter implemented from scratch
- Modular design for easy language extension
- Sample `.bng` programs included

---

## 🧠 Architecture Overview
- **Lexer**: Converts source code into tokens
- **Parser**: Builds an Abstract Syntax Tree (AST)
- **AST**: Represents program structure
- **Interpreter**: Walks the AST and executes logic

---

## 🛠️ Build and Run

### Prerequisites
- A C++ compiler supporting **C++17**
- GCC 7+, Clang 5+, or MSVC 2017+

---

### Using Code::Blocks
1. Create a new **Console Application (C++)**
2. Add all source files from the `src/` directory
3. Go to  
   **Project → Build Options → Compiler Settings**  
   Enable `-std=c++17`
4. To run a script, go to  
   **Project → Set programs' arguments**  
   Example:
   ```text
   examples/math.bng

## 📁 Project Structure
```text
BanglaLang/
├── src/
│   ├── main.cpp              # Entry point
│   ├── lexer.cpp / lexer.h   # Lexical analysis
│   ├── parser.cpp / parser.h # Parsing logic
│   ├── ast.h                 # AST node definitions
│   ├── interpreter.cpp / .h  # Execution engine
├── examples/                 # Sample .bng programs
└── README.md

