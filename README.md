# Copyright Carauleanu Valentin Gabriel 311CA

Working with a large number of functions, I decided to create 4 static libraries: 
- `dynamic_alloc.h`, composed of dynamic allocation, reallocation, and memory release functions
- `numeric_functions.h`, composed of functions that target matrix operations and "swap" functions
- `commands.h`, composed of functions that target the main operations of the `my_octave` program and use functions from the other 2 libraries
- `strassen.h`, composed of all the necessary functions for Strassen's matrix multiplication algorithm

Considering the necessity to store both an undefined number of matrices, as well as their sizes, 3 dynamically allocated "resizable" vectors will be used (2 of the type *v for the number of lines and columns and one of the type ***v for matrices). Moreover, the program's operations will be performed in a `while(1)` loop, which will only be exited if the 'Q' character is read.

To carry out all operations, a `switch` instruction will be used to test the values of the command variable where the characters entered from the keyboard are stored.

The vectors of matrices and of columns/lines are initialized with a dimension of 1, with their length incremented upon the addition of each new matrix except for the initial one. This way, the length of the vectors remains minimal throughout the program.

In the case of the multiplication operation, if the two matrices can be multiplied, the lengths of the matrix and dimension vectors will be incremented, and the resulting matrix (following a classic O(n^3) multiplication algorithm) will be added to the end of the series.

For the power-raising operation, an iterative algorithm is used, the unit matrix In. If the power is even, the matrix is multiplied by itself, and the power is halved. If the power is odd, the matrix In is multiplied by the power-raised matrix, and the power is decremented.

During the deletion operation, the 'i' matrix is freed from memory, and the swap operation is applied to all elements of the matrix and dimension vectors from position i to the maximum position. Thus, the deleted matrix ends up at the end of the matrix vector. Later, the lengths of the dimension and matrix vectors are decremented to use a minimum of memory.

If the 'Q' character is read from the keyboard, the 'end' variable becomes 1, leading to the exit from the `while(1)` loop and the complete release of the used memory.

Lastly, for each function that uses dynamic allocation, we will test if the allocation/reallocation was successful. In case of a potential failure, we will free all used memory and close the program.
