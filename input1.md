This mark down is the solution to input1

The first thing I did was to open this up in ghidra to look at how 

```C
undefined8 main(void)

{
  long in_FS_OFFSET;
  undefined4 local_18;
  int local_14;
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  setvbuf(stdout,(char *)0x0,2,0);
  setvbuf(stderr,(char *)0x0,2,0);
  puts("Do you know the correct number to input?");
  __isoc99_scanf(&DAT_00102031,&local_18);
  local_14 = check(local_18);
  if (local_14 != 0xb88202) {
    puts("You lose!");
                    /* WARNING: Subroutine does not return */
    exit(0);
  }
  puts("Congratulations!");
  system("cat flag.txt");
  if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return 0;
}
```

```C

uint check(uint param_1)

{
  return (param_1 ^ 0x735) >> 4 ^ 0x6f0;
}
```

#!/usr/bin/env python3 
import subprocess
from pwn import *

binary_path = './input1' # exe
libc_path = ''
remote_host = 'www.cweaccessionsctf.com'
remote_port = 1400  # <-- Needs to be a valid integer if using REMOTE

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
    
    payload = b''
    payload += (b'193480725')
    p.sendline(payload)

    p.interactive()

if __name__ == '__main__':
    main()

<!--stackedit_data:
eyJoaXN0b3J5IjpbOTUyMjc5ODUyLC0xMDM4MDc1Mjk4XX0=
-->