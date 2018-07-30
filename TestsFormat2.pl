#!/usr/bin/perl -w
use File::Basename;
use List::MoreUtils qw(uniq);
use Getopt::Long;
use List::Util qw(sum);
use List::Util qw( min max );
#use Statistics::Basic qw(:all);

my $PrefixFile="";
my $FilesMetric;
my $ProblemMax =0;
my @NickName;
#my $DirFiles;
GetOptions (
		"Label=s" => \$PrefixFile,
		"List=s" => \$FilesMetric,
	 	"Max=i" => \$ProblemMax
	 );

sub mean {
    return sum(@_)/@_;
};
sub median {
 my @vals = sort {$a <=> $b} @_;
    my $len = @vals;
    if($len%2) #odd?
    {
        return $vals[int($len/2)];
    }
    else #even
    {
        return ($vals[int($len/2)-1] + $vals[int($len/2)])/2;
    }
};
sub std_dev {
        my ($average, @values) = @_;

        my $count = scalar @values;
        my $std_dev_sum = 0;
        $std_dev_sum += ($_ - $average) ** 2 for @values;

        return $count ? sqrt($std_dev_sum / $count) : 0;
}
sub ImportData{

	open($FILE, '<', $_[0]);
	my @Data;
	while(my $data = <$FILE>)
	{
		chomp $data;
		if($ProblemMax eq 1)
		{
		   push(@Data, -$data);
		}
		else
		{
		   push(@Data, $data);
		}
	}
	return @Data;
}
sub EjecutarComandoR
{
	my $data = $_[0]; 
	my $Result = `echo " $data " | R --silent --no-save 2>/dev/null`;
	return $Result;
};
sub ShapiroWilk
{
	 $Command = "c(".join(',',@_).")";
                #$Command = EjecutarComandoR("shapiro.test($Command)[[2]]"); // 
                #$Command = EjecutarComandoR("shapiro.test($Command)$'p'"); // 
                $Command = EjecutarComandoR("shapiro.test($Command)");
#print "VALORRRR    ".$Command."\n";
        my @Value = split / /, $Command;
        #SÃ³lo obtener el ï¿½ltimo nï¿½mero pueden existir exponenciales
        ($Value[-2]) = $Value[-2] =~ m{(\d+\.\d+e*-*\d*)};
	if( length $Value[-2] )	
	{
	   return $Value[-2] + 0;
	}
	return 0;
};
sub KruskalWallis
{
	my ($A, $B) = @_;
	chomp(@$A);
	chomp(@$B);
	my $strMuestra1 = "c(".join(',',@$A).")";
	my $strMuestra2 = "c(".join(',',@$B).")";
	my $Comando = "x = kruskal.test( list($strMuestra1, $strMuestra2) );  ".  'x$\`p.value\`[1] ';
	#my $Comando = "x = kruskal.test( list($strMuestra1, $strMuestra2) )[3]  ";
	$Comando = EjecutarComandoR($Comando);
	my @Value = split / /, $Comando;
	($Value[-2]) = $Value[-2] =~ m{(\d+\.*\d*e*-*\d*)};
	if( length $Value[-2] )	
	{
	   return $Value[-2] + 0;
	}
	   return 0; ##No se pueden comparar las muestras por lo tanto se comparan directamente
};
sub Levene
{
	my ($A, $B) = @_;
	chomp(@$A);
	chomp(@$B);
	my $strMuestra1 = "c(".join(',',@$A).")";
	my $strMuestra2 = "c(".join(',',@$B).")";
	my $Size1 = scalar(@$A);
	my $Size2 = scalar(@$B);
	my $Comando2 = "library(car); x = leveneTest( c( $strMuestra1, $strMuestra2 ), as.factor(c(rep(1,$Size1), rep(2,$Size1) )) ); ". 'x$\`Pr(>F)\`[1] ';
	#my $Comando2 = "library(car); leveneTest( c( $strMuestra1, $strMuestra2 ), as.factor(c(rep(1,$Size1), rep(2,$Size1) )) )[1,3]; "; ##Alternativamente....
	$Comando2 = EjecutarComandoR($Comando2);
	my @Value = split / /, $Comando2;
	($Value[-2]) = $Value[-2] =~ m{(\d+\.*\d*e*-*\d*)};
	if( length $Value[-2] )	
	{
	   return $Value[-2] + 0;
	}
	return 0;
};
sub Anova
{
	my ($A, $B) = @_;
	chomp(@$A);
	chomp(@$B);
	my $strMuestra1 = "c(".join(',',@$A).")";
	my $strMuestra2 = "c(".join(',',@$B).")";
	my $Size1 = scalar(@$A);
	my $Size2 = scalar(@$B);
	my $Comando2 = "library(car); test =  aov( c( $strMuestra1, $strMuestra2 ) ~ as.factor(c(rep(1,$Size1), rep(2,$Size1) )) ) ; summary(test)[[1]][[1,".'\"Pr(>F)\"'."]] ";
	#my $Comando2 = "library(car); test =  aov( c( $strMuestra1, $strMuestra2 ) ~ as.factor(c(rep(1,$Size1), rep(2,$Size1) )) ) ; summary(test)[[1]][[1,5]] ";
	$Comando2 = EjecutarComandoR($Comando2);
	#print $Comando2;
	my @Value = split / /, $Comando2;
	($Value[-2]) = $Value[-2] =~ m{(\d+\.*\d*e*-*\d*)};
	return $Value[-2] + 0;
};
sub Welch
{
	my ($A, $B) = @_;
	chomp(@$A);
	chomp(@$B);
	my $strMuestra1 = "c(".join(',',@$A).")";
	my $strMuestra2 = "c(".join(',',@$B).")";
	my $Size1 = scalar(@$A);
	my $Size2 = scalar(@$B);
	#my $Comando2 = " t.test( $strMuestra1, $strMuestra2 , var.equal=FALSE )[3];  ";
	my $Comando2 = " x=t.test( $strMuestra1, $strMuestra2 , var.equal=FALSE );  ".  'x$\`p.value\`[1] ';
	$Comando2 = EjecutarComandoR($Comando2);
	my @Value = split / /, $Comando2;
	($Value[-2]) = $Value[-2] =~ m{(\d+\.*\d*e*-*\d*)};

	if( length $Value[-2] )	
	{
	   return $Value[-2] + 0;
	}
	return 0;
};
my %Groups;

