This write up is for the baseoddessey reverse engineering challenge

First thing I did was to put the binary into ghidra and run file
```C
  bool bVar1;
  int iVar2;
  long in_FS_OFFSET;
  ulong input_len;
  undefined8 local_220;
  undefined1 input_buff [256];
  int local_118;
  short local_114;
  float local_112;
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  setvbuf(stdout,(char *)0x0,2,0);
  setvbuf(stderr,(char *)0x0,2,0);
  printf("Waiting for input> ");
  input_len = read(0,input_buff,255);
  if ((long)input_len < 1) {
    puts("Input error!");
  }
  while ((input_buff[input_len - 1] == '\n' || (input_buff[input_len - 1] == ' '))) {
    input_buff[input_len - 1] = 0;
    input_len = input_len - 1;
  }
  printf("You entered \"%s\" (%ld characters)\n",input_buff,input_len);
  iVar2 = decode(input_buff,input_len & 0xffffffff,&local_118);
  if (iVar2 != 0) {
    puts("Invalid B64 data length!");
                    /* WARNING: Subroutine does not return */
    exit(0);
  }
    local_220 = &local_118;
  if ((local_118 == 2001) && (local_114 == 9000)) {
    if (0.0 <= local_112 - 1.618) {
      bVar1 = 0.001 < local_112 - 1.618;
    }
    else {
      bVar1 = local_112 - 1.618 < -0.001;
    }
    if (!bVar1) {
      puts("Phew! You\'ve deactivated the computer and can keep going to Jupiter...");
      system("cat flag.txt");
      goto LAB_00101461;
    }
  }
  puts("Wrong Input! Life support has been deactivated and everyone will perish!");
```
from this main function I can see that I give the program an input, it counts the length then runs a decode function. If can figure out how the decode function works I can use that to give me the correct values for the check and get the flag.

When looking inside of the decode function I saw this

```C
undefined8 decode(char *param_1,uint param_2,undefined1 *param_3)

{
  undefined8 uVar1;
  uint local_28;
  int i;
  char *local_20;
  undefined1 *local_18;
  
  if ((param_2 & 3) == 0) {
    local_20 = param_1;
    local_18 = param_3;
    while (local_20 < param_1 + (int)param_2) {
      local_28 = 0;
      for (i = 0; i < 4; i = i + 1) {
        if (*local_20 != '=') {
          local_28 = local_28 |
                     (uint)(byte)scrambled_alphabet[(int)*local_20] <<
                     (((char)i - (char)(i << 2)) * '\x02' + 0x12U & 0x1f);
        }
        local_20 = local_20 + 1;
      }
      *local_18 = (char)(local_28 >> 0x10);
      local_18[1] = (char)(local_28 >> 8);
      local_18[2] = (char)local_28;
      local_18 = local_18 + 3;
    }
    uVar1 = 0;
  }
  else {
    uVar1 = 0xffffffff;
  }
  return uVar1;
}
```
Based on the title im going to assume this is some sort of base64 encoder. The first thing it does is check if the input length is divisible by 4 which is to check if alignment is correct. next the char* is set to out input buffer, the second pointer is set to the int, short, and float that get checked in the if statement in main.

It then reads the input 4 characters at a time
```C
      for (i = 0; i < 4; i = i + 1) {
        if (*local_20 != '=') {
```
Each charter read in is mapped to the scrambled alphabet, this gives us a 6 bit value for each character and then places that into local 28. The shift that happens allows each one to be put in the correct spot in local 28. For each iteration is decrements by 6.
```C
      *local_18 = (char)(local_28 >> 0x10);
      local_18[1] = (char)(local_28 >> 8);
      local_18[2] = (char)local_28;
      local_18 = local_18 + 3;
    }
```

This last section takes the bits in local 28 and grabs 8 and places them into the resulting location. It then continues to the next block. Basically a normal base64 decoder but with a custom alphabet.

In order to get the output we want I need to create an encoder and that uses the final value we need to pass the check.

