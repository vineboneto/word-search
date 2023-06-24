#ifndef WORD_SEARCH_H
#define WORD_SEARCH_H

ROI *horizontal_forward(char *word, char **matrix, int *rows, int *cols);
ROI *horizontal_backward(char *word, char **matrix, int *rows, int *cols);
ROI *vertical_forward(char *word, char **matrix, int *rows, int *cols);
ROI *vertical_backward(char *word, char **matrix, int *rows, int *cols);
ROI *diagonal_SE(char *word, char **matrix, int *rows, int *cols);
ROI *diagonal_SW(char *word, char **matrix, int *rows, int *cols);
ROI *diagonal_NE(char *word, char **matrix, int *rows, int *cols);
ROI *diagonal_NW(char *word, char **matrix, int *rows, int *cols);
ROI *search_word(char *word, char **matrix, int *rows, int *cols);

#endif