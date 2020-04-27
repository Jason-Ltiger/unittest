#!/bin/bash

if [ ! -d "build"  ];then
     mkdir build
  
  fi
cd build
make clean
cmake .. -DCMAKE_BUILD_TYPE=Debug
make
