#!/bin/sh

clang++ \
  -I/usr/local/include/c++/v1 -stdlib=libc++ \
  -std=c++1z \
  -l c++abi \
  -L /usr/local/lib \
  test.cxx -o test
