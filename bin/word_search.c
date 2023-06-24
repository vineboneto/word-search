#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "roi.h"
#include "word_search.h"

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
