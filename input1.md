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

Looking this main function I can see that it prints, prompting for input. It then collects input and is sent to the check function. The returned value of that function is then saved and compared to a value. If we pass that check we can get to our flag.

```C

uint check(uint param_1)

{
  return (param_1 ^ 0x735) >> 4 ^ 0x6f0;
}
```

It looks like it just takes the parameter which in this case is the user input and does an xor, bithshift, then another xor. Ok cool, now all I have to do is use the checked value and reverse this process to find the input the program expects.

```python
result = (0xb88202 ^ 0x6f0) << 4 ^ 0x735

print(result)
```

This prints out the result 193480725

I then just use a simple script to send this payload to the program and print the flag
```python
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
```
<!--stackedit_data:
eyJoaXN0b3J5IjpbMTMzNjYxMTgxMCw5NTIyNzk4NTIsLTEwMz
gwNzUyOThdfQ==
-->