```python
scrambled = [
 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x24,0x00,0x00,0x00,0x1b,
 0x00,0x26,0x11,0x19,0x3f,0x0f,0x3b,0x20,0x35,0x23,0x00,0x00,0x00,0x00,0x00,0x00,
 0x00,0x3d,0x30,0x38,0x0d,0x1f,0x3c,0x34,0x3e,0x14,0x27,0x0c,0x25,0x04,0x0b,0x1c,
 0x31,0x17,0x1d,0x16,0x1a,0x09,0x1e,0x32,0x03,0x12,0x07,0x00,0x00,0x00,0x00,0x00,
 0x00,0x06,0x18,0x01,0x28,0x2a,0x21,0x22,0x0e,0x10,0x08,0x0a,0x39,0x02,0x2b,0x13,
 0x2c,0x37,0x29,0x36,0x05,0x15,0x2e,0x2f,0x33,0x2d,0x3a,0x00,0x00,0x00,0x00,0x00
] + [0x00] * (256 - 192)

# reverse map value -> an ASCII byte that maps to that value
rev = {}
for b, v in enumerate(scrambled):
    if v not in rev:
        rev[v] = b

```
First I create a map from the scrambled alphabet to go the opposite way, from the 6 bit value to an ascii character
```python 
for i in range(0, len(data), 3):
```
It then loops through the input by groups of 3 and turns those input characters into a group of 24 bits.
```python 
acc = (block[0] << 16) | (block[1] << 8) | block[2]
```
Once we have that group of 24 bits it shifts to the right 6 and places and stores each of those 6 bit groupings
```python
vals = [(acc >> 18) & 0x3f, (acc >> 12) & 0x3f, (acc >> 6) & 0x3f, acc & 0x3f]

```
```python

```
From there it maps each of those 6 bit groupings to a ascii character in the alphabet or if it runs into a 0 it gives a '='. It then appends these characters to an encoded final string.

So the last thing we need to do is find the input we need to encode. All I did there was to find the values we need for each to pass the check and append them together and pad each one to 8 bytes.

local_118 == 0x07d1
local_114 == 0x2328
local_112 = 0x3fcf1aa0

I then just run my encoder to find my output, then give that as input to the program to get my flag.
```python
#!/usr/bin/env python3
scrambled = [
 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x24,0x00,0x00,0x00,0x1b,
 0x00,0x26,0x11,0x19,0x3f,0x0f,0x3b,0x20,0x35,0x23,0x00,0x00,0x00,0x00,0x00,0x00,
 0x00,0x3d,0x30,0x38,0x0d,0x1f,0x3c,0x34,0x3e,0x14,0x27,0x0c,0x25,0x04,0x0b,0x1c,
 0x31,0x17,0x1d,0x16,0x1a,0x09,0x1e,0x32,0x03,0x12,0x07,0x00,0x00,0x00,0x00,0x00,
 0x00,0x06,0x18,0x01,0x28,0x2a,0x21,0x22,0x0e,0x10,0x08,0x0a,0x39,0x02,0x2b,0x13,
 0x2c,0x37,0x29,0x36,0x05,0x15,0x2e,0x2f,0x33,0x2d,0x3a,0x00,0x00,0x00,0x00,0x00
] + [0x00] * (256 - 192)

rev = {}
for b, v in enumerate(scrambled):
    if v not in rev:
        rev[v] = b

def encode_scrambled_b64(data: bytes) -> str:
    out = []
    for i in range(0, len(data), 3):
        block = data[i:i+3]

        acc = (block[0] << 16) | (block[1] << 8) | block[2]
        vals = [(acc >> 18) & 0x3F,(acc >> 12) & 0x3F,(acc >> 6)  & 0x3F,acc & 0x3F,]

        for v in vals:
            if v == 0:
                out.append('=')
            else:
                c = rev.get(v, ord('?'))
                out.append(chr(c))
    return ''.join(out)

if __name__ == "__main__":
    payload = bytes.fromhex("d10700002823bc1bcf3f0000")
    print(encode_scrambled_b64(payload))
```

Output = GiO==m79wcw55B==

CWE{Op3n_7he_p0d_B@y_d0Or_NXXaSf5v}

 ### References
 - https://www.lifewire.com/base64-encoding-overview-1166412
