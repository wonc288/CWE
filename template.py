#!/usr/bin/env python3 
import subprocess
from pwn import *

binary_path = './' # exe
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
    

    p.sendline(payload)

    p.interactive()

if __name__ == '__main__':
    main()
