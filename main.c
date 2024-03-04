#include "da.h"
#include "input.h"
#include "simulation.h"
#include "utils.h"

#include <complex.h>
#include <stdio.h>
#include <stdlib.h>

float totalLakeHeithgs(float lake[], Input input) {
  float sum = 0;
  for (size_t i = 0; i < input.lakeSize.height; ++i) {
    for (size_t j = 0; j < input.lakeSize.width; ++j) {
      int offset = i * input.lakeSize.width + j;
      sum += lake[offset];
    }
  }
  return sum;
}

int main(int argc, const char **argv) {

  if (argc < 3) {
    fprintf(stderr, "Error: must add the input file.");
    return -1;
  }

  size_t maxThreads = atoi(argv[2]);
  const char *inputFile = argv[1];
  Input input = readInputFile(inputFile);

  float *lake =
      malloc(input.lakeSize.height * input.lakeSize.width * sizeof(float));

  srand(input.seed);

  DroppedPoints droppedPoints = {0};

  float timestemp = (float)input.virtualTime / (float)input.interactions;
  size_t i, j;
  for (size_t n_int = 0; n_int < input.interactions; n_int++) {
#pragma omp parallel for schedule(static) private(i, j) shared(lake, input)    \
    num_threads(maxThreads)
    for (i = 0; i < input.lakeSize.height; ++i) {
      for (j = 0; j < input.lakeSize.width; ++j) {
        Point point = {.x = i, .y = j};
        updateLakePoint(lake, point, droppedPoints, input);
      }
    }

    float dropProb = ((float)rand()) / RAND_MAX * 100;
    if (dropProb <= input.probabilityOfDrop) {
      Point point = {
          .x = rand() % input.lakeSize.width,
          .y = rand() % input.lakeSize.height,
      };

      DropPoint dropPoint = {.point = point, .time = 0};

      dynamic_array_append(droppedPoints, dropPoint);
    }

    if (droppedPoints.count >= 1 && totalLakeHeithgs(lake, input) > 0) {
      createLakeImage(lake, input, n_int);
    }

    // Update drop time
    for (size_t t = 0; t < droppedPoints.count; ++t) {
      droppedPoints.items[t].time += timestemp;
    }
  }

  printInput(input);
  printf("\nTotal drops: %zu \n", droppedPoints.count);

  dynamic_array_free(droppedPoints);
  free(lake);

  return 0;
}
