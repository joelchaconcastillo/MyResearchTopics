for niche in 10 20 30 40 50 60 70 80 90 100;
do
  for nobj in {2..3};
  do
     reference=""
     #for k in $(seq 1 $nobj); do reference=$reference" "$((2*$k+1)); done
     for k in $(seq 1 $nobj); do reference=$reference" "$(echo print 2*${k} + 0.2*${k}| perl); done
     for i in WFG1 WFG2 WFG3 WFG4 WFG5 WFG6 WFG7 WFG8 WFG9;
     do
  	   fileout=${i}_${nobj}_${niche}
  	   rm $fileout
   	   for k in {1..35}
  	   do
  	   file=../POF/POF_MOEAD_${i}_RUN${k}_*_nobj_${nobj}_niche_${niche}.dat_bounded
  	      v1=$(cat $file | cut -d' ' -f 1-$((2*$nobj)) |./hv -r "$reference")
	      v2=$(./hv -r "$reference" ../Optimals/${i}_${nobj}.txt  )
	     echo print ${v1}/${v2} | perl  >> $fileout
	     echo "" >>$fileout 
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
  	      v1=$(cat $file | cut -d' ' -f 1-$((2*$nobj)) |./hv -r "$reference")
	      v2=$(./hv -r "$reference" ../Optimals/${i}_${nobj}.txt  )
	     echo print ${v1}/${v2} | perl >> $fileout
	     echo "" >>$fileout 
                 #cat $file | cut -d' ' -f 1-$((2*$nobj)) |./hv -r "$reference" >> $fileout
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
  	      v1=$(cat $file | cut -d' ' -f 1-$((2*$nobj)) |./hv -r "$reference")
	      v2=$(./hv -r "$reference" ../Optimals/${i}_${nobj}.txt  )
	     echo print ${v1}/${v2} | perl >> $fileout
	     echo "" >>$fileout 
#                 cat $file | cut -d' ' -f 1-$((2*$nobj)) |./hv -r "$reference" >> $fileout
              done
        done
     fi





     reference=""
     for k in $(seq 1 $nobj); do reference=$reference" "1.1; done
     for i in DTLZ2 DTLZ4;
     do
  	   fileout=${i}_${nobj}_${niche}
  	   rm $fileout
   	   for k in {1..35}
  	   do
  	   file=../POF/POF_MOEAD_${i}_RUN${k}_*_nobj_${nobj}_niche_${niche}.dat_bounded
   	     v1=$(cat $file | cut -d' ' -f 1-$((2*$nobj)) |./hv -r "$reference")
	     v2=$(./hv -r "$reference" ../Optimals/${i}_${nobj}.txt  )
	     echo print ${v1}/${v2} | perl >> $fileout
	     echo "" >>$fileout 
  	     # cat $file | cut -d' ' -f 1-$((2*$nobj)) |./hv -r "$reference" >> $fileout
  	   done
     done
  
     reference=""
     i="DTLZ1"
     for k in $(seq 1 $nobj); do reference=$reference" "0.55; done
  	   fileout=${i}_${nobj}_${niche}
             rm $fileout
     for k in {1..35}
     do
     file=../POF/POF_MOEAD_${i}_RUN${k}_*_nobj_${nobj}_niche_${niche}.dat_bounded
   	     v1=$(cat $file | cut -d' ' -f 1-$((2*$nobj)) |./hv -r "$reference")
	     v2=$(./hv -r "$reference" ../Optimals/${i}_${nobj}.txt  )
	     echo print ${v1}/${v2} | perl >> $fileout
	     echo "" >>$fileout 
        #cat $file | cut -d' ' -f 1-$((2*$nobj)) |./hv -r "$reference" >> $fileout
     done
  
     reference=""
     i="DTLZ3"
     for k in $(seq 1 $nobj); do reference=$reference" "1.1; done
  	   fileout=${i}_${nobj}_${niche}
     	   rm $fileout
     for k in {1..35}
     do
     file=../POF/POF_MOEAD_${i}_RUN${k}_*_nobj_${nobj}_niche_${niche}.dat_bounded
 	    v1=$(cat $file | cut -d' ' -f 1-$((2*$nobj)) |./hv -r "$reference")
	     v2=$(./hv -r "$reference" ../Optimals/${i}_${nobj}.txt  )
	     echo print ${v1}/${v2} | perl >> $fileout
	     echo "" >>$fileout 
        #cat $file | cut -d' ' -f 1-$((2*$nobj)) |./hv -r "$reference" >> $fileout
     done
  
     reference=""
     if [ $nobj -eq 2 ]
     then

        reference="1.1 1.1"
     fi
     if [ $nobj -eq 3 ]
     then
        value=$(awk 'BEGIN{print sqrt(0.5)+0.1*sqrt(0.5)}')
        reference="$value $value 1.1"
     fi

     i="DTLZ5"
 #    for k in $(seq 1 $nobj); do reference=$reference" "4; done
  	   fileout=${i}_${nobj}_${niche}
     	   rm $fileout
     for k in {1..35}
     do
     file=../POF/POF_MOEAD_${i}_RUN${k}_*_nobj_${nobj}_niche_${niche}.dat_bounded
    	  v1=$(cat $file | cut -d' ' -f 1-$((2*$nobj)) |./hv -r "$reference")
	  v2=$(./hv -r "$reference" ../Optimals/${i}_${nobj}.txt  )
	     echo print ${v1}/${v2} | perl >> $fileout
	     echo "" >>$fileout 
#        cat $file | cut -d' ' -f 1-$((2*$nobj)) |./hv -r "$reference" >> $fileout
     done
     i="DTLZ6"
     #for k in $(seq 1 $nobj); do reference=$reference" "11; done
  	   fileout=${i}_${nobj}_${niche}
     	   rm $fileout
     for k in {1..35}
     do
     file=../POF/POF_MOEAD_${i}_RUN${k}_*_nobj_${nobj}_niche_${niche}.dat_bounded
    	  v1=$(cat $file | cut -d' ' -f 1-$((2*$nobj)) |./hv -r "$reference")
	  v2=$(./hv -r "$reference" ../Optimals/${i}_${nobj}.txt  )
	     echo print ${v1}/${v2} | perl >> $fileout
	     echo "" >>$fileout 
        #cat $file | cut -d' ' -f 1-$((2*$nobj)) |./hv -r "$reference" >> $fileout
     done
  
     reference=""
     i="DTLZ7"
      if [ $nobj -eq 2 ]
     then

        reference="1.1 4.4"
     fi
     if [ $nobj -eq 3 ]
     then
        reference="1.1 1.1 6.6"
     fi
#     for k in $(seq 1 $nobj); do reference=$reference" "21; done
  	   fileout=${i}_${nobj}_${niche}
     	   rm $fileout
     for k in {1..35}
     do
     file=../POF/POF_MOEAD_${i}_RUN${k}_*_nobj_${nobj}_niche_${niche}.dat_bounded
	  v1=$(cat $file | cut -d' ' -f 1-$((2*$nobj)) |./hv -r "$reference")
	  v2=$(./hv -r "$reference" ../Optimals/${i}_${nobj}.txt  )
	     echo print ${v1}/${v2} | perl >> $fileout
	     echo "" >>$fileout 
        #cat $file | cut -d' ' -f 1-$((2*$nobj)) |./hv -r "$reference" >> $fileout
     done
  
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
