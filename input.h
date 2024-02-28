#ifndef INPUT_H_
#define INPUT_H_

#include <stdint.h>

typedef struct {
  uint16_t width;
  uint16_t height;
} LakeSize;

typedef struct {
  uint16_t rowsSize;
  uint16_t colsSize;
} MatrixSize;

typedef struct {
  LakeSize lakeSize;
  MatrixSize matrixSize;
  uint16_t virtualTime;
  uint16_t wavePropagationSpeed;
  float heightThreshold;
  uint16_t interactions;
  float probabilityOfDrop;
  uint16_t seed;
} Input;

Input readInputFile(const char *filename);
void printInput(Input input);

#endif // INPUT_H_
