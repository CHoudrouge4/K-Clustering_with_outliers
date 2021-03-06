#!/usr/bin/gnuplot
#
# Plotting coordinate points
#
# AUTHOR: Hagen Wierstorf
# gnuplot 4.6 patchlevel 0

reset

# wxt
set terminal wxt size 500,500 enhanced font 'Verdana,10' persist
# png
#set terminal pngcairo size 350,262 enhanced font 'Verdana,10'
set output 'data1.jpg'

# color definitions
set border linewidth 1.5
set style line 1 lc rgb '#0060ad' pt 7 ps 1.5 lt 1 lw 2 # --- blue

unset key

# Axes
set style line 11 lc rgb '#808080' lt 1
set border 3 back ls 11
set tics nomirror out scale 0.75
# Grid
set style line 12 lc rgb'#808080' lt 0 lw 1
set grid back ls 12

set xrange [-20:20]
set yrange [-20:20]
plot 'c1.txt' w p ls 1
