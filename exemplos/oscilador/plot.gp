#!/usr/bin/env gnuplot

set term png size 1920, 1080 font "serif,24" enhanced
set encoding utf8

set output "figura.png"
set size square
set multiplot layout 1,2 columns title "Oscilador Vertical Amortecido"

set grid
set key off

set xlabel "ω t"
set ylabel "-k / mg  y"

set xrange [0:10]

plot "dados.dat" u 1:2 w l lc rgb "black"

set xlabel "Q"
set ylabel "P"

unset xrange

plot "dados.dat" u 2:3 w l lc rgb "black"

exit