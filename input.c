#include "input.h"
#include <stdio.h>
Input readInputFile(const char *filename) {

  FILE *fp;
  Input inputFile;

  fp = fopen(filename, "r");

  fscanf(fp, "(%hu,%hu)\n", &inputFile.lakeSize.width,
         &inputFile.lakeSize.height);

  fscanf(fp, "(%hu,%hu)\n", &inputFile.matrixSize.rowsSize,
         &inputFile.matrixSize.colsSize);

  fscanf(fp, "%hu\n", &inputFile.virtualTime);
  fscanf(fp, "%hu\n", &inputFile.wavePropagationSpeed);
  fscanf(fp, "%f\n", &inputFile.heightThreshold);
  fscanf(fp, "%hu\n", &inputFile.interactions);
  fscanf(fp, "%f\n", &inputFile.probabilityOfDrop);
  fscanf(fp, "%hu\n", &inputFile.seed);

  fclose(fp);
  return inputFile;
}

void printInput(Input input) {
  printf("Lake Size: (%hu,%hu)\n", input.lakeSize.width, input.lakeSize.height);
  printf("Matrix Size: (%hu,%hu)\n", input.matrixSize.rowsSize,
         input.matrixSize.colsSize);
  printf("Virtual Time: %hu\n", input.virtualTime);
  printf("Wave Propagation Speed: %hu\n", input.wavePropagationSpeed);
  printf("Height Threshold: %f\n", input.heightThreshold);
  printf("Interactions: %hu\n", input.interactions);
  printf("Probability of a Drop: %f\n", input.probabilityOfDrop);
  printf("Seed: %hu\n", input.seed);
}
