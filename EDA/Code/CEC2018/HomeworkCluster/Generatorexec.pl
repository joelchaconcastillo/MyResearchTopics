#Con este script se genera la lista de ejecuciones....
#!/usr/bin/perl
use strict;
use warnings;
use Getopt::Long;
my $file = "ExecutionFileDiversity";
my $fout;
open($fout, '>' ,$file);
my $Path = `cd ..; pwd`; #   "/home/joel.chacon/Chacon/DE_diversity/CEC2018/";
chomp $Path;
my $Instance=0;
my $Sed=0;

####Realizar la búsqueda del parámetro D inicial que proporcione mejores resultados
my $PathAlgorithm = $Path;

my @Dimension =("10");#, "30", "50", "100");
  

#foreach(@DI)
foreach(@Dimension)
{
	for( my $problem= 1; $problem <=30; $problem++) ##Realizar 35 ejecuciones con distintas semilla de cada instancia..
	{
		for(my $Sed = 1; $Sed <=51; $Sed++) ##Realizar 35 ejecuciones con distintas semilla de cada instancia..
		{
			print $fout "~$PathAlgorithm/de-chaconeitor_exe $Sed $problem $_\n";
		}
	}
	
}