my @ListAlgoritmos;
sub LoadFiles
{
	open($FILE, '<', $FilesMetric);
	my $Data=[];
	my $key;
	while(my $data = <$FILE>)
	{
		chomp $data;
	 	if($data =~ m/~/) 
		{
		   $Data=[];
		   my @tmp = split /~/, $data;
		   $key = $tmp[1];
		}	
		else{
		   my @Value = split / /, $data;
		   push(@$Data, $Value[0]);
		   $NickName{$Value[0]} = $Value[1];	
		   $Groups{$key} = $Data;
		}
	}
};
my $flag ;
sub SummaryTest
{
	my %Data;
	my %SummaryMax;
	my %SummaryMin;
	my %SummaryEq;
	my %SummaryMaxDiff;
	my %SummaryMinDiff;
	my %SummaryEqDiff;
	my %IdAlgorithm;
	#Obtener las muestras de cada algoritmo
	my $cont = 0;
	foreach $Algoritmo( @ListAlgoritmos )
	{
		$IdAlgorithm{$cont} = $Algoritmo;
		$cont++;
		#print $Algoritmo."\n";
		my @Result =  ImportData($Algoritmo);
		@{$Data{$Algoritmo}} = @Result;	
		$SummaryMax{ $Algoritmo } = 0; # Veces que se gana
		$SummaryMin{ $Algoritmo } = 0; # Veces que se pierde
		$SummaryMaxDiff{ $Algoritmo } = 0; # Veces que se gana
		$SummaryMinDiff{ $Algoritmo } = 0; # Veces que se pierde
		$SummaryEq{ $Algoritmo } = 0; # Empates
		$SummaryEqDiff{ $Algoritmo } = 0; # Empates
	}

	##Obtener el conjunto de muestras comparables
	#foreach $key( sort keys %Data)
	for(my $i = 0; $i < $cont; $i++)
	{
		my $key = $IdAlgorithm{$i};
		#print STDERR "Archivo: $key\n";
	#	foreach $key2( sort keys %Data)
		for(my $j=$i+1; $j < $cont; $j++)
		{
			my $key2 = $IdAlgorithm{$j};
			if($key eq $key2)
			{
				next;
			}
			#print KruskalWallis(\@{ $Data{$key} },  \@{ $Data{$key2} });
			#print Anova(\@{ $Data{$key} },  \@{ $Data{$key2} });#."  <----\n";
			#print Welch(\@{ $Data{$key} },  \@{ $Data{$key2} });
			#print ShapiroWilk( @{$Data{$key}} );
			#print Levene(\@{ $Data{$key} },  \@{ $Data{$key2} });
			#last;

			my $Diff = max(mean(@{ $Data{$key} }), mean(@{ $Data{$key2} })) - min(mean(@{ $Data{$key} }), mean(@{ $Data{$key2} }));
			#Tiene una Distribución normal
			if(ShapiroWilk( @{$Data{$key}} ) > 0.05 && ShapiroWilk( @{$Data{$key2}} ) > 0.05) ## Si p-value es menor a alfa se rechaza la hipótesis nula y los datos no provienen de una distributión normal
			{
				if(Levene(\@{ $Data{$key} },  \@{ $Data{$key2} }) > 0.05 ) #Si el p-value es menor al nivel de significancia entonces es poco probable que las diferencias obtenidas en las variaciones de la muestra se hayan producido sobre la base de un muestreo aleatorio de una población con varianzas iguales
				{
					if(Anova(\@{ $Data{$key} },  \@{ $Data{$key2} }) < 0.05 )
					{
						if(mean(@{ $Data{$key} }) < mean(@{ $Data{$key2} }))
						{
							$SummaryMax{ $key }=$SummaryMax{ $key }+1;
							$SummaryMin{ $key2 }=$SummaryMin{ $key2 }+1;
							$SummaryMaxDiff{ $key } += $Diff;
                                                        $SummaryMinDiff{ $key2 } += $Diff;
				
						}
						elsif(mean(@{ $Data{$key} }) > mean(@{ $Data{$key2} }))
							{
								$SummaryMax{ $key2 } = $SummaryMax{ $key2 }+1;
								$SummaryMin{ $key } = $SummaryMin{ $key }+1;
								$SummaryMaxDiff{ $key2 } += $Diff;
								$SummaryMinDiff{ $key } += $Diff;
							}
							else 
						   	{
							      $SummaryEq{$key} = $SummaryEq{$key}+1;
							      $SummaryEq{$key2} = $SummaryEq{$key2}+1;
							      $SummaryEqDiff{$key} += $Diff;
							      $SummaryEqDiff{$key2} += $Diff;
						   	}
					}
					else 
					   {
					      $SummaryEq{$key} =  $SummaryEq{$key}+1;
					      $SummaryEq{$key2} =  $SummaryEq{$key2}+1;
					      $SummaryEqDiff{$key} += $Diff;
					      $SummaryEqDiff{$key2} += $Diff;
					   }
				}else 
					{
						if(Welch(\@{ $Data{$key} },  \@{ $Data{$key2} })  < 0.05)
						{
							if(mean(@{ $Data{$key} }) < mean(@{ $Data{$key2} }))
							{
								$SummaryMax{ $key } =  $SummaryMax{ $key }+1;
								$SummaryMin{ $key2 } = $SummaryMin{ $key2 }+1;
								$SummaryMaxDiff{ $key } += $Diff;
                                                                $SummaryMinDiff{ $key2 } += $Diff;

					
							}
				 			elsif(mean(@{ $Data{$key} }) > mean(@{ $Data{$key2} }))
							{
								$SummaryMax{ $key2 } = $SummaryMax{ $key2 }+1;
								$SummaryMin{ $key } = $SummaryMin{ $key }+1;
								$SummaryMaxDiff{ $key2 } += $Diff;
								$SummaryMinDiff{ $key } += $Diff;
							}
							else 
						   	{
							      $SummaryEq{$key} = $SummaryEq{$key}+1;
							      $SummaryEq{$key2} = $SummaryEq{$key2}+1;
							      $SummaryEqDiff{$key} += $Diff;
							      $SummaryEqDiff{$key2} += $Diff;
						   	}
						
						}
						else 
						   {
						      $SummaryEq{$key}  =  $SummaryEq{$key}+1;
						      $SummaryEq{$key2}  = $SummaryEq{$key2}+1;
						      $SummaryEqDiff{$key}  +=  $Diff;
						      $SummaryEqDiff{$key2}  += $Diff;
						   }
				
					}
			}
			else
			{
				if(KruskalWallis(\@{ $Data{$key} },  \@{ $Data{$key2} }) < 0.05 )
				{
					if(mean(@{ $Data{$key} }) < mean(@{ $Data{$key2} }))
					{
						$SummaryMax{ $key } = $SummaryMax{ $key }+1;
						$SummaryMin{ $key2 } = $SummaryMin{ $key2 }+1;
						$SummaryMaxDiff{ $key } += $Diff;
						$SummaryMinDiff{ $key2 } += $Diff;
			
					}
				 	elsif(mean(@{ $Data{$key} }) > mean(@{ $Data{$key2} }))
					{
						$SummaryMax{ $key2 } =  $SummaryMax{ $key2 }+1;
						$SummaryMin{ $key } = $SummaryMin{ $key }+1;
						$SummaryMaxDiff{ $key2 } += $Diff;
						$SummaryMinDiff{ $key } += $Diff;
					}
					else 
				   	{
					      $SummaryEq{$key} = $SummaryEq{$key}+1;
					      $SummaryEq{$key2} = $SummaryEq{$key2}+1;
					      $SummaryEqDiff{$key} += $Diff;
					      $SummaryEqDiff{$key2} += $Diff;
				   	}

				}
				else 
				   {
					      $SummaryEq{$key} = $SummaryEq{$key}+1;
					      $SummaryEq{$key2} = $SummaryEq{$key2}+1;
					      $SummaryEqDiff{$key} += $Diff;
					      $SummaryEqDiff{$key2} += $Diff;
				   }
			}
		}
		#last;
		
}

	if($flag == 0)
	{
		print "Orden... $flag";
		foreach $key(sort keys %SummaryMax)
		{
			print $key."\n";
		}
	        $flag = 1;
	}
	##Se divide entre dos porque la comparación se realiza con cardinaidad de todos a todos ( sin comparar el mismo...)
	foreach $key(sort keys %SummaryMax)
	{
#		print $NickName{$key}."\n";
		if( $ProblemMax eq 1)
		{	
		 print $SummaryMax{$key}."\t".($SummaryMin{$key})."\t".($SummaryEq{$key})."\t";#.-1.0*max(@{ $Data{$key} })."\t".-1.0*min(@{ $Data{$key} })."\t".-1.0*mean(@{ $Data{$key} })."\t".std_dev( mean(@{ $Data{$key} }), @{ $Data{$key} })."\n";
		 #print "$key ".$SummaryMax{$key}."\t".($SummaryMin{$key})."\t".($SummaryEq{$key})."\t";#.-1.0*max(@{ $Data{$key} })."\t".-1.0*min(@{ $Data{$key} })."\t".-1.0*mean(@{ $Data{$key} })."\t".std_dev( mean(@{ $Data{$key} }), @{ $Data{$key} })."\n";
		}
		else
		{
			print $SummaryMax{$key}."\t".($SummaryMin{$key})."\t".($SummaryEq{$key})."\t";#.min(@{ $Data{$key} })."\t".max(@{ $Data{$key} })."\t".mean(@{ $Data{$key} })."\t".std_dev( mean(@{ $Data{$key} }), @{ $Data{$key} })."\n";
			#print "$key ".$SummaryMax{$key}."\t".($SummaryMin{$key})."\t".($SummaryEq{$key})."\t";#.min(@{ $Data{$key} })."\t".max(@{ $Data{$key} })."\t".mean(@{ $Data{$key} })."\t".std_dev( mean(@{ $Data{$key} }), @{ $Data{$key} })."\n";
		}
	}
	print "\n";
};
sub SummaryTestStatisticals
{
	my %Data;
	my %SummaryMax;
	my %SummaryMin;
	my %SummaryEq;
	my %SummaryMaxDiff;
	my %SummaryMinDiff;
	my %SummaryEqDiff;
	my %IdAlgorithm;
	#Obtener las muestras de cada algoritmo
	my $cont = 0;
	foreach $Algoritmo( @ListAlgoritmos )
	{
		$IdAlgorithm{$cont} = $Algoritmo;
		$cont++;
		#print $Algoritmo."\n";
		my @Result =  ImportData($Algoritmo);
		@{$Data{$Algoritmo}} = @Result;	
		$SummaryMax{ $Algoritmo } = 0; # Veces que se gana
		$SummaryMin{ $Algoritmo } = 0; # Veces que se pierde
		$SummaryMaxDiff{ $Algoritmo } = 0; # Veces que se gana
		$SummaryMinDiff{ $Algoritmo } = 0; # Veces que se pierde
		$SummaryEq{ $Algoritmo } = 0; # Empates
		$SummaryEqDiff{ $Algoritmo } = 0; # Empates
	}

	##Obtener el conjunto de muestras comparables
	#foreach $key( sort keys %Data)
	for(my $i = 0; $i < $cont; $i++)
	{
		my $key = $IdAlgorithm{$i};
		#print STDERR "Archivo: $key\n";
	#	foreach $key2( sort keys %Data)
		for(my $j=$i+1; $j < $cont; $j++)
		{
			my $key2 = $IdAlgorithm{$j};
			if($key eq $key2)
			{
				next;
			}
			#print KruskalWallis(\@{ $Data{$key} },  \@{ $Data{$key2} });
			#print Anova(\@{ $Data{$key} },  \@{ $Data{$key2} });#."  <----\n";
			#print Welch(\@{ $Data{$key} },  \@{ $Data{$key2} });
			#print ShapiroWilk( @{$Data{$key}} );
			#print Levene(\@{ $Data{$key} },  \@{ $Data{$key2} });
			#last;

			my $Diff = max(mean(@{ $Data{$key} }), mean(@{ $Data{$key2} })) - min(mean(@{ $Data{$key} }), mean(@{ $Data{$key2} }));
			#Tiene una Distribución normal
			if(ShapiroWilk( @{$Data{$key}} ) > 0.05 && ShapiroWilk( @{$Data{$key2}} ) > 0.05) ##Es necesario comparar las dos muestras os olo una?...
			{
				if(Levene(\@{ $Data{$key} },  \@{ $Data{$key2} }) > 0.05 )
				{
					if(Anova(\@{ $Data{$key} },  \@{ $Data{$key2} }) < 0.05 )
					{
						if(mean(@{ $Data{$key} }) < mean(@{ $Data{$key2} }))
						{
							$SummaryMax{ $key }=$SummaryMax{ $key }+1;
							$SummaryMin{ $key2 }=$SummaryMin{ $key2 }+1;
							$SummaryMaxDiff{ $key } += $Diff;
                                                        $SummaryMinDiff{ $key2 } += $Diff;
				
						}
						else
						{
							$SummaryMax{ $key2 }=$SummaryMax{ $key2 }+1;
							$SummaryMin{ $key }=$SummaryMin{ $key }+1;
							$SummaryMaxDiff{ $key2 } += $Diff;
							$SummaryMinDiff{ $key } += $Diff;
						}
						
					}
					else 
					   {
					      $SummaryEq{$key} =  $SummaryEq{$key}+1;
					      $SummaryEq{$key2} =  $SummaryEq{$key2}+1;
					      $SummaryEqDiff{$key} += $Diff;
					      $SummaryEqDiff{$key2} += $Diff;
					   }
				}else 
					{
						if(Welch(\@{ $Data{$key} },  \@{ $Data{$key2} })  < 0.05)
						{
							if(mean(@{ $Data{$key} }) < mean(@{ $Data{$key2} }))
							{
								$SummaryMax{ $key } =  $SummaryMax{ $key }+1;
								$SummaryMin{ $key2 } = $SummaryMin{ $key2 }+1;
								$SummaryMaxDiff{ $key } += $Diff;
                                                                $SummaryMinDiff{ $key2 } += $Diff;

					
							}
							else
							{
								$SummaryMax{ $key2 } = $SummaryMax{ $key2 }+1;
								$SummaryMin{ $key } = $SummaryMin{ $key }+1;
								$SummaryMaxDiff{ $key2 } += $Diff;
								$SummaryMinDiff{ $key } += $Diff;
							}
						
						}
						else 
						   {
						      $SummaryEq{$key}  =  $SummaryEq{$key}+1;
						      $SummaryEq{$key2}  = $SummaryEq{$key2}+1;
						      $SummaryEqDiff{$key}  +=  $Diff;
						      $SummaryEqDiff{$key2}  += $Diff;
						   }
				
					}
			}
			else
			{
				#print KruskalWallis(\@{ $Data{$key} },  \@{ $Data{$key2} })."\n";
				if(KruskalWallis(\@{ $Data{$key} },  \@{ $Data{$key2} }) < 0.05 )
				{
					if(mean(@{ $Data{$key} }) < mean(@{ $Data{$key2} }))
					{
						$SummaryMax{ $key } = $SummaryMax{ $key }+1;
						$SummaryMin{ $key2 } = $SummaryMin{ $key2 }+1;
						$SummaryMaxDiff{ $key } += $Diff;
						$SummaryMinDiff{ $key2 } += $Diff;
			
					}
					else
					{
						$SummaryMax{ $key2 } =  $SummaryMax{ $key2 }+1;
						$SummaryMin{ $key } = $SummaryMin{ $key }+1;
						$SummaryMaxDiff{ $key2 } += $Diff;
						$SummaryMinDiff{ $key } += $Diff;
					}

				}
				else 
				   {
					      $SummaryEq{$key} = $SummaryEq{$key}+1;
					      $SummaryEq{$key2} = $SummaryEq{$key2}+1;
					      $SummaryEqDiff{$key} += $Diff;
					      $SummaryEqDiff{$key2} += $Diff;
				   }
			}
		}
		#last;
		
        }









	if($flag eq 0)
	{
		print "Orden... ";
		foreach $key(sort keys %SummaryMax)
		{
			print $key."\n";
		}
	        $flag = 1;
	}

        foreach $key(sort keys %SummaryMax)
        {

        #       print $NickName{$key}."\t";
                if( $ProblemMax eq 1)
                {
                   print -1.0*max(@{ $Data{$key} })."\t".-1.0*min(@{ $Data{$key} })."\t".-1.0*mean(@{ $Data{$key} })."\tN\t";#.std_dev( mean(@{ $Data{$key} }), @{ $Data{$key} })."\t";
                }
                else
                {
                        print min(@{ $Data{$key} })."\t".max(@{ $Data{$key} })."\t".mean(@{ $Data{$key} })."\tN\t";#.std_dev( mean(@{ $Data{$key} }), @{ $Data{$key} })."\t";
                }
        }

	print "\n";
};


