#!/usr/bin/env python3
from pwn import *

elf = context.binary = ELF('./')
p = process(elf.path)


p.sendline(cyclic(2000))  # This crashes the program 

p.wait()
core = p.corefile
crash_value = core.read(core.esp, 4)  # or .esp if 32-bit rsp if 64
offset = cyclic_find(crash_value)

log.info(f"Offset is {offset}")
