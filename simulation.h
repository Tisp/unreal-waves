#ifndef SIMULATION_H_
#define SIMULATION_H_
#include "input.h"
#include "ppm.h"
#include "utils.h"
#include <math.h>
#include <stdlib.h>

typedef struct {
  Point point;
  float time;
} DropPoint;

typedef struct {
  DropPoint *items;
  size_t capacity;
  size_t count;
} DroppedPoints;

float wavePropagationHeight(double p, double t, double v);
void lakeHeightMaxMin(float lake[], Input input, float *max, float *min);
void updateLakePoint(float lake[], Point point, DroppedPoints droppedPoints,
                     Input input);
void createLakeImage(float lake[], Input input, size_t n_int);
#endif // SIMULATION_H_
