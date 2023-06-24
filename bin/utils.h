#ifndef UTILS_H
#define UTILS_H

FILE *open_file(char *path);
void show_matrix(char **matrix, int *rows, int *cols);
void free_matrix(char **matrix, int rows);
char **malloc_matrix(int *rows, int *cols);
char **fill_matrix(FILE *file, int *rows, int *cols);
char *create_string(int size);

#endif