sub SummaryTestDiff
{
	my %Data;
	my %SummaryMax;
	my %SummaryMin;
	my %SummaryEq;
	my %SummaryMaxDiff;
	my %SummaryMinDiff;
	my %SummaryEqDiff;
	my %IdAlgorithm;
	#Obtener las muestras de cada algoritmo
	my $cont = 0;
	foreach $Algoritmo( @ListAlgoritmos )
	{
		$IdAlgorithm{$cont} = $Algoritmo;
		$cont++;
		#print $Algoritmo."\n";
		my @Result =  ImportData($Algoritmo);
		@{$Data{$Algoritmo}} = @Result;	
		$SummaryMax{ $Algoritmo } = 0; # Veces que se gana
		$SummaryMin{ $Algoritmo } = 0; # Veces que se pierde
		$SummaryMaxDiff{ $Algoritmo } = 0; # Veces que se gana
		$SummaryMinDiff{ $Algoritmo } = 0; # Veces que se pierde
		$SummaryEq{ $Algoritmo } = 0; # Empates
		$SummaryEqDiff{ $Algoritmo } = 0; # Empates
	}

	##Obtener el conjunto de muestras comparables
	#foreach $key( sort keys %Data)
	for(my $i = 0; $i < $cont; $i++)
	{
		my $key = $IdAlgorithm{$i};
		#print STDERR "Archivo: $key\n";
	#	foreach $key2( sort keys %Data)
		for(my $j=$i+1; $j < $cont; $j++)
		{
			my $key2 = $IdAlgorithm{$j};
			if($key eq $key2)
			{
				next;
			}
			#print KruskalWallis(\@{ $Data{$key} },  \@{ $Data{$key2} });
			#print Anova(\@{ $Data{$key} },  \@{ $Data{$key2} });#."  <----\n";
			#print Welch(\@{ $Data{$key} },  \@{ $Data{$key2} });
			#print ShapiroWilk( @{$Data{$key}} );
			#print Levene(\@{ $Data{$key} },  \@{ $Data{$key2} });
			#last;

			my $Diff = max(mean(@{ $Data{$key} }), mean(@{ $Data{$key2} })) - min(mean(@{ $Data{$key} }), mean(@{ $Data{$key2} }));
			
	

			#Tiene una Distribución normal
			if(ShapiroWilk( @{$Data{$key}} ) > 0.05 && ShapiroWilk( @{$Data{$key2}} ) > 0.05) ##Es necesario comparar las dos muestras os olo una?...
			{
				if(Levene(\@{ $Data{$key} },  \@{ $Data{$key2} }) > 0.05 )
				{
					if(Anova(\@{ $Data{$key} },  \@{ $Data{$key2} }) < 0.05 )
					{
						if(mean(@{ $Data{$key} }) < mean(@{ $Data{$key2} }))
						{
							$SummaryMax{ $key }=$SummaryMax{ $key }+1;
							$SummaryMin{ $key2 }=$SummaryMin{ $key2 }+1;
							$SummaryMaxDiff{ $key } += $Diff;
                                                        $SummaryMinDiff{ $key2 } += $Diff;
				
						}
						else
						{
							$SummaryMax{ $key2 }=$SummaryMax{ $key2 }+1;
							$SummaryMin{ $key }=$SummaryMin{ $key }+1;
							$SummaryMaxDiff{ $key2 } += $Diff;
							$SummaryMinDiff{ $key } += $Diff;
						}
						
					}
					else 
					   {
					      $SummaryEq{$key} =  $SummaryEq{$key}+1;
					      $SummaryEq{$key2} =  $SummaryEq{$key2}+1;
					      $SummaryEqDiff{$key} += $Diff;
					      $SummaryEqDiff{$key2} += $Diff;
					   }
				}else 
					{
						if(Welch(\@{ $Data{$key} },  \@{ $Data{$key2} })  < 0.05)
						{
							if(mean(@{ $Data{$key} }) < mean(@{ $Data{$key2} }))
							{
								$SummaryMax{ $key } =  $SummaryMax{ $key }+1;
								$SummaryMin{ $key2 } = $SummaryMin{ $key2 }+1;
								$SummaryMaxDiff{ $key } += $Diff;
                                                                $SummaryMinDiff{ $key2 } += $Diff;

					
							}
							else
							{
								$SummaryMax{ $key2 } = $SummaryMax{ $key2 }+1;
								$SummaryMin{ $key } = $SummaryMin{ $key }+1;
								$SummaryMaxDiff{ $key2 } += $Diff;
								$SummaryMinDiff{ $key } += $Diff;
							}
						
						}
						else 
						   {
						      $SummaryEq{$key}  =  $SummaryEq{$key}+1;
						      $SummaryEq{$key2}  = $SummaryEq{$key2}+1;
						      $SummaryEqDiff{$key}  +=  $Diff;
						      $SummaryEqDiff{$key2}  += $Diff;
						   }
				
					}
			}
			else
			{
				#print KruskalWallis(\@{ $Data{$key} },  \@{ $Data{$key2} })."\n";
				if(KruskalWallis(\@{ $Data{$key} },  \@{ $Data{$key2} }) < 0.05 )
				{
					if(mean(@{ $Data{$key} }) < mean(@{ $Data{$key2} }))
					{
						$SummaryMax{ $key } = $SummaryMax{ $key }+1;
						$SummaryMin{ $key2 } = $SummaryMin{ $key2 }+1;
						$SummaryMaxDiff{ $key } += $Diff;
						$SummaryMinDiff{ $key2 } += $Diff;
			
					}
					else
					{
						$SummaryMax{ $key2 } =  $SummaryMax{ $key2 }+1;
						$SummaryMin{ $key } = $SummaryMin{ $key }+1;
						$SummaryMaxDiff{ $key2 } += $Diff;
						$SummaryMinDiff{ $key } += $Diff;
					}

				}
				else 
				   {
					      $SummaryEq{$key} = $SummaryEq{$key}+1;
					      $SummaryEq{$key2} = $SummaryEq{$key2}+1;
					      $SummaryEqDiff{$key} += $Diff;
					      $SummaryEqDiff{$key2} += $Diff;
				   }
			}
		}
		#last;
		
        }









	if($flag eq 0)
	{
		print "Orden... ";
		foreach $key(sort keys %SummaryMaxDiff)
		{
			print $key."\n";
		}
	        $flag = 1;
	}


 	foreach $key(sort keys %SummaryMaxDiff)
        {
                #print $NickName{$key}."\t";
                if( $ProblemMax eq 1)
                {
                 print $SummaryMaxDiff{$key}."\t".($SummaryMinDiff{$key})."\t".($SummaryEqDiff{$key})."\t";#."\t".-1.0*max(@{ $Data{$key} })."\t".-1.0*min(@{ $Data{$key} })."\t".-1.0*mean(@{ $Data{$key} })."\t".std_dev( mean(@{ $Data{$key} }), @{ $Data{$key} })."\n";
                }
                else
                {
                        print $SummaryMaxDiff{$key}."\t".($SummaryMinDiff{$key})."\t".($SummaryEqDiff{$key})."\t";#."\t".min(@{ $Data{$key} })."\t".max(@{ $Data{$key} })."\t".mean(@{ $Data{$key} })."\t".std_dev( mean(@{ $Data{$key} }), @{ $Data{$key} })."\n";
                }
        }

	print "\n";
};

##if(  length($PrefixFile) > 0)
#{
# #  @ListAlgoritmos = glob($PrefixFile);
#}
#elsif( length($FilesMetric) > 0 )
#{
   LoadFiles();
#}
#
$flag=0;
foreach $key( sort keys %Groups)
{
   @ListAlgoritmos = @{$Groups{$key}};
   SummaryTest();
#	$flag=0;
#   SummaryTestStatisticals();
#	$flag=0;
#   SummaryTestDiff();
}
$flag=0;
foreach $key( sort keys %Groups)
{
   #print $key."\n";
   @ListAlgoritmos = @{$Groups{$key}};
   SummaryTestStatisticals();
}
#$flag=0;
#foreach $key( sort keys %Groups)
#{
#   #print $key."\n";
#   @ListAlgoritmos = @{$Groups{$key}};
#   SummaryTestDiff();
#}
$flag=0;
foreach $key( sort keys %Groups)
{
   print $key."\n";
}
