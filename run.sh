#!/bin/bash

set -xe

# rm ./images/*.ppm
docker build -t gcc:waves . && docker run -v ./images:/app/images --rm  -it gcc:waves $1 $2
