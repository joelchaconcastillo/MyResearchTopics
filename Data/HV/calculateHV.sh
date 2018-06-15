algname=(GDE3 MOEA_D_DE MOEA_D_SBX NSGAII_SBX Proposal_SBX Proposal_DE)
##Calculating the HV considering plus 10% for each objective
   cont=0
for alg in GDE3/POF MOEA_D/DE/POF MOEA_D/SBX/POF NSGAII/SBX/POF Proposal/SBX/POF Proposal/DE/POF
do
   for i in WFG1 WFG2 WFG3 WFG4 WFG5 WFG6 WFG7 WFG8 WFG9;
	do
		rm ${algname[$cont]}/${i}_2

	   for file in ../$alg/${i}_2*
	   do
	   ./hv -r "2.2 4.4" $file >>${algname[${cont}]}/${i}_2
	   done
        done
   cont=$((cont+1))
done
