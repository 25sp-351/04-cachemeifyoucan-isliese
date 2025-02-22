# CACHEMEIFYOUCAN Program Document
### Input: 
The program reads a list of piece prices from input.txt, where each line contains three integers:

* Length: The length of the rod piece.
* Value: The value of that rod piece.
* Max number of rod to be cut: The maximum number of pieces that can be cut for a given length. A value of 0 means there is no limit on the number of pieces.

### Rod Length: 
The program will accept a rod length from the user as a command-line argument (e.g., ./rod_cutting 45).

### Expexted Output:
 For each rod length provided:

* The program calculates and prints the cutting plan in the format:
```<n> @ <size> = <total value>```

* After the cutting list, it prints the remainder of the rod:
```Remainder: <length>```

* Finally, it prints the total value of all cuts:
```Value: <total value>```

<br>
<br>
<br>

# Instuction for Running
1. Navigate to the directory containing the C source file in Bash (CMD) using `cd`.

2. Compile the C file using `make` and if your computer's Operating System is Windows, use `mingw32-make`.

3. Enter input.txt as a first parameter for the program. 

    If you want to cut the rods using LRU Caching Policy, run the compiled .exe file using `rod_cut_lru input.txt`.

    If you want to cut the rods using FIFO Caching Policy, run the compiled .exe file using `rod_cut_fifo input.txt`.

4. Enter the length of rod that you want to cut and run the program.
<br>e.g. `45`
<br>
<br>
<br>

<br>

# Example Usage

### Input (input.txt):
```
1, 2, 5
2, 5, 3
3, 8, 2
4, 10, 0
5, 12, 1
``` 

### Command Line(cmd): 
```
rod_cut_lru input.txt 
45
```

### Expexted Output:
```
45 @ 1 = 90
Remainder: 0
Value: 90
```
