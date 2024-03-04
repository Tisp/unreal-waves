FROM gcc:latest
RUN apt update && apt install time valgrind -y
COPY . /app
WORKDIR /app
RUN make
ENTRYPOINT ["./waves"]
