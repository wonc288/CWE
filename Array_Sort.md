This write up is for the array sort programming challenge

 In this challenge the goal is to sort an array with a given value in the first 2 bytes then a flag portion that will be XORed to get the flag. 

 First, we have to parse the file, I will be doing this using the struct module in python, I then append it to a list of the val and flag pieces
```python
def parse(data):
    elements = []
    record_size = 34  # 2 bytes (val) + 32 bytes (flag_piece)
    for i in range(0, len(data), record_size):
        val, flag_piece = struct.unpack_from("<h32s", data, i)
        elements.append((val, flag_piece))
    return elements    
```
I then need to then just run the .bin file to the parse function and then sort and print the XORed flag pieces of even indices

```python
    with open(INPUT_FILE, "rb") as f:
        data = f.read()

    array = parse(data)
    array.sort()  # sort by val

    flag = bytearray(32)
    for i, (_, flag_piece) in enumerate(array):
        if i % 2 == 0:  # even index
            for j in range(32):
                flag[j] ^= flag_piece[j]
```
After that I can just run and print the flag
 ```python
import struct

INPUT_FILE = "input_array.bin"

def parse(data):
    elements = []
    record_size = 34  # 2 bytes (val) + 32 bytes (flag_piece)
    for i in range(0, len(data), record_size):
        val, flag_piece = struct.unpack_from("<h32s", data, i)
        elements.append((val, flag_piece))
    return elements    

def main():
    with open(INPUT_FILE, "rb") as f:
        data = f.read()

    array = parse(data)
    array.sort()  # sort by val

    flag = bytearray(32)
    for i, (_, flag_piece) in enumerate(array):
        if i % 2 == 0:  # even index
            for j in range(32):
                flag[j] ^= flag_piece[j]

    print(flag.decode("ascii", errors="replace"))

if __name__ == "__main__":
    main()

```

After running the program I get the flag

CWE{pFivB93uGUUuEViQBhaPHWEu79b}

### References
-https://docs.python.org/2/library/struct.html
-https://www.geeksforgeeks.org/python/struct-module-python/
