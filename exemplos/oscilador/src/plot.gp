#!/usr/bin/env gnuplot

set term png size 1080, 1080 font "serif,24" enhanced
set encoding utf8
set size square

set grid
set key off

set output "figura_00.png"
   set title "Oscilador Vertical"

   set xlabel "ω t"
   set ylabel "k / mg  y"

   set xrange [0:20]

   plot "dados.dat" u 1:2 w l lc rgb "black"

set output "figura_01.png"
   set xlabel "k / mg  y"
   set ylabel "ω / g  v"

   unset xrange

   plot "dados.dat" u 2:3 w l lc rgb "black"

exit