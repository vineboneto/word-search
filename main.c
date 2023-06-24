#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bin/roi.h"
#include "bin/utils.h"
#include "bin/word_search.h"

#define FILE_PATH "files/grade.txt"

void *menu(int *flag);
char *get_word();
char **parser_file(int *rows, int *cols);

int main() {
  int flag = 0;
  int rows, cols;

  char **matrix = parser_file(&rows, &cols);

  while (flag != 1) {
    menu(&flag);

    if (flag == 1) {
      continue;
    } else if (flag == 2) {
      char *word = get_word();

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
      continue;
    }

    printf("Opcao invalida.\n");
  }

  free_matrix(matrix, rows);

  return 0;
}

void *menu(int *flag) {
  printf("\nSair - 1\n");
  printf("Buscar - 2\n");
  printf("Escolha a opcao para buscar a palavra: ");
  scanf("%d", flag);
  getchar(); // Limpar o buffer
}

char *get_word() {
  char *word = create_string(100);
  printf("Digite a palavra que deseja buscar: ");
  fgets(word, 100, stdin);
  word[strcspn(word, "\n")] = 0; // remover quebra de linha
  return word;
}

char **parser_file(int *rows, int *cols) {
  FILE *file = open_file(FILE_PATH);
  char **matrix = fill_matrix(file, rows, cols);
  show_matrix(matrix, rows, cols);
  fclose(file);
  return matrix;
}
