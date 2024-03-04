#ifndef PPM_H_
#define PPM_H_

#include <stdint.h>

typedef struct {
  unsigned char R;
  unsigned char G;
  unsigned char B;
} Pixel;

// TODO aumentar os valores de altura e largura para suportar dimensoes maiores
typedef struct {
  uint16_t width;
  uint16_t height;
  Pixel *pixels;
} Image;

Image ppmNewImage(uint16_t width, uint16_t height);
void ppmFreeImage(Image image);
void ppmSave(Image image, const char *fileName);
void ppmSetPixel(Image image, uint16_t x, uint16_t y, Pixel pixel);

#endif // PPM_H_
