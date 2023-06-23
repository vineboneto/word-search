#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FILE_PATH "files/grade.txt"
#define true 1
#define false 0

typedef struct {
  int x, y;
} CORD;

typedef struct {
  CORD A, B;
} ROI;

FILE *open_file(char *path);
char **malloc_matrix(int *rows, int *cols);
char **fill_matrix(FILE *file, int *rows, int *cols);
char *create_string(int size);
ROI *create_roi();
ROI *horizontal_forward(char *word, char **matrix, int *rows, int *cols);
ROI *horizontal_backward(char *word, char **matrix, int *rows, int *cols);
ROI *vertical_forward(char *word, char **matrix, int *rows, int *cols);
ROI *vertical_backward(char *word, char **matrix, int *rows, int *cols);
ROI *diagonal_SE(char *word, char **matrix, int *rows, int *cols);
ROI *diagonal_SW(char *word, char **matrix, int *rows, int *cols);
ROI *diagonal_NE(char *word, char **matrix, int *rows, int *cols);
ROI *diagonal_NW(char *word, char **matrix, int *rows, int *cols);
ROI *search_word(char *word, char **matrix, int *rows, int *cols);
void show_matrix(char **matrix, int *rows, int *cols);
void show_roi(ROI *roi);
int has_value(ROI *roi);

int main() {
  int flag = 0;
  int rows, cols;
  FILE *file = open_file(FILE_PATH);

  char **matrix = fill_matrix(file, &rows, &cols);
  show_matrix(matrix, &rows, &cols);
  fclose(file);

  while (flag != 1) {
    printf("\nSair - 1\n");
    printf("Buscar - 2\n");
    printf("Escolha a opcao para buscar a palavra: ");
    scanf("%d", &flag);
    getchar(); // Limpar o buffer

    if (flag == 1) {
      continue;
    } else if (flag == 2) {
      char *word = create_string(100);
      printf("Digite a palavra que deseja buscar: ");
      fgets(word, 100, stdin);
      word[strcspn(word, "\n")] =
          0; // remover quebra de linha para não ficar um caracter a mais

      printf("\nBuscando a palavra: %s\n", word);

      ROI *roi = search_word(word, matrix, &rows, &cols);

      if (has_value(roi)) {
        printf("Palavra encontrada.\n");
        show_roi(roi);
      } else {
        printf("Palavra nao encontrada.\n");
      }
      free(word);
      free(roi);
    } else {
      printf("Opcao invalida.\n");
    }
  }

  for (int i = 0; i < rows; i++) {
    free(matrix[i]);
  }

  free(matrix);

  return 0;
}

ROI *search_word(char *word, char **matrix, int *rows, int *cols) {
  // Ponteiros para funções
  ROI *(*search_funcs[])(char *, char **, int *, int *) = {
      horizontal_forward, horizontal_backward, vertical_forward,
      vertical_backward,  diagonal_SE,         diagonal_SW,
      diagonal_NE,        diagonal_NW};

  ROI *roi;
  int num_funcs = sizeof(search_funcs) / sizeof(search_funcs[0]);

  for (int i = 0; i < num_funcs; i++) {
    roi = search_funcs[i](word, matrix, rows, cols);

    if (has_value(roi))
      return roi;
  }

  return create_roi();
}

int has_value(ROI *roi) {
  if (roi->A.x != -1 && roi->A.y != -1 && roi->B.x != -1 && roi->B.y != -1)
    return true;
  return false;
}

// (↙️) - SW (Sudoeste)
ROI *diagonal_SW(char *word, char **matrix, int *rows, int *cols) {
  int length_word = strlen(word);
  ROI *roi = create_roi();

  for (int i = 0; i < *rows; i++) {
    for (int j = 0; j < *cols; j++) {

      if (word[0] == matrix[i][j]) {

        int count_equals = 0;
        int k = 0;

        for (k = 0; k < length_word; k++) {
          if (i + k < *rows && j - k >= 0 && word[k] == matrix[i + k][j - k]) {
            if (++count_equals == length_word)
              break;
          }
        }

        if (count_equals == length_word) {
          roi->A.x = i;
          roi->A.y = j;
          roi->B.x = i + k;
          roi->B.y = j - k;
          return roi;
        }
      }
    }
  }

  return roi;
}

//  (↗️) - NE (Nordeste)
ROI *diagonal_NE(char *word, char **matrix, int *rows, int *cols) {
  int length_word = strlen(word);
  ROI *roi = create_roi();

  for (int i = 0; i < *rows; i++) {
    for (int j = 0; j < *cols; j++) {

      if (word[0] == matrix[i][j]) {

        int count_equals = 0;
        int k = 0;

        for (k = 0; k < length_word; k++) {
          if (i - k >= 0 && j + k < *cols && word[k] == matrix[i - k][j + k]) {
            if (++count_equals == length_word)
              break;
          }
        }

        if (count_equals == length_word) {
          roi->A.x = i;
          roi->A.y = j;
          roi->B.x = i - k;
          roi->B.y = j + k;
          return roi;
        }
      }
    }
  }
  return roi;
}

