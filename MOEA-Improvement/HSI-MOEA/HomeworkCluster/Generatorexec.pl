#Con este script se genera la lista de ejecuciones....
#!/usr/bin/perl
use strict;
use warnings;
use Getopt::Long;
my $file = "ExecutionFileDiversity";
my $fout;
open($fout, '>' ,$file);
my $Path =  `cd ..; pwd`;#"/home/joel.chacon/Current/MyResearchTopics/MOEA-D-Diversity/MOEAD-DE/vsd-moead-opt";
chomp $Path;

####Realizar la búsqueda del parámetro D inicial que proporcione mejores resultados
my $PathAlgorithm = $Path;

my @Instance = ("DTLZ1", "DTLZ2", "DTLZ3", "DTLZ4", "DTLZ5", "DTLZ6", "DTLZ7");
foreach(@Instance)
{
	my $nvar;
	
	for(my $nobj = 2; $nobj <=3; $nobj++)
	{

   	   if($_ eq "DTLZ")
	   {
	      $nvar=5+$nobj-1;
	   }
	   elsif($_ eq "DTLZ7")
	   {
	      $nvar=20+$nobj-1;
	   }
	   else
	   {
	      $nvar=10+$nobj-1;
	   }
	   my $pops;
	   my $max_nfes;
	   if($nobj == 2 || $nobj==3 || $nobj==4 || $nobj==8)
	   {
		$pops = 120;
		$max_nfes = 49920;
	   }
	   elsif($nobj == 5 || $nobj==6)
	   {
		$pops = 126;
		$max_nfes = 49896;
	   }
	   elsif($nobj == 7)
	   {
		$pops = 84;
		$max_nfes = 49980;
	   }
	
	   for(my $Sed = 1; $Sed <=35; $Sed++) ##Realizar 35 ejecuciones con distintas semilla de cada instancia..
	   {
	   	print $fout "~$PathAlgorithm/Ejecutable $_ $Sed $nobj $pops $max_nfes $nvar\n";
	   }
	}
}
	


#@Instance = ("WFG1", "WFG2", "WFG3", "WFG4", "WFG5", "WFG6", "WFG7", "WFG8", "WFG9");
#foreach(@Instance)
#{
#	my $nvar;
#	
#	for(my $nobj = 2; $nobj <=3; $nobj++)
#	{
#	   my $k = 2*($nobj-1);
#	   my $l = 24-$k;
#	   $nvar=$l+$k;
#	   my $pops;
#	   my $max_nfes;
#	   if($nobj == 2 || $nobj==3 || $nobj==4 || $nobj==8)
#	   {
#		$pops = 120;
#		$max_nfes = 49920;
#	   }
#	   elsif($nobj == 5 || $nobj==6)
#	   {
#		$pops = 126;
#		$max_nfes = 49896;
#	   }
#	   elsif($nobj == 7)
#	   {
#		$pops = 84;
#		$max_nfes = 49980;
#	   }
#	
#	   for(my $Sed = 1; $Sed <=35; $Sed++) ##Realizar 35 ejecuciones con distintas semilla de cada instancia..
#	   {
#	   	print $fout "~$PathAlgorithm/Ejecutable $_ $Sed $nobj $pops $max_nfes $l $k\n";
#	   }
#	}
#}
