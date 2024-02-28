FROM gcc:latest

COPY . /app
WORKDIR /app
run make
ENTRYPOINT ["./waves", "input2"]
