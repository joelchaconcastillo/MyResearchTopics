#Con este script se genera la lista de ejecuciones....
#!/usr/bin/perl
use strict;
use warnings;
use Getopt::Long;
my $file = "ExecutionFileDiversity";
my $fout;
open($fout, '>' ,$file);
my $Path = "/home/joel.chacon/Chacon/DE_diversity/Parametrization/Case1/";
my $Instance=0;
my $Sed=0;

####Realizar la búsqueda del parámetro D inicial que proporcione mejores resultados
my $PathAlgorithm = $Path;

my @Dimension =("10");#, "30", "50", "100");
  
##Params...//.Exec path sed n_problem dimension popsize Di
my $sizePop = 50;
#foreach(@DI)
foreach(@Dimension)
{
	for( my $problem= 1; $problem <=30; $problem++) ##Realizar 35 ejecuciones con distintas semilla de cada instancia..
	{
		for(my $Sed = 1; $Sed <=51; $Sed++) ##Realizar 35 ejecuciones con distintas semilla de cada instancia..
		{
			print $fout "~$PathAlgorithm/DE_Next_Generation_exe $Path $Sed $problem $_ $sizePop 0.1\n";
		}
	}
	
}
