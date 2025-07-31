# Surveying

Checksec: Use to find initial defences

File: Basic file metadata

Return Address: rbp + 8

Canary: Starts with 00

Libc: 0x7ffff

64-bit: stack starts at 6th format argument, the rest are pushed to registers

32-bit: arguments passed to the stack

PIE: Look for any constant address in program memory ie. saved rbp right before return

Shellcode: if using shellcraft make sure to set context and check if you have enough room in the buffer


