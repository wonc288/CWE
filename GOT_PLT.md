# Global Offset Table & Procedure Linkage Table

GOT:

The global offset table is a section in a program that holds the addresses of dynamically linked functions. Most programs use partial RELRO, meaning that they are lazily linked. Programs will try and reduce binary size by not loading every single dynamically linked function(such as libc) into the GOT; they will only be added once the function is called. However, if full RELRO is active, one cannot write to the GOT, and all functions will be present. If Full RELRO is not active there is the possibility for a GOT overwrite.


PLT:

The procedure linkage table is a mechanism used in the ELF format and includes instructions in order to call a function. If it is lazily linked the PLT will run a procedure to resolve the function that is called to the GOT, and from that point on, the GOT will include that address.


Lazily Linked :

[Your Code]
   |
   | calls
   v
puts@plt (in binary)
   |
   | indirect jmp → GOT entry (puts@got)
   |
   | first time: GOT holds address of resolver stub → _dl_runtime_resolve
   |-------------------------------------------------------------|
   |                       Dynamic Linker                        |
   | Resolves real libc address of puts()                        |
   | Updates GOT: puts@got ← real address of puts in libc        |
   |-------------------------------------------------------------|
   |
   |→ Subsequent calls use puts@got directly (no more resolving)


Eager binding:

[Program Start]
   |
   |-- Dynamic linker resolves all needed symbols
   |-- Writes real addresses into GOT (e.g., puts@got ← libc puts)
   |-- Marks GOT read-only
   |
[Your Code]
   |
   v
puts@plt
   |
   v
puts@got → libc puts()    ← already resolved at startup!



