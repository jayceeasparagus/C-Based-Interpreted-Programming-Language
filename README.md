C-Based Interpreted Programming Language

This is a interpreted programming language I made in C.  This is a progamming language inspired by HDL languages, made to be easy to use.  An example program is provided.  My C program interprets it and outputs its result.
The language features variables, printing, control flow, loops, and modules.

The program uses a lexer to make tokens, parser that uses ast for structure, eval to run the parsed program, and env for stack-based scoping variables.

To run the interpreter, get the executable and run: "./jh 'file_path'"
