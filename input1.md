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
<!--stackedit_data:
eyJoaXN0b3J5IjpbLTEwMzgwNzUyOThdfQ==
-->