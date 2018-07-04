from scipy import stats
from numpy import *
file1 = loadtxt("a.txt") #open("a.txt", "r") 
file2 = loadtxt("b.txt") #open("b.txt", "r") 


###Primero prueba de normalidad con shapiro wilk, es decir si pvalue menor 0.05 se rechaza la hipotesis de que los datos tienen una distribucion formal
print 

if stats.shapiro(file1)[1] > 0.05 and stats.shapiro(file2)[1] > 0.05 :
#levene...The Levene test tests the null hypothesis that all input samples are from populations with equal variances
#The test rejects the hypothesis of normality when the p-value is less than or equal to 0.05
  if stats.levene(file1, file2)[1] > 0.05 :
  #no equal variances.. 
#The null hypothesis for an ANOVA is that there is no significant difference among the groups
#The one-way ANOVA tests the null hypothesis that two or more groups have the same population mean. #if the p-value associated with the F is smaller than .05, then the null hypothesis is rejected and the alternative hypothesis is supported
     if stats.anova(file1, file2)[1] < 0.05:
       print('no equal')
     else:
       print('equal')
  else:
#The null hypothesis for the test is that the means are equal.
#If we observe a large p-value, for example larger than 0.05 or 0.1, then we cannot reject the null hypothesis of identical average scores
# If the p-value is smaller than the threshold, e.g. 1%, 5% or 10%, then we reject the null hypothesis of equal averages.

#        if stats.welch(file1, file2)[1] < 0.05:
        if stats.ttest_ind(file1, file2, equal_var = False)[1] < 0.05:
           print('no tie, so compare')
        else:
           print('tie')
else:
## The Kruskal-Wallis H-test tests the null hypothesis that the population median of all of the groups are equal. It is a non-parametric version of ANOVA
##If p-value is less than 0.05 then we reject the null hypothesis
   if stats.kruskal(file1, file2)[1] > 0.05:
     print('tie')
   else:
     print('no tie, so check the means...')


print stats.shapiro(file1)[1]
print stats.shapiro(file2)[1]
print stats.kruskal(file1, file2)
