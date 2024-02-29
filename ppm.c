#include "ppm.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

Image ppmNewImage(uint16_t width, uint16_t height) {
  Pixel *pixels = malloc(width * height * sizeof(Pixel));
  Image image = {.width = width, .height = height, .pixels = pixels};
  return image;
}

void ppmFreeImage(Pixel *image) { free(image); }

void ppmSetPixel(Image image, uint16_t x, uint16_t y, Pixel pixel) {
  image.pixels[x * image.width + y] = pixel;
}

void ppmSave(Image image, const char *fileName) {
  FILE *file = fopen(fileName, "wb");
  if (file == NULL) {
    fprintf(stderr, "Fail to open the file");
  }

  const char *comment = "# No comment";
  fprintf(file, "P6\n%s\n%hu %hu\n%d\n", comment, image.width, image.height,
          255);
  typedef unsigned char pixel_t[3];

  pixel_t realPixels[image.height * image.width];

  for (size_t i = 0; i < image.height; ++i) {
    for (size_t j = 0; j < image.width; ++j) {
      int offset = i * image.width + j;
      realPixels[offset][0] = image.pixels[offset].R;
      realPixels[offset][1] = image.pixels[offset].G;
      realPixels[offset][2] = image.pixels[offset].B;
    }
  }

  fwrite(realPixels, sizeof(pixel_t), image.height * image.width, file);
  fclose(file);
  // free(realPixels);
}
