%%Replacement Phase
N =100000
Min = -1;
Max = 1;
modas = 2
%%Initialization
Population = Min + rand(N, 2)*(Max-Min);
Di=1.0

x = Min:0.2:Max;
y = Min:0.2:Max;
x = linspace(Min,Max); 
y = linspace(Min,Max);

[X,Y] = meshgrid(x,y);
%Z = -X.^2 - Y.^2;
Z = sin(X*modas*pi) + cos(Y*modas*pi);
figure
s = contour(X,Y,Z,'ShowText','on');
%hold on
%Z = (1-X).^2 + 100*(Y-X.^2).^2;

%Evaluate points

Penalized = []
Reference_Point= []
Candidate = []
Survivors = []
FSurvivors = []
pause(5)
count = 0

%Ranks = zeros(500,2)
F = sin(Population(:,1)*modas*pi) + cos(Population(:,2)*modas*pi); %%Evaluate the population
%Sort the best individuals...
[Candidate, I] = sort(F); %%sort by fitness
Candidate = I;%Population(I,:)
% hold on
%s = scatter( Candidate(:,1), Candidate(:,2), 90, 'filled');
% hold on
while size(Candidate,1) >= 2  %%Select the best individuals inside the constraints
 %Select the best individual with max fitness
   Survivors = [Survivors; Candidate(1)];
  best = Candidate(1)
  Candidate = removerows(Candidate,'ind',1);
  [IndexDistances, Distances] = knnsearch(Population(Candidate,:), Population(best,:), 'k', size(Population(Candidate,:),1));
 
  Penalized = [Penalized ; Candidate(IndexDistances(Distances<=Di),:)];
  Candidate = removerows(Candidate,'ind',IndexDistances(Distances<=Di));
end
%Identify attraction bassis...
[IndexDistances, Distances] = knnsearch(Population(Penalized,:), Population(Survivors,:), 'k', size(Population(Penalized,:),1));

FPenalized = sin(Population(Penalized,1)*modas*pi) + cos(Population(Penalized,2)*modas*pi);
FSurvivors = sin(Population(Survivors,1)*modas*pi) + cos(Population(Survivors,2)*modas*pi);
 hold on
s = scatter(Population(Survivors,1), Population(Survivors,2), 90, 'filled');
 hold on
s = scatter(Population(Penalized,1), Population(Penalized,2), 90, 'filled');  