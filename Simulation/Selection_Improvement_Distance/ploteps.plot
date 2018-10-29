set encoding utf8
#set yrange[0:0.5]
set title "Distancia Euclidea"
#set key outside
unset key
set term post color 18
set xlabel "f1"
set ylabel "f2"
set zlabel "f3"
set view 40,65
set output "euclidea.eps"
splot "normal" #DTLZ4_2obj.txt" using 1:2 with linespoints title "GDE3", "DTLZ4_2obj.txt" using 1:3 with linespoints title "MOMBI-II",  "DTLZ4_2obj.txt" using 1:4 with linespoints title "NSGA-II", "DTLZ4_2obj.txt"using 1:5 with linespoints title "MOEA/D", "DTLZ4_2obj.txt" using 1:6 with linespoints title "VSD-MOEA" ;

#set yrange[0:0.8]
set title "Distancia de mejoria"
#set key outside
unset key
set term post color 18
set xlabel "f1"
set ylabel "f2"
set zlabel "f3"
set view 40,65
set output "mejoria.eps"
splot "Improvement_Distance" # using 1:2 with linespoints title "GDE3", "DTLZ4_3obj.txt" using 1:3 with linespoints title "MOMBI-II",  "DTLZ4_3obj.txt" using 1:4 with linespoints title "NSGA-II", "DTLZ4_3obj.txt"using 1:5 with linespoints title "MOEA/D", "DTLZ4_3obj.txt" using 1:6 with linespoints title "VSD-MOEA" ;


