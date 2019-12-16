FROM ubuntu:18.04
RUN apt-get update && apt-get -y install build-essential libgmp3-dev
RUN mkdir -p /usr/src/app
COPY . /usr/src/app
WORKDIR /usr/src/app
RUN gcc -O3 -o rhofactor rhofactor.c -lgmp
CMD ./rhofactor

