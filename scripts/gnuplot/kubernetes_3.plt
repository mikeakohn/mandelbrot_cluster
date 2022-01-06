set title "Mandelbrot Cluster"
set xlabel "Frame"
set xrange [0:4668]
set ylabel "Time In Seconds"
set yrange [0:100]
set term png
set output "kubernetes_3.png"
set datafile separator "|"
plot "kubernetes_3.dat" using 1:2 title "kubernetes-3"

