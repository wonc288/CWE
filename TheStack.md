# Understanding the Call Stack and Stack Frames in C

## Overview

The call stack is a special region of memory used by a program to:
- Keep track of function calls and their return addresses.
- Store local variables and function parameters.
- Manage control flow between functions.

It grows and shrinks dynamically during runtime, following a Last In, First Out (LIFO) structure.

When a function is called:
1. A new stack frame is created.
2. Parameters and local variables are stored in that frame.
3. When the function returns, the frame is popped off, and control returns to the caller.

---

## Stack Memory Layout (x86 / x86-64)

Memory in most architectures is divided into segments:

```
|---------------------------|  <-- High Address
|        Stack              |  (grows downward)
|---------------------------|
|        Heap               |  (grows upward)
|---------------------------|
|  Static / Global Memory   |
|---------------------------|
|        Code (Text)        |
|---------------------------|  <-- Low Address
```

The stack grows downward in memory (toward lower addresses), meaning every new allocation (like a local variable or stack frame) subtracts from the stack pointer (RSP or ESP).

---

## Anatomy of a Stack Frame

When a function is called, a stack frame (also known as an activation record) is created.

Here’s what it typically contains (x86-64 System V ABI convention):

```
           +--------------------+
High Addr  |  Arguments >6      |  (passed via stack if more than 6)
           +--------------------+
           |  Return Address    |  (saved by CALL instruction)
           +--------------------+
           |  Old Base Pointer  |  (saved RBP)
           +--------------------+
           |  Local Variables   |
           +--------------------+
Low Addr   |  Temporary Storage |
           +--------------------+
```

Registers used:
- RSP (Stack Pointer): Points to the top of the current stack.
- RBP (Base Pointer): Points to the base of the current stack frame.

---

## How Function Calls Work (Step by Step)

Example in C:

```c
int add(int a, int b) {
    int sum = a + b;
    return sum;
}

int main() {
    int x = 5;
    int y = 7;
    int z = add(x, y);
    return 0;
}
```

### 1. main() Starts

The system sets up the initial stack frame for main. Local variables x, y, and z are stored in this frame.

### 2. add(x, y) is Called

The call sequence:

#### a. Push arguments

On x86-64 (System V ABI):
- First 6 integer/pointer args go in registers: RDI, RSI, RDX, RCX, R8, R9
- Any more go on the stack.

So:
```
RDI = x (5)
RSI = y (7)
```

#### b. CALL instruction

Assembly (simplified):
```asm
call add
```

This instruction:
- Pushes the return address (the next instruction in main) onto the stack.
- Jumps to the add function.

#### c. Function prologue (in add)
When add begins, it sets up its own frame:

```asm
push rbp
mov rbp, rsp
sub rsp, 16
```

Now the stack looks like:

```
|-------------------|
| caller variables  | ← RBP of caller
| return address    |
| old RBP           | ← RBP of callee
| local vars (sum)  |
|-------------------|
```

---

### 3. Function Executes

a and b are already in registers or copied into the frame. sum = a + b executes. The result is stored in the RAX register (used for function return values).

---

### 4. Function Returns

Function epilogue (in add):
```asm
mov rsp, rbp
pop rbp
ret
```

The ret instruction:
- Pops the return address off the stack.
- Jumps to it (back into main).

---

### 5. Back to main

Execution continues after the call:
```c
int z = add(x, y);  // z now holds 12
```
The value returned in RAX is stored in z.

---

## Visual Summary

Before the call:
```
main frame:
|----------------|
|   y = 7        |
|   x = 5        |
|----------------|
RSP → top of stack
```

During the call:
```
add frame:
|----------------|
|   sum = ?      |
|----------------|
| old RBP        |
| return address |
|----------------|
main frame below
```

After return:
```
main frame:
|----------------|
|   z = 12       |
|----------------|
```

---

## Parameter Passing

- x86 (32-bit): Parameters are pushed onto the stack right to left.
- x86-64 (System V ABI):
  - Integers/pointers: First 6 → RDI, RSI, RDX, RCX, R8, R9
  - Floats: XMM0–XMM7
  - Extra arguments → on the stack.

Example:
```c
foo(int a, int b, int c, int d, int e, int f, int g);
```
Registers:
```
a → RDI
b → RSI
c → RDX
d → RCX
e → R8
f → R9
g → stack
```

---

## Return Mechanism (RET Instruction)

- ret pops the return address from the stack into the instruction pointer (RIP).
- CPU resumes execution at that address (the caller’s next instruction).
- Return value convention:
  - Integers/pointers → RAX
  - Floats → XMM0

So:
```c
return sum;  // result in RAX
```

---

## Recursive Calls

Each recursive call creates its own stack frame.

Example:
```c
int factorial(int n) {
    if (n <= 1) return 1;
    return n * factorial(n - 1);
}
```
Each call:
- Pushes a new frame with its own n.
- Waits for the return of factorial(n-1).
- Pops the frame when done.

Stack grows until base case, then unwinds back.

---

## Function Pointers and Stack

When using a function pointer:
```c
int (*fp)(int, int) = add;
int result = fp(3, 4);
```
The same calling convention applies — only the address used by CALL differs (indirect jump).

---

## Stack Overflow

Because the stack has limited size (e.g. 8 MB by default on Linux), excessive recursion or large local arrays can cause stack overflow, overwriting adjacent memory and crashing the program.

---

## Key Takeaways

| Concept | Description |
|----------|--------------|
| Call Stack | LIFO structure that stores function calls and local variables. |
| Stack Frame | Contains function parameters, return address, local vars, and saved registers. |
| RSP | Points to top of current stack. Moves with push/pop. |
| RBP | Base of current function’s stack frame. |
| CALL | Pushes return address, jumps to function. |
| RET | Pops return address, resumes caller. |
| Return Value | Passed via RAX (integer/pointer) or XMM0 (float). |

---

## Summary Diagram

```
Caller Stack Frame (main)
 ├── Local vars (x, y, z)
 ├── Return address to OS
 └── RBP (saved)

↓ CALL add(x, y)
Callee Stack Frame (add)
 ├── Local vars (sum)
 ├── Saved RBP
 ├── Return address (→ main)
 └── Parameters (a=5, b=7)
```

---

Pro tip: You can inspect stack frames in a debugger like gdb using:
```
info frame
backtrace
disassemble
```
These commands let you watch stack growth, return addresses, and register states in real time.
