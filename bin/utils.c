#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

FILE *open_file(char *path) {
  FILE *file = fopen(path, "r");

  if (!file) {
    perror("Erro ao abrir o arquivo.\n");
    exit(EXIT_FAILURE);
  }

  return file;
}

char **malloc_matrix(int *rows, int *cols) {
  char **matrix;

  matrix = (char **)malloc(*rows * sizeof(char *));

  if (matrix == NULL) {
    printf("Erro ao alocar memória.\n");
    exit(EXIT_FAILURE);
  }

  for (int i = 0; i < *rows; i++) {
    matrix[i] = (char *)malloc(*cols * sizeof(char));

    if (matrix[i] == NULL) {
      printf("Erro ao alocar memória.\n");
      exit(EXIT_FAILURE);
    }
  }

  return matrix;
}

char **fill_matrix(FILE *file, int *rows, int *cols) {
  fscanf(file, "%d %d", rows, cols);

  char **matrix = malloc_matrix(rows, cols);

  for (int i = 0; i < *rows; i++) {
    for (int j = 0; j < *cols * 2; j++) {
      if (j % 2 == 0)
        fscanf(file, "%*c");
      else
        fscanf(file, "%c", &matrix[i][j / 2]);
    }
  }

  return matrix;
}

void show_matrix(char **matrix, int *rows, int *cols) {
  printf("\n");

  for (int i = 0; i < *rows; ++i) {
    printf("%d ", i);
    for (int j = 0; j < *cols; j++) {
      printf("%c\t", matrix[i][j]);
    }
    printf("\n");
  }
}

char *create_string(int size) {
  char *word = (char *)malloc(size * sizeof(char));

  if (word == NULL) {
    perror("Erro ao alocar memória.\n");
    exit(EXIT_FAILURE);
  }

  return word;
}

void free_matrix(char **matrix, int rows) {
  for (int i = 0; i < rows; i++) {
    free(matrix[i]);
  }

  free(matrix);
}
