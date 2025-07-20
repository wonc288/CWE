Binary exploitation  -> Analyzing and manipulating a binary in order to make it do what you want, often this ends in RCE(remote code execution)

EXE Protections
  - Canary
  - PIE(Position Independendent Executable)
  - NX
  - RELRO(Relocation Read Only)
  - Stripping

Common Vulnerabilities
  - Buffer Overflow
  - Format Strings
  - Shellcode Injection
  - Pivot
  - Use-After free
  - Heap overflow
  - ROP(Return Oriented Programming)

Tools
 - Ghidra -> NSA C reverse engineering
 - GDB/GEF/PWNDBG -> Debuggers
 - Radare2 -> Reverse engineering tool
 - Pwntools -> Script writing aid
 - One_Gadget -> Find shell in libc
 - Cyclic -> Help find buffer offsets
