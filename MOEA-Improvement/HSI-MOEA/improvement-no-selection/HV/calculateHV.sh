for nobj in {2..5};
do
   reference=""
   for k in $(seq 1 $nobj); do reference=$reference" "$((2*$k+1)); done
   for i in WFG1 WFG2 WFG3 WFG4 WFG5 WFG6 WFG7 WFG8 WFG9;
   do
	   fileout=${i}_$nobj
	   rm $fileout
 	   for k in {1..30}
	   do
	   file=../POF_MOEAD_${i}_RUN${k}_*_nobj_${nobj}.dat_bounded
	      cat $file | cut -d' ' -f 1-$((2*$nobj)) |./hv -r "$reference" >> $fileout
	   done
   done
   reference=""
   for k in $(seq 1 $nobj); do reference=$reference" "2; done
   for i in DTLZ2 DTLZ4;
   do
	   fileout=${i}_$nobj
	   rm $fileout
 	   for k in {1..30}
	   do
	   file=../POF_MOEAD_${i}_RUN${k}_*_nobj_${nobj}.dat_bounded
	      cat $file | cut -d' ' -f 1-$((2*$nobj)) |./hv -r "$reference" >> $fileout
	   done
   done

   reference=""
   i="DTLZ1"
   for k in $(seq 1 $nobj); do reference=$reference" "1; done
   fileout=${i}_$nobj
   rm $fileout
   for k in {1..30}
   do
   file=../POF_MOEAD_${i}_RUN${k}_*_nobj_${nobj}.dat_bounded
      cat $file | cut -d' ' -f 1-$((2*$nobj)) |./hv -r "$reference" >> $fileout
   done

   reference=""
   i="DTLZ3"
   for k in $(seq 1 $nobj); do reference=$reference" "7; done
   fileout=${i}_$nobj
   rm $fileout
   for k in {1..30}
   do
   file=../POF_MOEAD_${i}_RUN${k}_*_nobj_${nobj}.dat_bounded
      cat $file | cut -d' ' -f 1-$((2*$nobj)) |./hv -r "$reference" >> $fileout
   done

   reference=""
   i="DTLZ5"
   for k in $(seq 1 $nobj); do reference=$reference" "4; done
   fileout=${i}_$nobj
   rm $fileout
   for k in {1..30}
   do
   file=../POF_MOEAD_${i}_RUN${k}_*_nobj_${nobj}.dat_bounded
      cat $file | cut -d' ' -f 1-$((2*$nobj)) |./hv -r "$reference" >> $fileout
   done

   reference=""
   i="DTLZ6"
   for k in $(seq 1 $nobj); do reference=$reference" "11; done
   fileout=${i}_$nobj
   rm $fileout
   for k in {1..30}
   do
   file=../POF_MOEAD_${i}_RUN${k}_*_nobj_${nobj}.dat_bounded
      cat $file | cut -d' ' -f 1-$((2*$nobj)) |./hv -r "$reference" >> $fileout
   done

   reference=""
   i="DTLZ7"
   for k in $(seq 1 $nobj); do reference=$reference" "21; done
   fileout=${i}_$nobj
   rm $fileout
   for k in {1..30}
   do
   file=../POF_MOEAD_${i}_RUN${k}_*_nobj_${nobj}.dat_bounded
      cat $file | cut -d' ' -f 1-$((2*$nobj)) |./hv -r "$reference" >> $fileout
   done

done

echo "">RESULT
for inst in {1..9}
do
   echo "-----instance WFG"$inst  >> RESULT
   for nobj in {2..5};
   do
      cat WFG${inst}_${nobj} | Rscript -e 'mean (as.numeric (readLines ("stdin")))' >> RESULT
   done
done
for inst in {1..7}
do
   echo "-----instance DTLZ"$inst  >> RESULT
   for nobj in {2..5}
   do
      cat DTLZ${inst}_${nobj} | Rscript -e 'mean (as.numeric (readLines ("stdin")))' >> RESULT
   done
done

