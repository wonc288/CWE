# Pwntools Cheat Sheet and Guide

Pwntools is a powerful Python library used for CTFs and binary exploitation. This guide summarizes its core features with examples.

---

## Installation

```bash
pip install pwntools
```

---

## Basic Imports

```python
from pwn import *
```

---

## Running Binaries Locally

```python
p = process('./binary')
p.recv()        # Receive output
p.sendline(b'input')
p.interactive() # Get interactive shell
```

---

## Connecting Remotely

```python
p = remote('host', port)
```

---

## Sending Data

```python
p.send(b'data')
p.sendline(b'data')
```

---

## Receiving Data

```python
p.recv()                 # Read any amount
p.recvline()             # Read one line
p.recvuntil(b'> ')       # Read until specific bytes
```

---

## ELF and Libc Handling

```python
elf = ELF('./binary')
libc = ELF('./libc.so.6')
print(elf.symbols['main'])
```

---

## Gadgets and ROP (Return-Oriented Programming)

```python
rop = ROP(elf)
rop.call('puts', [elf.got['puts']])  # Call puts with argument
rop.call('main')                     # Return to main
print(rop.dump())                    # Print the ROP chain
```

### ROP Functions Explained:

* `ROP(elf)`: Initializes a ROP object using the given ELF binary. Automatically finds all available gadgets.
* `rop.call(function, [args])`: Adds a function call to the ROP chain with optional arguments. You can pass addresses or function names.
* `rop.find_gadget(['ret'])`: Finds a specific gadget (e.g., `ret`, `pop rdi; ret`).
* `rop.raw(address)`: Manually append a raw address to the chain.
* `rop.dump()`: Shows a human-readable summary of the constructed ROP chain.
* `rop.chain()`: Converts the constructed ROP chain to a byte payload ready for sending.

---

## Packing and Unpacking

```python
p64() # Pack to 8 bytes
u64() # Unpack to int
p32(0xdeadbeef) # Pack to 4 bytes
u32(b'\xef\xbe\xad\xde') # Unpack to int
```

---

## Format String Exploits

```python
payload = fmtstr_payload(offset, {addr: value})
```

---

## Useful Settings

```python
context.binary = './binary'
context.log_level = 'debug' # or 'info', 'error'
context.terminal = ['tmux', 'splitw', '-h']
```

---

## Debugging with GDB

```python
p = gdb.debug('./binary', '''
b *main
c
''')
```

---

## Sample Exploit Template

```python
from pwn import *

context.binary = './vuln'
elf = context.binary
p = process(elf.path)

payload = b'A' * offset + p32(elf.symbols['win'])
p.sendline(payload)
p.interactive()
```

---


---

## Reference

* Docs: [https://docs.pwntools.com/](https://docs.pwntools.com/)
* GitHub: [https://github.com/Gallopsled/pwntools](https://github.com/Gallopsled/pwntools)
