This writeup is for the linked list sort 

First I had to parse the binary data into the given format, I did this using the stuct module in python.
```
Each linked list node takes the following form:


| Flink | Value |Length | Flag Piece... |
| 0 | 1 | 2 | 3 | 4 | 5 | 6 | ......... |
```

- Flink: The pointer to the next node in the list. The flink is given as an offset from the beginning of the binary file.
- Value: The value which should be used to sort the linked list.
- Length: Size, in bytes, of the Flag Piece
- Flag Piece: You will use these bytes to generate the flag once the list is sorted. Note: Flag Pieces are of variable length (see the length parameter to know the number of bytes).
```
After parsing the data all I had to do was sort the list, I did this isung the .sort method in python and sorted by the value. I then XORed the even nodes and then decoded/printed the flag is ascii/

```python
#!/usr/bin/env python3
import struct

INPUT_FILE = "input_list.bin"
SENTINEL = 0xFFFF  # end-of-list marker

def parse_list(data):
    nodes = []
    cur = 0 #Current byte
    while True:
        flink = struct.unpack_from("<H", data, cur)[0]
        value = struct.unpack_from("<H", data, cur + 2)[0]
        length = struct.unpack_from("<H", data, cur + 4)[0]
        start = cur + 6
        nodes.append((value, data[start:start+length]))
        if flink == SENTINEL:
            break
        cur = flink
    return nodes

def sort_key(item): #Gets key to use in sort
    return item[0]  

def xor(flags_sorted):
    evens = [flag for i, (_, flag) in enumerate(flags_sorted) if i % 2 == 0] #Find even nodes
    if not evens:
        return b""
    m = max(len(f) for f in evens)
    out = bytearray(m)
    for f in evens:
        for i, b in enumerate(f):
            out[i] ^= b #XOR bytes
    return bytes(out)

def main():
    with open(INPUT_FILE, "rb") as f:
        data = f.read()
    nodes = parse_list(data)
    nodes.sort(key=sort_key)
    flag = xor(nodes)
    print(flag.decode("ascii")) #Print as ASCII

if __name__ == "__main__":
    main()
```
