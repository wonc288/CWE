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
   | indirect jump →
   v
puts@got (initially points to resolver stub)
   |
   |------------------------- First Call -------------------------|
   |                                                             |
   | puts@got → _dl_runtime_resolve (dynamic linker stub)        |
   |                                                             |
   | Dynamic Linker resolves actual libc address of puts()       |
   | Updates GOT: puts@got ← libc puts address                   |
   |-------------------------------------------------------------|
   |
   |--------------------- Subsequent Calls ----------------------|
   |                                                             |
   | puts@plt → puts@got → libc puts() (no more resolving)       |
   |-------------------------------------------------------------|



Eager binding:

[Binary is loaded]
   |
   |------------------------- Startup ---------------------------|
   |                                                             |
   | Dynamic Linker immediately resolves all symbols             |
   | GOT: puts@got ← libc puts address                           |
   |                                                             |
   | Marks GOT read-only via mprotect                           |
   |-------------------------------------------------------------|
   |
   | calls
   v
puts@plt
   |
   | indirect jump →
   v
puts@got → libc puts()




