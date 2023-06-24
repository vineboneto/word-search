#include <stdio.h>
#include <stdlib.h>

#include "roi.h"

#define true 1
#define false 0

void show_roi(ROI *roi) {
  printf("x: %d, y: %d\n", roi->A.x, roi->A.y);
  printf("x: %d, y: %d\n", roi->B.x, roi->B.y);
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

int has_value(ROI *roi) {
  if (roi->A.x != -1 && roi->A.y != -1 && roi->B.x != -1 && roi->B.y != -1)
    return true;
  return false;
}
