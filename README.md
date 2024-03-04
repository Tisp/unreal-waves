# Unreal waves simulation


Let's simulate a fantasy rainstorm on an imaginary planet, generating unreal waves. To make the scene a little more surreal, a special material covers the entire edge of the rectangular lake, completely absorbing the waves that touch it.


The unreal wave propagates according to the function:

$h(\rho,t) = (\rho - v) .e^{(-(\rho-v.t^2))}.e^{-t/10}$

![plot](./images/unreal_waves.gif)

Inspired in [this](Ondas.pdf) IME USP Homework

## Run
### Makefile
```shell
$ ~ ./run.sh <INPUT_FILE> <NUM_CORS>
```
