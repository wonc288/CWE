The first thing I did was to run ghidra on this binary so I could get a better understanding of what was going on. 
When looking i find that we have our input then a bunch of bitmasks.

   local_50 = 0;
  10short = 0x1010101;
  local_34 = 0x2020202;
  local_38 = 0x4040404;
  local_3c = 0x8080808;
  local_40 = 0x10101010;
  local_44 = 0x20202020;
  local_48 = 0x40404040;
  local_4c = 0x80808080

The flag that is printed within plain text was flag{r3d_h3rr1ng}, im gonna assume that not the flag but ill try it ... yea that doesnt work. I then see that all of the bit masks are being sent to another function where they are being bitwise OR'd together. 
```C
void FUN_00101160(char 1,uint 2,uint 4,uint 8,uint 10,uint 20,uint 40)

{
  if (part1 == 0) {
    putchar((int)(char)2 | 4 | 20 | 40);
    putchar((int)(char)4 | 8 | 20 | 40);
    putchar((int)1 | 20 | 40);
    putchar((int)1 | 2 | 4 | 20 | 40);
    putchar((int)1 | 2 | 8 | 10 | 20 | 40);
    part1 = 1;
  }
  if (part1 != 0) {
    putchar((int)1 | 2 | 4 | 10 | 20 | 40);
    putchar((int)(char)8 | 20 | 40);
    putchar((int)1 | 20 | 40);
    putchar((int)(char)4 | 10 | 20 | 40);
    putchar((int)1 | 2 | 4 | 8 | 10 | 40);
    putchar((int)1 | 20 | 40);
    putchar((int)1 | 2 | 4 | 8 | 10 | 40);
    putchar((int)1 | 4 | 8 | 20 | 40);
    putchar((int)1 | 4 | 20 | 40);
    putchar((int)1 | 2 | 10 | 20 | 40);
    putchar((int)1 | 2 | 10 | 20 | 40);
    part2 = 1;
  }
  if (part2 != 0) {
    putchar((int)1 | 4 | 8 | 10 | 20 | 40);
    putchar((int)(char)2 | 8);
  }
  return;
}
```
I manually did this operation on the low bit of each and then found the corresponding ASCII character and I print flag{what_a_mess}
<!--stackedit_data:
eyJoaXN0b3J5IjpbLTEyODU2Mzk3Ml19
-->