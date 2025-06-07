# Matrix Calculator in C

A comprehensive matrix operations calculator implemented in C, supporting various linear algebra operations.

## Features

- ➕ Matrix Addition
- ➖ Matrix Subtraction
- ✖️ Matrix Multiplication
- 🔄 Matrix Transpose
- 🧮 Determinant Calculation
- ⚙️ Adjoint Matrix
- 🔄 Matrix Inversion
- 🧩 Dynamic memory allocation
- 🚫 Error handling for invalid operations

## Installation & Usage

### Compilation

   gcc matrix_calculator.c -o matrix_calculator -Wall -Wextra 

### Execution

./matrix_calculator

## Program Flow

1. Select operation from menu
2. Input matrix dimensions
3. Enter matrix elements
4. View results

## Supported Operations

### Operation	  -->  Requirements 
Addition	      -->  Same dimensions 

Subtraction	    -->  Same dimensions 

Multiplication	-->  cols(A) = rows(B) 

Transpose	      -->  Any matrix 

Determinant	    -->  Square matrix only 

Adjoint	        -->  Square matrix only 

Inverse	        -->  Square, non-singular matrix 


## Example Usage

Matrix Calculator:
1. Addition
2. Subtraction
3. Multiplication
4. Transpose
5. Determinant
6. Adjoint
7. Inverse

Enter your choice: 3

Enter rows and columns of Matrix A: 2 2

Enter rows and columns of Matrix B: 2 2

Matrix A:

Enter matrix (2 x 2):

1 2

3 4

Matrix B:

Enter matrix (2 x 2):

5 6

7 8

Result:

19 22

43 50

## Implementation Details

1. Dynamic memory allocation for matrices
2. Recursive determinant calculation
3. Proper memory deallocation
4. Floating-point precision for inverse operations
5. Clean console interface

## Limitations

1. No file I/O for matrices.
2. Limited to integer inputs (except inverse).
3. No complex number support.
4. No eigenvalue calculations.

## Contributing

Contributions are welcome! Please:
1. Fork the repository
2. Create your feature branch
3. Commit your changes
4. Push to the branch
5. Open a pull request

## License
MIT
