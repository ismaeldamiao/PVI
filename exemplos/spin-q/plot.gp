#!/usr/bin/env gnuplot

set term png size 1280, 720 font "serif,24" enhanced
set encoding utf8

set grid
set key box center right

set output "figura.png"
set title  "Spin no Campo Magnético"
set xlabel "t"
set ylabel "Probabilidade"

set xrange [0:10]
set yrange [0:1]

plot \
   "dados.dat" u 1:2 w l lc rgb "blue"  t "|Ψ_+|^2", \
   "dados.dat" u 1:3 w l lc rgb "red"   t "|Ψ_-|^2"

exit