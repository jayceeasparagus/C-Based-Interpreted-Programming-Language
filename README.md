# jh: C-Based Interpreted Programming Language

**jh** is an **interpreted programming language** implemented in **C**.  
The language is inspired by HDL-style modular design, with an emphasis on simplicity, clarity, and clean implementation.

---

## Language Features

- Variables
- Arithmetic and boolean logic
- Bitwise operations and binary literals
- Control flow statements
- Loop constructs
- Modules with defined inputs and outputs

---

## Architecture and Functionality

- **Lexer**  
  Converts source code into a stream of tokens representing keywords, identifiers, operators, and literals.

- **Parser**  
  Uses a recursive-descent approach to parse tokens and construct an **Abstract Syntax Tree (AST)** representing program structure.

- **Abstract Syntax Tree (AST)**  
  A tree-based representation of the program used during evaluation.

- **Environment (Env)**  
  A stack-based environment system that maps variable names to values and supports lexical scoping through parent environments.

- **Evaluator (Eval)**  
  Traverses and evaluates the AST to execute programs directly using a tree-walking interpreter.

---

## Running jh

1. Build or obtain the `jh` executable.
2. Place the executable in the project directory.
3. Run a jh program using:

```bash
./jh <filepath>
