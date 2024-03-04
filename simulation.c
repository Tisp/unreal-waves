#include "simulation.h"
#include "ppm.h"
#include <stdio.h>

float wavePropagationHeight(double p, double t, double v) {
  float d = p - v * t;
  return d * exp(-d * d - t / 10);
}

void lakeHeightMaxMin(float lake[], Input input, float *max, float *min) {
  (*max) = -INFINITY;
  (*min) = INFINITY;

  for (size_t i = 0; i < input.lakeSize.height; ++i) {
    for (size_t j = 0; j < input.lakeSize.width; ++j) {
      float prop = lake[i * input.lakeSize.width + j];
      if (prop < (*min)) {
        (*min) = prop;
      }
      if (prop > (*max)) {
        (*max) = prop;
      }
    }
  }
}

void updateLakePoint(float lake[], Point point, DroppedPoints droppedPoints,
                     Input input) {
  float wave_high = 0;
  for (size_t t = 0; t < droppedPoints.count; ++t) {
    float dist = distance(point, droppedPoints.items[t].point);
    float propagation = wavePropagationHeight(dist, droppedPoints.items[t].time,
                                              input.wavePropagationSpeed);
    wave_high += propagation;
  }
  float p = wave_high;
  if (p < 0) {
    p = p * -1;
  }

  size_t offset = point.x * input.lakeSize.width + point.y;
  lake[offset] = p > input.heightThreshold ? wave_high : 0;
}

void createLakeImage(float lake[], Input input, size_t n_int) {

  float max, min;
  lakeHeightMaxMin(lake, input, &max, &min);
  Image image = ppmNewImage(input.lakeSize.width, input.lakeSize.height);
  float delta = fmaxf(max, -min) / 255;

  for (size_t i = 0; i < input.lakeSize.height; ++i) {
    for (size_t j = 0; j < input.lakeSize.width; ++j) {
      int offset = i * input.lakeSize.width + j;
      if (lake[offset] > 0) {
        int component = (int)ceil(lake[offset] / delta);
        Pixel pixel = {.R = 0, .G = 0, .B = component};
        ppmSetPixel(image, i, j, pixel);
      }

      if (lake[offset] < 0) {
        int component = (int)ceil(-lake[offset] / delta);
        Pixel pixel = {.R = component, .G = 0, .B = 0};
        ppmSetPixel(image, i, j, pixel);
      }
    }
  }

  char fileNamePrefix[] = "wave_";
  char fileNameExt[] = ".ppm";
  char result[100] = {0};
  snprintf(result, sizeof(result), "images/%s%zu%s", fileNamePrefix, n_int,
           fileNameExt);
  ppmSave(image, result);
  image.pixels = NULL;
  ppmFreeImage(image);
}
