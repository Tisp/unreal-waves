#include "da.h"
#include "input.h"
#include "simulation.h"
#include "utils.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char **argv) {

  if (argc < 2) {
    fprintf(stderr, "Error: must add the input file.");
    return -1;
  }

  const char *inputFile = argv[1];
  Input input = readInputFile(inputFile);

  float *lake =
      malloc(input.lakeSize.height * input.lakeSize.width * sizeof(float));

  srand(input.seed);

  DroppedPoints droppedPoints = {0};

  float timestemp = (float)input.virtualTime / (float)input.interactions;
  float time = 0;

  for (size_t n_int = 0; n_int < input.interactions; n_int++) {

    size_t i, j = 0;
    for (i = 0; i < input.lakeSize.height; ++i) {
      for (j = 0; j < input.lakeSize.width; ++j) {
        Point point = {.x = i, .y = j};
        updateLakePoint(lake, point, droppedPoints, time, input);
      }
    }

    float dropProb = ((float)rand()) / RAND_MAX * 100;
    if (dropProb <= input.probabilityOfDrop) {
      Point p1 = {.x = rand() % input.lakeSize.width,
                  .y = rand() % input.lakeSize.height};
      dynamic_array_append(droppedPoints, p1);
    }

    if (droppedPoints.count > 1) {
      createLakeImage(lake, input, n_int);
    }
    time += timestemp;
  }

  dynamic_array_free(droppedPoints);
  free(lake);
  return 0;
}
