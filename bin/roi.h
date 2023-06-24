#ifndef ROI_H
#define ROI_H

typedef struct {
  int x, y;
} CORD;

typedef struct {
  CORD A, B;
} ROI;

ROI *create_roi();
void show_roi(ROI *roi);
int has_value(ROI *roi);

#endif