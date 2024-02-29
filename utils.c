#include "utils.h"
#include <math.h>

float distance(Point p1, Point p2) {
  float dx = p1.x - p2.x;
  float dy = p1.y - p2.y;
  return sqrt(dx * dx + dy * dy);
}
