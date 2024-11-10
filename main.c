#include <math.h>
#include <stdio.h>
#include <stdlib.h>

long long **allocateMatrix(int rows, int cols) {
  long long **allocatedMatrix = malloc(rows * sizeof(long long *));
  for (int i = 0; i < cols; i++) {
    allocatedMatrix[i] = malloc(cols * sizeof(long long));
  }
  return allocatedMatrix;
}

void printaMatrix(long long **MatrixToPrint, int rows, int columns) {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      printf(" %d", MatrixToPrint[i][j]);
    }
    printf("\n");
  }
}

void fillMatrixWithZeros(long long **MatrixToFill, int rows, int columns) {
  for (int i = 0; i < rows - 1; i++) {
    for (int j = 0; j < rows - 1; j++) {
      MatrixToFill[i][j] = 0;
    }
  }
}

long long **MatrixMultiply(long long **MatrixA, long long **MatrixB, int rowsA,
                           int colsA, int rowsB, int colsB) {
  printf("Matrix A: \n");
  printaMatrix(MatrixA, 2, 2);
  printf("Matrix B: \n");
  printaMatrix(MatrixB, 2, 2);
  if (rowsA != colsB) {
    printf("Error, the number of rows in the matrix A must be equal the "
           "number of columns in the matrixB");
  }
  long long **productMatrix = allocateMatrix(rowsA, colsB);
  fillMatrixWithZeros(productMatrix, 2, 2);
  for (int i = 0; i < rowsA; i++) {
    for (int j = 0; j < colsB; j++) {
      productMatrix[i][j] = 0;
      for (int k = 0; k < colsA; k++) {
        printf("MatrixA[%d][%d] = %d \n", i, k, MatrixA[i][k]);
        printf("MatrixB[%d][%d] = %d \n", i, k, MatrixB[i][k]);
        productMatrix[i][j] += MatrixA[i][k] * MatrixB[k][j];
        printf("productMatrix[%d][%d] = %d \n", i, j, productMatrix[i][j]);
      }
    }
  }
  printf("Product Matrix: \n");
  printaMatrix(productMatrix, 2, 2);
  return productMatrix;
}

long long **MatrixToPower(long long **Matrix, long n) {
  long long **ResultingMatrix = allocateMatrix(2, 2);
  fillMatrixWithZeros(ResultingMatrix, 2, 2);
  if (n == 0) {
    **ResultingMatrix = 1;
  } else if (n == 1) {
    return Matrix;
  } else {
    if (n % 2 == 0) {
      long long **temp = MatrixToPower(Matrix, n / 2);
      ResultingMatrix = MatrixMultiply(temp, temp, 2, 2, 2, 2);
    } else if (n % 2 == 1) {
      long long **temp = MatrixToPower(Matrix, floor(n / 2));
      temp = MatrixMultiply(temp, temp, 2, 2, 2, 2);
      ResultingMatrix = MatrixMultiply(Matrix, temp, 2, 2, 2, 2);
    }
  }
  printf("Result matrix: \n");
  printaMatrix(ResultingMatrix, 2, 2);
  return ResultingMatrix;
}

long long FastFibbonaci(long n) {
  if (n < 2) {
    return n;
  } else {
    long long **IdenityMatrix = allocateMatrix(2, 2);
    IdenityMatrix[0][0] = 1;
    IdenityMatrix[0][1] = 1;
    IdenityMatrix[1][0] = 1;
    IdenityMatrix[1][1] = 0;
    long long Result = MatrixToPower(IdenityMatrix, n)[0][1];
    return Result;
  }
}

int main() {
  long number = 0;
  printf("Enter the number: ");
  scanf_s("%d", &number);
  printf("%lld", FastFibbonaci(number));
  return 0;
}