This write up is for the input2 reverse engineering challenge

First, I run file then I open this binary up in Ghidra
```C
undefined8 main(void)

{
  int iVar1;
  int iVar2;
  long in_FS_OFFSET;
  undefined1 local_28 [24];
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  setvbuf(stdout,(char *)0x0,2,0);
  setvbuf(stderr,(char *)0x0,2,0);
  puts("Please enter the password: ");
  read(0,local_28,19);
  iVar1 = check1(local_28);
  iVar2 = check2(local_28);
  if ((iVar1 != 0) && (iVar2 != 0)) {
    puts("Congratulations!");
    system("cat flag.txt");
    if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail();
    }
    return 0;
  }
  puts("You lose!");
                    /* WARNING: Subroutine does not return */
  exit(0);
}
```
I see that there are two variables that get values from the functions check1() and check2. All I need for the flag to be printed is for both of these variables to not be 0/false.


```C
bool check1(long param_1)

{
  undefined4 i;
  
  for (i = 0; *(char *)(param_1 + i) != '\0'; i = i + 1) {
  }
  return i == 15;
}
```
Check1() returns true if my input is 15 characters/bytes long.
```C
undefined8 check2(long param_1)

{
  int i;
  
  i = 0;
  while( true ) {
    if (14 < i) {
      return 1;
    }
    if ((buffers[(long)(i % 3) * 15 + (long)i] ^ *(byte *)(param_1 + i)) != final[14 - i]) break;
    i = i + 1;
  }
  return 0;
}
```
Check2() is more complex, but we just need the loop to increment more than 14 times. We do this by giving the program the right input to meet condidtions in the if statment.
In the if statement, it first finds the index by finding the modulo i and 3, then adds i. From there, it XORs by the value of i in the input and compares it to final buffer. If it
is not equal, it will break and return 0.

I then wrote a script to recreate the password by undoing the XOR to find the input needed using the buffers and final extracted from ghidra.

```python
#!/usr/bin/env python3

def reconstruct(buffers: list[int], final: list[int]) -> bytes:

    out = bytearray(15)
    for i in range(15):
        idx = i + 15 * (i % 3)
        out[i] = buffers[idx] ^ final[14 - i]
    return bytes(out)

def main():

    buffers = [
        0xA8, 0x66, 0xE5, 0xA2, 0xAF, 0x8D, 0x7E, 0xB2, 0xC7, 0xC6,
        0x98, 0x95, 0x65, 0x12, 0xEE, 0x45, 0xE8, 0xE4, 0x22, 0x84,
        0xC6, 0xE9, 0xB9, 0xAA, 0x61, 0x73, 0xD0, 0x0F, 0xB6, 0xA6,
        0xDE, 0x06, 0xD4, 0xBB, 0xE0, 0x96, 0x68, 0xE8, 0xC6, 0x44,
        0x88, 0x0A, 0x30, 0xC8, 0x54,
    ]


    final = [
        0x84, 0xE7, 0xCC, 0x30, 0x10,
        0x7F, 0xFE, 0x40, 0xE2, 0x4D,
        0xB9, 0x99, 0x9C, 0x18, 0x03,
    ]

    required = reconstruct(buffers, final)

    # Show the result
    print("input:", required.hex())

if __name__ == "__main__":
    main()

```
I then just sent this as bytes to the program using a python script to get the flag

```python
#!/usr/bin/env python3 
import subprocess
from pwn import *

binary_path = './input2' # exe
libc_path = ''
remote_host = 'www.cweaccessionsctf.com'
remote_port = 1405 # <-- Needs to be a valid integer if using REMOTE

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
    s = bytes.fromhex('abf0483b3ddb9cf938b9633aa951d0') +b'\x00'
    payload = b''
    payload += s

    p.sendline(payload)

    p.interactive()

if __name__ == '__main__':
    main()
```

At first it did not work but I just needed to null terminate the byte string

CWE{g3tt!ng_p@sT_$ecuritY_r_w3_9sRgGhFC}

