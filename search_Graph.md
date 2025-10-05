This markdown file was for the search Graph programming challenge.

The goal of this challenge was to search a graph given by the binary data file to find the flag.

The first thing I needed to do was create a function that would parse and organize my graph according to the README. I decided to do this in Python.
```
| Val |  Length   |    Out    |    Out    | ... |
|  0  |  1  |  2  |  3  |  4  |  5  |  6  | ... |


Val: The ASCII value stored by the node.
Length: The number of Out links.
Out: Represents a one-directional link from this node to another. Out refers to the destination node by index within the binary file.
```

```python
def load_graph(filename):
    data = open(filename, "rb").read() #Reads binary data from file 
    graph, i = [], 0
    while i < len(data): #Iterates through file
        val = chr(data[i]) #Gets first byte
        length = struct.unpack_from("<H", data, i + 1)[0] #Gets little endian 2 byte integer
        outs = [struct.unpack_from("<H", data, i + 3 + j*2)[0] for j in range(length)] #Gets little endian 2 byte integer for both outs
        graph.append((val, outs)) #adds corresponding val to outs
        i += 3 + length * 2
    return graph
```

Next, I needed to implement a BFS search on this graph. I used an example BFS search from geeksforgeeks.

```python
def bfs(graph, target="}"): #BFS algorithm from geeks for geeks
    q, visited = deque([(0, [0])]), {0}
    while q:
        node, path = q.popleft()
        val, outs = graph[node]
        if val == target:
            return path
        for nxt in outs:
            if nxt not in visited:
                visited.add(nxt)
                q.append((nxt, path + [nxt]))
```

All that was left was to run it in a main function, then print the corresponding val in the organized path

```python
graph = load_graph("input_search.bin") #Read graph from input file
path = bfs(graph) #Returns nodes that were in BFS
flag = "".join(graph[i][0] for i in path) #Create flag by iterating through each node and getting val
print("Flag:", flag) #Print flag
```

CWE{sQyPF[X_[cK.}

### References 
-https://www.geeksforgeeks.org/dsa/breadth-first-search-or-bfs-for-a-graph/
