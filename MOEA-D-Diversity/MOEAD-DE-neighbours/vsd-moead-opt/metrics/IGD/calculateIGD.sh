for niche in 10 20 30 40 50 60 70 80 90 100;
do
  for nobj in {2..3};
  do
     for i in WFG1 WFG2 WFG3 WFG4 WFG5 WFG6 WFG7 WFG8 WFG9 DTLZ1 DTLZ2 DTLZ3 DTLZ4 DTLZ5 DTLZ6 DTLZ7;
     do
  	   fileout=${i}_${nobj}_${niche}
  	   rm $fileout
   	   for k in {1..35}
  	   do
  	     file=../POF/POF_MOEAD_${i}_RUN${k}_*_nobj_${nobj}_niche_${niche}.dat_bounded
	     cat ${file} | ./IGD.exe --IGD --r ../Optimals/${i}_${nobj}.txt >> $fileout
  	   done 
     done
     if [ $nobj -eq 2 ]
        then
        reference=""
        for k in $(seq 1 $nobj); do reference=$reference" "1.1; done
        for i in UF1 UF2 UF3 UF4 UF5 UF6 UF7;
        do
  	      fileout=${i}_${nobj}_${niche}
              rm $fileout
              for k in {1..35}
              do
              file=../POF/POF_MOEAD_${i}_RUN${k}_*_nobj_${nobj}_niche_${niche}.dat_bounded
	     cat ${file} | ./IGD.exe --IGD --r ../Optimals/${i}_${nobj}.txt >> $fileout
              done
        done
     fi

     if [ $nobj -eq 3 ]
        then
        reference=""
        for k in $(seq 1 $nobj); do reference=$reference" "1.1; done
        for i in UF8 UF9 UF10;
        do
  	      fileout=${i}_${nobj}_${niche}
              rm $fileout
              for k in {1..35}
              do
              file=../POF/POF_MOEAD_${i}_RUN${k}_*_nobj_${nobj}_niche_${niche}.dat_bounded
	     cat ${file} | ./IGD.exe --IGD --r ../Optimals/${i}_${nobj}.txt >> $fileout
#                 cat $file | cut -d' ' -f 1-$((2*$nobj)) |./hv -r "$reference" >> $fileout
              done
        done
     fi
 done
done


rm RESULT*
rm Total*
echo "">RESULT
for inst in {1..9}
do
   echo "-----instance WFG"$inst  >> RESULT
   for nobj in {2..3};
   do
      for niche in 10 20 30 40 50 60 70 80 90 100;
      do

         cat WFG${inst}_${nobj}_${niche} | Rscript -e 'mean (as.numeric (readLines ("stdin")))' >> RESULT
         cat WFG${inst}_${nobj}_${niche} | Rscript -e 'mean (as.numeric (readLines ("stdin")))' >> RESULT_${niche}_${nobj}
      done
   done
done
for inst in {1..7}
do
   echo "-----instance DTLZ"$inst  >> RESULT
   for nobj in {2..3}
   do
      for niche in 10 20 30 40 50 60 70 80 90 100;
      do
           cat DTLZ${inst}_${nobj}_${niche} | Rscript -e 'mean (as.numeric (readLines ("stdin")))' >> RESULT
           cat DTLZ${inst}_${nobj}_${niche} | Rscript -e 'mean (as.numeric (readLines ("stdin")))' >> RESULT_${niche}_${nobj}
      done
   done
done
for inst in {1..7}
do
   echo "-----instance UF"$inst  >> RESULT
      for niche in 10 20 30 40 50 60 70 80 90 100;
      do
           cat UF${inst}_2_${niche} | Rscript -e 'mean (as.numeric (readLines ("stdin")))' >> RESULT
           cat UF${inst}_2_${niche} | Rscript -e 'mean (as.numeric (readLines ("stdin")))' >> RESULT_${niche}_2
      done
done
for inst in {8..10}
do
   echo "-----instance UF"$inst  >> RESULT
      for niche in 10 20 30 40 50 60 70 80 90 100;
      do
           cat UF${inst}_3_${niche} | Rscript -e 'mean (as.numeric (readLines ("stdin")))' >> RESULT
           cat UF${inst}_3_${niche} | Rscript -e 'mean (as.numeric (readLines ("stdin")))' >> RESULT_${niche}_3
      done
done

#total mean By niche
for niche in 10 20 30 40 50 60 70 80 90 100;
do 
echo $niche
cut -f2 -d' ' RESULT_${niche}_2 | Rscript -e ' dat=as.numeric( readLines ("stdin"));  print( paste(paste(paste(min(dat), max(dat)),mean(dat)), sd(dat))) '>> Total_2
cut -f2 -d' ' RESULT_${niche}_3 | Rscript -e ' dat=as.numeric( readLines ("stdin"));  print( paste(paste(paste(min(dat), max(dat)),mean(dat)), sd(dat))) '>> Total_3
done
