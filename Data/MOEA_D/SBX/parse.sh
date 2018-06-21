for instance in WFG1 WFG2 WFG3 WFG4 WFG5 WFG6 WFG7 WFG8 WFG9 DTLZ1 DTLZ2 DTLZ3 DTLZ4 DTLZ5 DTLZ6 DTLZ7 UF1 UF2 UF3 UF4 UF5 UF6 UF7
do
   for sed in {1..35}   
   do
#OBJ_GD3_CROSS_SELECTON_DIFERENTAL_EVALUATIONS_250000_DTLZ6_SEED_20.txt_2obj
#POF_MOEAD_UF6_RUN25_seed_25_2.dat
   mv POF/*_${instance}_*seed_${sed}_2.dat POF/${instance}_2_${sed}
   done
done
for instance in WFG1 WFG2 WFG3 WFG4 WFG5 WFG6 WFG7 WFG8 WFG9 DTLZ1 DTLZ2 DTLZ3 DTLZ4 DTLZ5 DTLZ6 DTLZ7 UF8 UF9 UF10
do
   for sed in {1..35}   
   do
#OBJ_GD3_CROSS_SELECTON_DIFERENTAL_EVALUATIONS_250000_WFG9_SEED_34.txt_3obj
   mv POF/*_${instance}_*seed_${sed}_3.dat POF/${instance}_3_${sed}
   done
done
