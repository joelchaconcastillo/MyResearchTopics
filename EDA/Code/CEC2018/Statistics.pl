#!/usr/bin/perl
use strict;
use warnings;
use Getopt::Long;
use List::Util qw< min max sum >;
#use Statistics::Basic qw(:all);

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
    
#my @Dimension=("10", "30", "50", "100");
my @Dimension=("10");#, "30", "50", "100");

foreach( @Dimension)
{
   print "\nDimension $_\n\n";
   for( my $problem = 1; $problem <=30; $problem++)
   {
	my @Error;
      for( my $sed =1; $sed < 51; $sed++)
      {
	my $fin;
        open($fin,'<', $_."D/$problem/$sed.txt ");
      #  open($fin,'<', "o/$problem/$sed.txt ");

	my $data = <$fin>;	
#	$data = <$fin>;	
	chomp $data;
	push @Error, $data;
	
	close($fin);
	
      }
	print $problem." ".min(@Error)." ".max(@Error)." ".median(@Error)." ".mean(@Error)." ".std_dev(@Error)." \n";
   }
}
