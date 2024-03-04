#ifndef UTIL_H_
#define UTIL_H_

#include <stdint.h>
#include <stdlib.h>
typedef struct {
  uint16_t x;
  uint16_t y;
  float droppedTime;
} Point;

float distance(Point p1, Point p2);

#endif // UTIL_H_
