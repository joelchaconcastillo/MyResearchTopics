niche=10
#POF_MOEAD_UF6_RUN7_seed_30_nobj_2_niche_10.dat_bounded-5.477226_D_1.0
#for Di in 0.0 0.1 0.2 0.3 0.4 0.5 0.6 0.7 0.8 0.9 1.0 1.1;
#do
#  for nobj in {2..3};
#  do
#     reference=""
#     for k in $(seq 1 $nobj); do reference=$reference" "$((2*$k+1)); done
#     for i in WFG1 WFG2 WFG3 WFG4 WFG5 WFG6 WFG7 WFG8 WFG9;
#     do
#  	   fileout=${i}_${nobj}_${Di}
#  	   rm $fileout
#   	   for k in {1..35}
#  	   do
#  	   file=../POF/POF_MOEAD_${i}_RUN${k}_*_nobj_${nobj}_niche_${niche}.dat_bounded*_${Di}
#  	      v1=$(cat $file | cut -d' ' -f 1-$((2*$nobj)) |./hv -r "$reference")
#	      v2=$(./hv -r "$reference" ../Optimals/${i}_${nobj}.txt  )
#	     echo print ${v1}/${v2} | perl  >> $fileout
#	     echo "" >>$fileout 
#  	   done 
#     done
#     if [ $nobj -eq 2 ]
#        then
#        reference=""
#        for k in $(seq 1 $nobj); do reference=$reference" "1.1; done
#        for i in UF1 UF2 UF3 UF4 UF5 UF6 UF7;
#        do
#  	      fileout=${i}_${nobj}_${Di}
#              rm $fileout
#              for k in {1..35}
#              do
#              file=../POF/POF_MOEAD_${i}_RUN${k}_*_nobj_${nobj}_niche_${niche}.dat_bounded*_${Di}
#  	      v1=$(cat $file | cut -d' ' -f 1-$((2*$nobj)) |./hv -r "$reference")
#	      v2=$(./hv -r "$reference" ../Optimals/${i}_${nobj}.txt  )
#	     echo print ${v1}/${v2} | perl >> $fileout
#	     echo "" >>$fileout 
#                 #cat $file | cut -d' ' -f 1-$((2*$nobj)) |./hv -r "$reference" >> $fileout
#              done
#        done
#     fi
#
#     if [ $nobj -eq 3 ]
#        then
#        reference=""
#        for k in $(seq 1 $nobj); do reference=$reference" "1.1; done
#        for i in UF8 UF9 UF10;
#        do
#  	      #fileout=${i}_${nobj}_${niche}
#  	      fileout=${i}_${nobj}_${Di}
#              rm $fileout
#              rm $fileout
#              for k in {1..35}
#              do
#              file=../POF/POF_MOEAD_${i}_RUN${k}_*_nobj_${nobj}_niche_${niche}.dat_bounded*_${Di}
#  	      v1=$(cat $file | cut -d' ' -f 1-$((2*$nobj)) |./hv -r "$reference")
#	      v2=$(./hv -r "$reference" ../Optimals/${i}_${nobj}.txt  )
#	     echo print ${v1}/${v2} | perl >> $fileout
#	     echo "" >>$fileout 
##                 cat $file | cut -d' ' -f 1-$((2*$nobj)) |./hv -r "$reference" >> $fileout
#              done
#        done
#     fi
#
#
#
#
#
#     reference=""
#     for k in $(seq 1 $nobj); do reference=$reference" "2; done
#     for i in DTLZ2 DTLZ4;
#     do
#  	   fileout=${i}_${nobj}_${Di}
#  	   #fileout=${i}_${nobj}_${niche}
#  	   rm $fileout
#   	   for k in {1..35}
#  	   do
#  	   file=../POF/POF_MOEAD_${i}_RUN${k}_*_nobj_${nobj}_niche_${niche}.dat_bounded*_${Di}
#   	     v1=$(cat $file | cut -d' ' -f 1-$((2*$nobj)) |./hv -r "$reference")
#	     v2=$(./hv -r "$reference" ../Optimals/${i}_${nobj}.txt  )
#	     echo print ${v1}/${v2} | perl >> $fileout
#	     echo "" >>$fileout 
#  	     # cat $file | cut -d' ' -f 1-$((2*$nobj)) |./hv -r "$reference" >> $fileout
#  	   done
#     done
#  
#     reference=""
#     i="DTLZ1"
#     for k in $(seq 1 $nobj); do reference=$reference" "1; done
#  	   #fileout=${i}_${nobj}_${niche}
#  	   fileout=${i}_${nobj}_${Di}
#             rm $fileout
#     for k in {1..35}
#     do
#     file=../POF/POF_MOEAD_${i}_RUN${k}_*_nobj_${nobj}_niche_${niche}.dat_bounded*_${Di}
#   	     v1=$(cat $file | cut -d' ' -f 1-$((2*$nobj)) |./hv -r "$reference")
#	     v2=$(./hv -r "$reference" ../Optimals/${i}_${nobj}.txt  )
#	     echo print ${v1}/${v2} | perl >> $fileout
#	     echo "" >>$fileout 
#        #cat $file | cut -d' ' -f 1-$((2*$nobj)) |./hv -r "$reference" >> $fileout
#     done
#  
#     reference=""
#     i="DTLZ3"
#     for k in $(seq 1 $nobj); do reference=$reference" "7; done
#  	   fileout=${i}_${nobj}_${Di}
#  	   #fileout=${i}_${nobj}_${niche}
#     	   rm $fileout
#     for k in {1..35}
#     do
#     file=../POF/POF_MOEAD_${i}_RUN${k}_*_nobj_${nobj}_niche_${niche}.dat_bounded*_${Di}
# 	    v1=$(cat $file | cut -d' ' -f 1-$((2*$nobj)) |./hv -r "$reference")
#	     v2=$(./hv -r "$reference" ../Optimals/${i}_${nobj}.txt  )
#	     echo print ${v1}/${v2} | perl >> $fileout
#	     echo "" >>$fileout 
#        #cat $file | cut -d' ' -f 1-$((2*$nobj)) |./hv -r "$reference" >> $fileout
#     done
#  
#     reference=""
#     i="DTLZ5"
#     for k in $(seq 1 $nobj); do reference=$reference" "4; done
#  	   #fileout=${i}_${nobj}_${niche}
#  	   fileout=${i}_${nobj}_${Di}
#     	   rm $fileout
#     for k in {1..35}
#     do
#     file=../POF/POF_MOEAD_${i}_RUN${k}_*_nobj_${nobj}_niche_${niche}.dat_bounded*_${Di}
#    	  v1=$(cat $file | cut -d' ' -f 1-$((2*$nobj)) |./hv -r "$reference")
#	  v2=$(./hv -r "$reference" ../Optimals/${i}_${nobj}.txt  )
#	     echo print ${v1}/${v2} | perl >> $fileout
#	     echo "" >>$fileout 
##        cat $file | cut -d' ' -f 1-$((2*$nobj)) |./hv -r "$reference" >> $fileout
#     done
#  
#     reference=""
#     i="DTLZ6"
#     for k in $(seq 1 $nobj); do reference=$reference" "11; done
#  	   #fileout=${i}_${nobj}_${niche}
#  	   fileout=${i}_${nobj}_${Di}
#     	   rm $fileout
#     for k in {1..35}
#     do
#     file=../POF/POF_MOEAD_${i}_RUN${k}_*_nobj_${nobj}_niche_${niche}.dat_bounded*_${Di}
#    	  v1=$(cat $file | cut -d' ' -f 1-$((2*$nobj)) |./hv -r "$reference")
#	  v2=$(./hv -r "$reference" ../Optimals/${i}_${nobj}.txt  )
#	     echo print ${v1}/${v2} | perl >> $fileout
#	     echo "" >>$fileout 
#        #cat $file | cut -d' ' -f 1-$((2*$nobj)) |./hv -r "$reference" >> $fileout
#     done
#  
#     reference=""
#     i="DTLZ7"
#     for k in $(seq 1 $nobj); do reference=$reference" "21; done
#  	   #fileout=${i}_${nobj}_${niche}
#  	   fileout=${i}_${nobj}_${Di}
#     	   rm $fileout
#     for k in {1..35}
#     do
#     file=../POF/POF_MOEAD_${i}_RUN${k}_*_nobj_${nobj}_niche_${niche}.dat_bounded*_${Di}
#	  v1=$(cat $file | cut -d' ' -f 1-$((2*$nobj)) |./hv -r "$reference")
#	  v2=$(./hv -r "$reference" ../Optimals/${i}_${nobj}.txt  )
#	     echo print ${v1}/${v2} | perl >> $fileout
#	     echo "" >>$fileout 
#        #cat $file | cut -d' ' -f 1-$((2*$nobj)) |./hv -r "$reference" >> $fileout
#     done
#  
#  done
#done


