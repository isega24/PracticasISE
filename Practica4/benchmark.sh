#!/bin/bash

g++ Benchmark.c -o Benchmark
g++ media.cpp -o media
i=1000

./Benchmark $i > resultado.txt
./Benchmark $i >> resultado.txt
./Benchmark $i >> resultado.txt
./Benchmark $i >> resultado.txt
./Benchmark $i >> resultado.txt

cat resultado.txt | ./media
echo ""
rm Benchmark media resultado.txt
