#Con este script se genera la lista de ejecuciones....
#!/usr/bin/perl
use strict;
use warnings;
use Getopt::Long;
my $file = "ExecutionFileDiversity";
my $fout;
open($fout, '>' ,$file);
my $Path = "/home/user_demo/Chacon/Tesis/Dominance_Diversity/Core";
my $Instance=0;
my $Sed=0;

####Realizar la búsqueda del parámetro D inicial que proporcione mejores resultados
#my @DI = ("0.1", "0.2", "0.3", "0.4", "0.5", "0.6", "0.7", "0.8", "0.9"); ##Parámetro inicial de diversidad.... 0.25*sqrt(24)......
my @DI = ("0.2"); ##Parámetro inicial de diversidad.... 0.25*sqrt(24)......
my $PathAlgorithm = $Path."/Algorithms/VSD-MOEA-2obj";
my @Instances= ("WFG1", "WFG2", "WFG3", "WFG4", "WFG5", "WFG6", "WFG7", "WFG8", "WFG9", "DTLZ1", "DTLZ2", "DTLZ3", "DTLZ4", "DTLZ5", "DTLZ6", "DTLZ7", "UF1", "UF2", "UF3", "UF4", "UF5", "UF6", "UF7");
#my @Instances= ("DTLZ7");
#my @Instances= ("WFG1", "WFG2", "WFG3", "WFG4", "WFG5", "WFG6", "WFG7", "WFG8", "WFG9");
#my @Instances= ("ZDT1","ZDT2", "ZDT3", "ZDT4", "ZDT6"); ##La ZDT5 es para cadenas binarias.....
foreach(@DI)
{
#	for(my $i = 0 ; $i <= le(@Instances); $i++) ##Para cada instancia WFG...
	foreach my $i (@Instances)
	{
		for($Sed = 1; $Sed <=35; $Sed++) ##Realizar 35 ejecuciones con distintas semilla de cada instancia..
		{
			#print $fout "~$PathAlgorithm/MODiversity --Instance WFG$Instance --Sed $Sed --SizePool 100 --Generations 250000 --PeriodReport 2500 --Crossover SBXHybridDynamic --Mutation Polynomial --Label D$_ --Path $Path/Results_SizePool100/Diversity_Based_Dominance_HybridDynamic_Operator_D025sqrtN/ --DI $_ \n";
			print $fout "~$PathAlgorithm/MODiversity --Instance ".$i." --Sed $Sed --SizePool 100 --Generations 250000 --PeriodReport 2500 --Crossover SBXHybridDynamic --Mutation Polynomial --Label D$_ --Path $Path/VSD-MOEA-Improvement-Rank/obj2/ --DI $_ \n";
		}
	}
	
}
