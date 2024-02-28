#include "input.h"
#include "math.h"
#include "ppm.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define dynamic_array_append(array, element)                                   \
  do {                                                                         \
    if (array.count >= array.capacity) {                                       \
      if (array.capacity == 0)                                                 \
        array.capacity = 2;                                                    \
      else                                                                     \
        array.capacity *= 2;                                                   \
      array.items =                                                            \
          realloc(array.items, array.capacity * sizeof(*array.items));         \
    }                                                                          \
    array.items[array.count++] = element;                                      \
  } while (0)

#define dynamic_array_free(array) free((array).items)

typedef struct {
  uint16_t x;
  uint16_t y;
} Point;

typedef struct {
  Point *items;
  size_t capacity;
  size_t count;
} DroppedPoints;

float distance(Point p1, Point p2) {
  float dx = p1.x - p2.x;
  float dy = p1.y - p2.y;
  return sqrt(dx * dx + dy * dy);
}

float wave_propagation(double p, double t, double v) {
  float d = p - v * t;
  return d * exp(-d * d - t / 10);
}

void calculate_lake_propagation_wave(float lake[], Point point, Input input,
                                     float time) {
  size_t i, j = 0;
  for (i = 0; i < input.lakeSize.height; ++i) {
    for (j = 0; j < input.lakeSize.width; ++j) {
      Point p2 = {.x = i, .y = j};
      float dist = distance(p2, point);
      float threshold = input.heightThreshold;
      float propagation =
          wave_propagation(dist, time, input.wavePropagationSpeed);

      float p = propagation;
      if (propagation < 0) {
        p = p * -1;
      }

      if (p > threshold) {
        lake[i * input.lakeSize.width + j] += propagation;
      } else {
        lake[i * input.lakeSize.width + j] = 0;
      }
    }
  }
}

void maxMin(float lake[], Input input, float *max, float *min) {
  (*max) = -INFINITY;
  (*min) = INFINITY;
  size_t i, j = 0;

  for (i = 0; i < input.lakeSize.height; ++i) {
    for (j = 0; j < input.lakeSize.width; ++j) {
      float prop = lake[i * input.lakeSize.width + j];
      // printf("Offset: %zu PROP: %.6lf, MIN: %.6lf MAX: %.6lf\n",
      // (i * input.lakeSize.width + j), prop, (*min), (*max));
      if (prop < (*min)) {
        (*min) = prop;
      }
      if (prop > (*max)) {
        (*max) = prop;
      }
    }
  }
}

int main(int argc, const char **argv) {

  if (argc < 2) {
    fprintf(stderr, "Error: must add the input file.");
    return -1;
  }

  const char *inputFile = argv[1];
  Input input = readInputFile(inputFile);
  // printInput(input);

  float *lake =
      malloc(input.lakeSize.height * input.lakeSize.width * sizeof(float));
  srand(input.seed);

  DroppedPoints droppedPoints = {0};

  float timestemp = (float)input.virtualTime / (float)input.interactions;
  float time = 0;

  for (size_t n_int = 0; n_int < input.interactions; n_int++) {
    size_t i = 0;
    for (i = 0; i < droppedPoints.count; ++i) {
      calculate_lake_propagation_wave(lake, droppedPoints.items[i], input,
                                      time);
    }

    float dropProb = ((float)rand()) / RAND_MAX * 100;
    if (dropProb <= input.probabilityOfDrop) {
      Point p1 = {.x = rand() % input.lakeSize.width,
                  .y = rand() % input.lakeSize.height};
      dynamic_array_append(droppedPoints, p1);
    }

    time += timestemp;
  }

  float max, min;

  maxMin(lake, input, &max, &min);
  // fprintf(stderr, "Max: %f  Min: %f", max, min);
  // for (size_t i = 0; i < droppedPoints.count; ++i) {
  //   fprintf(stderr, "P%zu(%hu, %hu)\n", i, droppedPoints.items[i].x,
  //           droppedPoints.items[i].y);
  // }

  // printf("%lf %lf \n", max, min);
  Image image = ppmNewImage(input.lakeSize.width, input.lakeSize.height);
  float delta = fmaxf(max, -min) / 255;

  for (size_t i = 0; i < input.lakeSize.height; ++i) {
    for (size_t j = 0; j < input.lakeSize.width; ++j) {
      int offset = i * input.lakeSize.width + j;
      printf("H: %lf\n", lake[offset]);
      if (lake[offset] > 0) {
        // printf("B ->%d\n", (int)ceil(lake[offset] / delta));
        Pixel pixel = {
            .R = 255, .G = 255, .B = (int)ceil(lake[offset] / delta)};
        ppmSetPixel(image, i, j, pixel);
      }

      if (lake[offset] < 0) {
        // printf("R ->%d\n", (int)ceil(-lake[offset] / delta));
        Pixel pixel = {.R = (int)ceil(-lake[offset] / delta), .G = 0, .B = 0};
        ppmSetPixel(image, i, j, pixel);
      }
    }
  }

  ppmSave(image, "waves.ppm");
  dynamic_array_free(droppedPoints);
  ppmFreeImage(image.pixels);
  free(lake);
  return 0;
}
