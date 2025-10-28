# PVM - Python Virtual Machine

A minimal, educational implementation of a **stack-based virtual machine** that executes Python bytecode, written in C. This project demonstrates the core concepts of how Python interpreters work at a low level.

## Table of Contents
- [Overview](#overview)
- [What is a Virtual Machine?](#what-is-a-virtual-machine)
- [Architecture](#architecture)
- [Supported Operations](#supported-operations)
- [Project Structure](#project-structure)
- [How It Works](#how-it-works)
- [Building and Running](#building-and-running)
- [Example Programs](#example-programs)
- [Educational Concepts](#educational-concepts)
- [Learning Resources](#learning-resources)

## Overview

PVM is a simplified Python Virtual Machine that can:
- Parse and execute Python bytecode (.pyc files)
- Support basic arithmetic operations
- Handle variables and constants
- Execute comparison operations
- Implement control flow (if/else, while loops)
- Print output

This project is designed for learning how interpreters and virtual machines work internally.

## What is a Virtual Machine?

A **Virtual Machine (VM)** is an emulation of a computer system that executes instructions in an abstract, platform-independent manner. Instead of running directly on hardware, code is compiled to **bytecode** - an intermediate representation that the VM interprets and executes.

### Why Use a VM?

1. **Platform Independence**: Write once, run anywhere
2. **Security**: Sandboxed execution environment
3. **Memory Management**: Automatic garbage collection
4. **Optimization**: JIT compilation opportunities

### Stack-Based vs Register-Based VMs

This implementation uses a **stack-based architecture**:

- **Stack-Based** (Python, Java, .NET):
  - Operations use an implicit operand stack
  - Simpler to implement
  - More compact bytecode
  - Example: `PUSH 5`, `PUSH 3`, `ADD` → Result: 8 on stack

- **Register-Based** (Lua, Dalvik):
  - Operations specify register operands explicitly
  - Fewer instructions needed
  - More complex implementation

## Architecture

### Core Components

```
┌─────────────────────────────────────────┐
│         Python Source Code              │
│            (e.g., final.py)             │
└──────────────────┬──────────────────────┘
                   │
                   ▼
┌─────────────────────────────────────────┐
│         Python Compiler                 │
│      (generates .pyc bytecode)          │
└──────────────────┬──────────────────────┘
                   │
                   ▼
┌─────────────────────────────────────────┐
│           Bytecode File                 │
│  (hex opcodes + constants section)      │
└──────────────────┬──────────────────────┘
                   │
                   ▼
┌─────────────────────────────────────────┐
│         PVM (vm2.c)                     │
│  ┌───────────────────────────────────┐  │
│  │    Instruction Pointer (IP)       │  │
│  │    Points to current opcode       │  │
│  └───────────────────────────────────┘  │
│  ┌───────────────────────────────────┐  │
│  │    Operand Stack                  │  │
│  │    [value1, value2, value3, ...]  │  │
│  └───────────────────────────────────┘  │
│  ┌───────────────────────────────────┐  │
│  │    Constants Table                │  │
│  │    [const1, const2, ...]          │  │
│  └───────────────────────────────────┘  │
│  ┌───────────────────────────────────┐  │
│  │    Variable Storage               │  │
│  │    [var1, var2, ...]              │  │
│  └───────────────────────────────────┘  │
└─────────────────────────────────────────┘
                   │
                   ▼
┌─────────────────────────────────────────┐
│           Program Output                │
└─────────────────────────────────────────┘
```

### Execution Model

The VM follows a **fetch-decode-execute cycle**:

1. **Fetch**: Read the next opcode from the bytecode stream
2. **Decode**: Identify the operation and its operands
3. **Execute**: Perform the operation (manipulate stack, jump, etc.)
4. **Repeat**: Continue until the program ends

## Supported Operations

### Opcode Reference

| Opcode | Name          | Description                                    | Stack Effect      |
|--------|---------------|------------------------------------------------|-------------------|
| `0x64` | LOAD_CONST    | Push constant onto stack                       | → value           |
| `0x5a` | STORE_NAME    | Pop stack and store in variable slot           | value →           |
| `0x65` | LOAD_NAME     | Load variable onto stack                       | → value           |
| `0x47` | PRINT_ITEM    | Print top of stack                             | value →           |
| `0x48` | PRINT_NEWLINE | Print newline character                        |                   |
| `0x17` | ADD           | Add two numbers                                | a, b → (a+b)      |
| `0x18` | SUBTRACT      | Subtract two numbers                           | a, b → (b-a)      |
| `0x14` | MULTIPLY      | Multiply two numbers                           | a, b → (a*b)      |
| `0x15` | DIVIDE        | Divide two numbers                             | a, b → (b/a)      |
| `0x16` | MODULO        | Modulo operation                               | a, b → (b%a)      |
| `0x6b` | COMPARE_OP    | Compare two values (<, <=, ==, !=, >, >=)     | a, b → result     |
| `0x72` | POP_JUMP_IF_FALSE | Jump if top of stack is false            | value →           |
| `0x6e` | JUMP_FORWARD  | Unconditional relative forward jump            |                   |
| `0x71` | JUMP_ABSOLUTE | Jump to absolute bytecode position             |                   |
| `0x57` | NOP           | No operation                                   |                   |

### Example Bytecode Execution

For Python code: `c = a + b`

```
LOAD_NAME    0    ; Load variable 'a' → stack: [a_value]
LOAD_NAME    1    ; Load variable 'b' → stack: [a_value, b_value]
ADD               ; Pop both, add, push result → stack: [result]
STORE_NAME   2    ; Store in variable 'c' → stack: []
```

## Project Structure

```
pvm/
├── vm2.c          # Main VM interpreter (executes bytecode)
├── convert.c      # Bytecode parser/debugger utility
├── con.c          # Simple byte-to-ASCII converter
├── vm2            # Compiled VM executable
├── convert        # Compiled converter executable
├── con            # Compiled con executable
├── *.py           # Test Python programs
├── *.pyc          # Compiled bytecode files
└── README.md      # This file
```

### Source Files

#### `vm2.c` - The Virtual Machine
- **Stack management**: `push()`, `pop()`
- **Bytecode parsing**: `get_op()`, `get_const()`
- **Arithmetic operations**: `add()`, `sub()`, `mul()`, `div()`, `mod()`
- **Comparison operations**: `comp()`
- **Control flow**: `jump_f()`, `jump_fwd()`, `jump_absolute()`
- **I/O operations**: `print_item()`, `print_line()`
- **Main execution loop**: Fetch-decode-execute cycle

#### `convert.c` - Bytecode Analyzer
Utility for debugging bytecode files - displays opcodes and constants in human-readable format.

#### `con.c` - Byte Converter
Simple tool to view raw bytecode values as decimal numbers.

## How It Works

### Step-by-Step Execution

1. **Compilation**: Python source is compiled to bytecode
   ```bash
   python -m py_compile final.py  # Creates final.pyc
   ```

2. **Loading**: VM reads bytecode file
   - `get_op()`: Extracts opcode sequence
   - `get_const()`: Parses constant pool

3. **Execution**: VM processes each opcode
   ```c
   while(li < i) {
       switch (op[li++]) {
           case 0x64:  // LOAD_CONST
               load_cons(operand);
               break;
           // ... other opcodes
       }
   }
   ```

4. **Output**: Results printed to stdout

### Example: Variable Assignment

Python code:
```python
a = 5
b = 3
c = a + b
print c
```

Bytecode execution:
```
1. LOAD_CONST 0    → Stack: [5]
2. STORE_NAME 0    → Stack: [], Vars: {a: 5}
3. LOAD_CONST 1    → Stack: [3]
4. STORE_NAME 1    → Stack: [], Vars: {a: 5, b: 3}
5. LOAD_NAME 0     → Stack: [5]
6. LOAD_NAME 1     → Stack: [5, 3]
7. ADD             → Stack: [8]
8. STORE_NAME 2    → Stack: [], Vars: {a: 5, b: 3, c: 8}
9. LOAD_NAME 2     → Stack: [8]
10. PRINT_ITEM     → Output: "8", Stack: []
11. PRINT_NEWLINE  → Output: "\n"
```

## Building and Running

### Prerequisites
- GCC or any C compiler
- Python 2.x (for generating bytecode)

### Compilation

```bash
# Compile the VM
gcc vm2.c -o vm2

# Compile utilities (optional)
gcc convert.c -o convert
gcc con.c -o con
```

### Usage

```bash
# 1. Create Python source file
echo 'print 5 + 3' > test.py

# 2. Compile to bytecode
python -m py_compile test.py

# 3. Run on PVM
./vm2 < test.pyc
```

### Running Examples

```bash
# Simple arithmetic
./vm2 < sam.pyc

# Prime number finder (finds all primes < 1000)
./vm2 < final.pyc
```

## Example Programs

### Simple Arithmetic (`sam.py`)
```python
a = 8
b = 2
c = a - b
print c
```
Output: `6`

### Prime Number Finder (`final.py`)
```python
i = 2
s = 0

while i < 1000:
    j = 2
    while j < i:
        if i % j == 0:
            s = 1
        j = j + 1
    if s == 0:
        print i
    s = 0
    i = i + 1
```
Output: All prime numbers less than 1000

## Educational Concepts

This project teaches fundamental concepts in:

### 1. Interpreter Design
- How high-level code is translated to low-level operations
- The role of bytecode as an intermediate representation
- Instruction set architecture design

### 2. Stack-Based Computation
- How expressions are evaluated using a stack
- Reverse Polish Notation (RPN) evaluation
- Stack frame management

### 3. Control Flow Implementation
- How if/else statements compile to conditional jumps
- How loops are implemented with jump instructions
- Program counter manipulation

### 4. Bytecode Format
- Two's complement representation
- Little-endian vs big-endian encoding
- Constant pool design

### 5. Virtual Machine Architecture
- Fetch-decode-execute cycle
- Opcode dispatch mechanisms (switch-based interpretation)
- Memory layout (stack, constants, variables)

## Learning Resources

### Virtual Machine & Interpreter Theory
- [Crafting Interpreters](https://craftinginterpreters.com/) - Free online book on building interpreters
- [Write a VM in Python](https://csl.name/post/vm/) - Tutorial on building a simple VM
- [A Python Interpreter Written in Python](https://aosabook.org/en/500L/a-python-interpreter-written-in-python.html) - By Allison Kaptur

### Python Internals
- [Python Bytecode Documentation](https://docs.python.org/3/library/dis.html) - Official dis module docs
- [Inside the Python Virtual Machine](https://leanpub.com/insidethepythonvirtualmachine) - Deep dive into CPython
- [Your Guide to the CPython Source Code](https://realpython.com/cpython-source-code-guide/) - CPython internals tutorial

### Stack-Based VMs
- [Understanding Stack-Based Virtual Machines](https://andreabergia.com/stack-based-virtual-machines/) - Explanation of stack VMs
- [Java Virtual Machine Specification](https://docs.oracle.com/javase/specs/jvms/se8/html/) - Stack-based VM design
- [WebAssembly Design](https://webassembly.github.io/spec/core/intro/introduction.html) - Modern stack-based VM

### Bytecode & Compilation
- [Python Bytecode Adventures](https://www.youtube.com/watch?v=mxjv9KqzwjI) - Talk on Python bytecode
- [Bytecode Alliance](https://bytecodealliance.org/) - Modern bytecode technologies
- [LLVM Tutorial](https://llvm.org/docs/tutorial/) - Building a language with LLVM

### Computer Architecture
- [Nand2Tetris](https://www.nand2tetris.org/) - Build a computer from first principles
- [Computer Systems: A Programmer's Perspective](http://csapp.cs.cmu.edu/) - Classic CS textbook
- [The Elements of Computing Systems](https://www.nand2tetris.org/book) - Understanding computation

### Related Projects
- [Byterun](https://github.com/nedbat/byterun) - Python VM implementation in Python (500 lines)
- [MicroPython](https://github.com/micropython/micropython) - Python for microcontrollers
- [TinyVM](https://github.com/jakogut/tinyvm) - Small, fast, lightweight VM

## Development History

This project was developed incrementally:

1. Basic arithmetic operations (`add`)
2. Extended arithmetic (`sub`, `mul`, `div`, `mod`)
3. Comparison operations (`<`, `<=`, `==`, `!=`, `>`, `>=`)
4. Control flow: if statements with conditional jumps
5. Loops: while statements with backward jumps
6. Complex programs: Nested loops (prime number finder)

## Limitations

This is an educational VM with several limitations:

- Only supports integer arithmetic (no floats, strings, lists, etc.)
- No function calls or recursion
- Limited variable storage (fixed array)
- No garbage collection
- Python 2.x bytecode only
- No error handling or exceptions
- No standard library support

## Future Enhancements

Potential improvements for learning:

- [ ] Add support for functions and CALL_FUNCTION opcode
- [ ] Implement more data types (strings, lists, dictionaries)
- [ ] Add debugging features (step-through execution, breakpoints)
- [ ] Implement garbage collection
- [ ] Support Python 3.x bytecode
- [ ] Add JIT compilation for performance
- [ ] Implement exception handling (try/except)

## Contributing

This is an educational project. Feel free to:
- Experiment with the code
- Add new opcodes and features
- Create more example programs
- Improve documentation

## License

This project is for educational purposes. Feel free to use and modify as needed for learning.

---

**Built with curiosity about how Python really works under the hood.**

For questions or discussions, please open an issue on the repository.
