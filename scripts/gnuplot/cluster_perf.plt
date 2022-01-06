set title "Mandelbrot Cluster"
set xlabel "Frame"
set xrange [0:4668]
set ylabel "Time In Seconds"
set yrange [0:100]
set term png
set output "cluster_perf.png"
plot "second_perf.dat" title "Performance"

