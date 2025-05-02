#include <stdio.h>
#include <stdlib.h>

int **allocateMatrix(int rows, int cols) {
    int **matrix = (int **)malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; i++)
        matrix[i] = (int *)malloc(cols * sizeof(int));
    return matrix;
}

void freeMatrix(int **matrix, int rows) {
    for (int i = 0; i < rows; i++)
        free(matrix[i]);
    free(matrix);
}

void inputMatrix(int **matrix, int rows, int cols) {
    printf("Enter matrix (%d x %d):\n", rows, cols);
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            scanf("%d", &matrix[i][j]);
}

void printMatrix(int **matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++)
            printf("%d ", matrix[i][j]);
        printf("\n");
    }
}

int **addMatrices(int **A, int **B, int rows, int cols) {
    int **res = allocateMatrix(rows, cols);
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            res[i][j] = A[i][j] + B[i][j];
    return res;
}

int **subtractMatrices(int **A, int **B, int rows, int cols) {
    int **res = allocateMatrix(rows, cols);
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            res[i][j] = A[i][j] - B[i][j];
    return res;
}

int **multiplyMatrices(int **A, int **B, int r1, int c1, int c2) {
    int **res = allocateMatrix(r1, c2);
    for (int i = 0; i < r1; i++)
        for (int j = 0; j < c2; j++) {
            res[i][j] = 0;
            for (int k = 0; k < c1; k++)
                res[i][j] += A[i][k] * B[k][j];
        }
    return res;
}

int **transposeMatrix(int **A, int rows, int cols) {
    int **T = allocateMatrix(cols, rows);
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            T[j][i] = A[i][j];
    return T;
}

// Helper function to get minor
void getMinor(int **src, int **dest, int row, int col, int size) {
    int r = 0, c = 0;
    for (int i = 0; i < size; i++) {
        if (i == row) continue;
        c = 0;
        for (int j = 0; j < size; j++) {
            if (j == col) continue;
            dest[r][c++] = src[i][j];
        }
        r++;
    }
}

// Recursive determinant
int determinant(int **matrix, int size) {
    if (size == 1)
        return matrix[0][0];
    if (size == 2)
        return matrix[0][0]*matrix[1][1] - matrix[0][1]*matrix[1][0];

    int det = 0;
    int **minor = allocateMatrix(size - 1, size - 1);

    for (int col = 0; col < size; col++) {
        getMinor(matrix, minor, 0, col, size);
        int sign = (col % 2 == 0) ? 1 : -1;
        det += sign * matrix[0][col] * determinant(minor, size - 1);
    }

    freeMatrix(minor, size - 1);
    return det;
}

int **adjoint(int **matrix, int size) {
    int **adj = allocateMatrix(size, size);
    int **minor = allocateMatrix(size - 1, size - 1);

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            getMinor(matrix, minor, i, j, size);
            int sign = ((i + j) % 2 == 0) ? 1 : -1;
            adj[j][i] = sign * determinant(minor, size - 1);  // Note: Transposed
        }
    }

    freeMatrix(minor, size - 1);
    return adj;
}

float **inverse(int **matrix, int size) {
    int det = determinant(matrix, size);
    if (det == 0) {
        printf("Matrix is singular, inverse does not exist.\n");
        return NULL;
    }

    int **adj = adjoint(matrix, size);
    float **inv = (float **)malloc(size * sizeof(float *));
    for (int i = 0; i < size; i++) {
        inv[i] = (float *)malloc(size * sizeof(float));
        for (int j = 0; j < size; j++)
            inv[i][j] = (float)adj[i][j] / det;
    }

    freeMatrix(adj, size);
    return inv;
}

void printFloatMatrix(float **matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++)
            printf("%.2f ", matrix[i][j]);
        printf("\n");
    }
}

int main() {
    int choice, r1, c1, r2, c2;
    printf("Matrix Calculator:\n");
    printf("1. Addition\n2. Subtraction\n3. Multiplication\n4. Transpose\n5. Determinant\n6. Adjoint\n7. Inverse\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    int **A, **B, **res;
    float **fres;

    switch (choice) {
        case 1:
        case 2:
            printf("Enter rows and columns: ");
            scanf("%d%d", &r1, &c1);
            A = allocateMatrix(r1, c1);
            B = allocateMatrix(r1, c1);
            printf("Matrix A:\n");
            inputMatrix(A, r1, c1);
            printf("Matrix B:\n");
            inputMatrix(B, r1, c1);
            res = (choice == 1) ? addMatrices(A, B, r1, c1) : subtractMatrices(A, B, r1, c1);
            printf("Result:\n");
            printMatrix(res, r1, c1);
            freeMatrix(A, r1); freeMatrix(B, r1); freeMatrix(res, r1);
            break;

        case 3:
            printf("Enter rows and columns of Matrix A: ");
            scanf("%d%d", &r1, &c1);
            printf("Enter rows and columns of Matrix B: ");
            scanf("%d%d", &r2, &c2);
            if (c1 != r2) {
                printf("Multiplication not possible.\n");
                break;
            }
            A = allocateMatrix(r1, c1);
            B = allocateMatrix(r2, c2);
            printf("Matrix A:\n");
            inputMatrix(A, r1, c1);
            printf("Matrix B:\n");
            inputMatrix(B, r2, c2);
            res = multiplyMatrices(A, B, r1, c1, c2);
            printf("Result:\n");
            printMatrix(res, r1, c2);
            freeMatrix(A, r1); freeMatrix(B, r2); freeMatrix(res, r1);
            break;

        case 4:
            printf("Enter rows and columns: ");
            scanf("%d%d", &r1, &c1);
            A = allocateMatrix(r1, c1);
            printf("Matrix:\n");
            inputMatrix(A, r1, c1);
            res = transposeMatrix(A, r1, c1);
            printf("Transpose:\n");
            printMatrix(res, c1, r1);
            freeMatrix(A, r1); freeMatrix(res, c1);
            break;

        case 5:
            printf("Enter size (n x n): ");
            scanf("%d", &r1);
            A = allocateMatrix(r1, r1);
            printf("Matrix:\n");
            inputMatrix(A, r1, r1);
            printf("Determinant: %d\n", determinant(A, r1));
            freeMatrix(A, r1);
            break;

        case 6:
            printf("Enter size (n x n): ");
            scanf("%d", &r1);
            A = allocateMatrix(r1, r1);
            printf("Matrix:\n");
            inputMatrix(A, r1, r1);
            res = adjoint(A, r1);
            printf("Adjoint:\n");
            printMatrix(res, r1, r1);
            freeMatrix(A, r1); freeMatrix(res, r1);
            break;

        case 7:
            printf("Enter size (n x n): ");
            scanf("%d", &r1);
            A = allocateMatrix(r1, r1);
            printf("Matrix:\n");
            inputMatrix(A, r1, r1);
            fres = inverse(A, r1);
            if (fres) {
                printf("Inverse:\n");
                printFloatMatrix(fres, r1, r1);
                for (int i = 0; i < r1; i++)
                    free(fres[i]);
                free(fres);
            }
            freeMatrix(A, r1);
            break;

        default:
            printf("Invalid choice.\n");
    }

    return 0;
}