rm RESULT*
rm Total*
echo "">RESULT
for inst in {1..9}
do
   echo "-----instance WFG"$inst  >> RESULT
   for nobj in {2..3};
   do
      #for niche in 10 20 30 40 50 60 70 80 90 100;
      for Di in 0.0 0.1 0.2 0.3 0.4 0.5 0.6 0.7 0.8 0.9 1.0 1.1;
      #for Di in 0_0 0_1 0_2 0_3 0_4 0_5 0_6 0_7 0_8 0_9 1_0 1_1
      do

         cat WFG${inst}_${nobj}_${Di} | Rscript -e 'mean (as.numeric (readLines ("stdin")))' >> RESULT
         cat WFG${inst}_${nobj}_${Di} | Rscript -e 'mean (as.numeric (readLines ("stdin")))' >> RESULT_${Di}_${nobj}
      done
   done
done

   for inst in {1..7}
   do
      echo "-----instance DTLZ"$inst  >> RESULT
      for nobj in {2..3}
      do
         for Di in 0.0 0.1 0.2 0.3 0.4 0.5 0.6 0.7 0.8 0.9 1.0 1.1;
	 #for Di in 0_0 0_1 0_2 0_3 0_4 0_5 0_6 0_7 0_8 0_9 1_0 1_1
         #for niche in 10 20 30 40 50 60 70 80 90 100;
         do
              cat DTLZ${inst}_${nobj}_${Di} | Rscript -e 'mean (as.numeric (readLines ("stdin")))' >> RESULT
              cat DTLZ${inst}_${nobj}_${Di} | Rscript -e 'mean (as.numeric (readLines ("stdin")))' >> RESULT_${Di}_${nobj}
         done
      done
   done
   for inst in {1..7}
   do
      echo "-----instance UF"$inst  >> RESULT
         for Di in 0.0 0.1 0.2 0.3 0.4 0.5 0.6 0.7 0.8 0.9 1.0 1.1;
	 #for Di in 0_0 0_1 0_2 0_3 0_4 0_5 0_6 0_7 0_8 0_9 1_0 1_1
         #for niche in 10 20 30 40 50 60 70 80 90 100;
         do
              cat UF${inst}_2_${Di} | Rscript -e 'mean (as.numeric (readLines ("stdin")))' >> RESULT
              cat UF${inst}_2_${Di} | Rscript -e 'mean (as.numeric (readLines ("stdin")))' >> RESULT_${Di}_2
         done
   done
   for inst in {8..10}
   do
      echo "-----instance UF"$inst  >> RESULT
         for Di in 0.0 0.1 0.2 0.3 0.4 0.5 0.6 0.7 0.8 0.9 1.0 1.1
	 #for Di in 0_0 0_1 0_2 0_3 0_4 0_5 0_6 0_7 0_8 0_9 1_0 1_1
         #for niche in 10 20 30 40 50 60 70 80 90 100;
         do
              cat UF${inst}_3_${Di} | Rscript -e 'mean (as.numeric (readLines ("stdin")))' >> RESULT
              cat UF${inst}_3_${Di} | Rscript -e 'mean (as.numeric (readLines ("stdin")))' >> RESULT_${Di}_3
         done
   done

#total mean By niche

#for Di in 0_0 0_1 0_2 0_3 0_4 0_5 0_6 0_7 0_8 0_9 1_0 1_1;
for Di in 0.0 0.1 0.2 0.3 0.4 0.5 0.6 0.7 0.8 0.9 1.0 1.1;
do 
echo $Di
   cut -f2 -d' ' RESULT_${Di}_2 | Rscript -e ' dat=as.numeric( readLines ("stdin"));  print( paste(paste(paste(min(dat), max(dat)),mean(dat)), sd(dat))) '>> Total_2
   cut -f2 -d' ' RESULT_${Di}_3 | Rscript -e ' dat=as.numeric( readLines ("stdin"));  print( paste(paste(paste(min(dat), max(dat)),mean(dat)), sd(dat))) '>> Total_3
done