//  (↖️) - NW (Noroeste)
ROI *diagonal_NW(char *word, char **matrix, int *rows, int *cols) {

  int length_word = strlen(word);
  ROI *roi = create_roi();

  for (int i = *rows - 1; i > -1; i--) {
    for (int j = *cols - 1; j > -1; j--) {

      if (word[0] == matrix[i][j]) {

        int count_equals = 0;
        int k = 0;

        for (k = 0; k < length_word; k++) {
          if (i - k >= 0 && j - k >= 0 && word[k] == matrix[i - k][j - k]) {
            if (++count_equals == length_word)
              break;
          }
        }

        if (count_equals == length_word) {
          roi->A.x = i;
          roi->A.y = j;
          roi->B.x = i - k;
          roi->B.y = j - k;
          return roi;
        }
      }
    }
  }
  return roi;
}

// (↘️) - SE (Sudeste)
ROI *diagonal_SE(char *word, char **matrix, int *rows, int *cols) {
  int length_word = strlen(word);
  ROI *roi = create_roi();

  for (int i = 0; i < *rows; i++) {
    for (int j = 0; j < *cols; j++) {

      if (word[0] == matrix[i][j]) {

        int count_equals = 0;
        int k = 0;

        for (k = 0; k < length_word; k++) {
          if (i + k < *rows && j + k < *cols &&
              word[k] == matrix[i + k][j + k]) {
            if (++count_equals == length_word)
              break;
          }
        }

        if (count_equals == length_word) {
          roi->A.x = i;
          roi->A.y = j;
          roi->B.x = i + k;
          roi->B.y = j + k;
          return roi;
        }
      }
    }
  }

  return roi;
}

ROI *vertical_backward(char *word, char **matrix, int *rows, int *cols) {
  ROI *roi = create_roi();
  int length_word = strlen(word);

  for (int i = *rows - 1; i > -1; i--) {
    for (int j = *cols - 1; j > -1; j--) {

      if (word[0] == matrix[i][j]) {

        int count_equals = 0;
        int k = 0;

        for (k = 0; k < length_word; k++) {
          if (i - k >= 0 && word[k] == matrix[i - k][j]) {
            if (++count_equals == length_word)
              break;
          }
        }

        if (count_equals == length_word) {
          roi->A.x = i;
          roi->A.y = j;
          roi->B.x = i - k;
          roi->B.y = j;
          return roi;
        }
      }
    }
  }

  return roi;
}

ROI *vertical_forward(char *word, char **matrix, int *rows, int *cols) {

  ROI *roi = create_roi();
  int length_word = strlen(word);

  for (int i = 0; i < *rows; i++) {
    for (int j = 0; j < *cols; j++) {

      if (word[0] == matrix[i][j]) {

        int count_equals = 0;
        int k = 0;

        for (k = 0; k < length_word; k++) {
          if (i + k < *rows && word[k] == matrix[i + k][j]) {
            if (++count_equals == length_word)
              break;
          }
        }

        if (count_equals == length_word) {
          roi->A.x = i;
          roi->A.y = j;
          roi->B.x = i + k;
          roi->B.y = j;
          return roi;
        }
      }
    }
  }

  return roi;
}

ROI *horizontal_backward(char *word, char **matrix, int *rows, int *cols) {
  ROI *roi = create_roi();
  int length_word = strlen(word);

  for (int i = *rows - 1; i > -1; i--) {
    for (int j = *cols - 1; j > -1; j--) {

      if (word[0] == matrix[i][j]) {

        int count_equals = 0;
        int k = 0;

        for (k = 0; k < length_word; k++) {
          if (j - k >= 0 && word[k] == matrix[i][j - k]) {
            if (++count_equals == length_word)
              break;
          }
        }

        if (count_equals == length_word) {
          roi->A.x = i;
          roi->A.y = j;
          roi->B.x = i;
          roi->B.y = j - k;
          return roi;
        }
      }
    }
  }

  return roi;
}

ROI *horizontal_forward(char *word, char **matrix, int *rows, int *cols) {

  ROI *roi = create_roi();
  int length_word = strlen(word);

  for (int i = 0; i < *rows; i++) {
    for (int j = 0; j < *cols; j++) {

      if (word[0] == matrix[i][j]) {

        int count_equals = 0;
        int k = 0;

        for (k = 0; k < length_word; k++) {
          if (j + k < *cols && word[k] == matrix[i][j + k]) {
            if (++count_equals == length_word)
              break;
          }
        }

        if (count_equals == length_word) {
          roi->A.x = i;
          roi->A.y = j;
          roi->B.x = i;
          roi->B.y = j + k;
          return roi;
        }
      }
    }
  }

  return roi;
}

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

ROI *create_roi() {
  ROI *roi = malloc(sizeof(ROI));

  if (roi == NULL) {
    perror("Erro ao alocar memória.\n");
    exit(EXIT_FAILURE);
  }

  roi->A.x = -1;
  roi->A.y = -1;
  roi->B.x = -1;
  roi->B.y = -1;

  return roi;
}

void show_roi(ROI *roi) {
  printf("x: %d, y: %d\n", roi->A.x, roi->A.y);
  printf("x: %d, y: %d\n", roi->B.x, roi->B.y);
}
