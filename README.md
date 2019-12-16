# docker-rhofactor

A clone of bsdgames `factor` using Pollard's rho algorithm.

# Introduction

It is a clone of the `factor` command in [bsdgames](https://packages.ubuntu.com/bionic/bsdgames) using [Pollard's rho algorithm](https://en.wikipedia.org/wiki/Pollard%27s_rho_algorithm) and a demonstration of building and using docker image.

It is written in C and uses [libgmp](https://gmplib.org/) for arbitrary precision arithmetic.

# Build the docker image

To build the docker image, please type

```
$ docker build -t rhofactor:v1 .
```

# Run the docker image

To run the docker image, please type:

```
$ docker run -i rhofactor:v1
```

It should behave exactly the same as `factor` in bsdgames. Except it accepts arbitrary precision integer as input

```
$ docker run -i rhofactor:v1
12121
12121: 31 23 17 
2222
2222: 2 11 101 
219372139821732198372821921372982
219372139821732198372821921372982: 2 3 3 11 285301 30478374287 127415185044107 
210382109321821098210921832091821093280921821093210918329
210382109321821098210921832091821093280921821093210918329: 7 3 1489 348839 43832699 165766793 814732627 3258058834222311880571 
```

For a comparison:
```
$ factor
12121
12121: 17 23 31
2222
2222: 2 11 101
219372139821732198372821921372982                                 
219372139821732198372821921372982: 2 3 3 11 285301 30478374287 127415185044107
210382109321821098210921832091821093280921821093210918329
factor: '210382109321821098210921832091821093280921821093210918329' is too large
```

To terminate the program, you should send `EOF` (Ctrl+D on most terminals) to the stdin.
