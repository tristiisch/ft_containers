#!/bin/bash
c++ main.cpp && time ./a.out 1047552 && c++ main.cpp -D IS_STL && time ./a.out 1047552