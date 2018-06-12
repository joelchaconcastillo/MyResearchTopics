#include <iostream>
#include <math.h>

using namespace std;

int main(){
	//Tchhebycheff
	//Asumiendo punto de referencia en 0: la función es max(w1*f1, w2*f2, w3*f3).
	//Asumiendo continuidad del frente, el minimo se producira con w1*f1 = w2*f2 = w3*f3
	//es decir, f2 = w1/w2 * f1, f3 = w1/w3*f1
	//Supongamos que todos los puntos cumplen f1*f1 + f2*f2 + f3*f3 = 1;
	//Entonces f1^2 + (w1/w2)^2 * f1^2 + (w1/w3)^2 *f1^2 = 1
	//es decir f1^2 * (1 + (w1/w2)^2 + (w1/w3)^2) = 1
	const double dif = 0.05;
	const double EPS = 1e-6;
	for (double w1_ = dif; w1_ <= 1 - dif + EPS; w1_+=dif){
		for (double w2_ = dif; w2_ <= 1 - dif - w1_ + EPS; w2_ +=dif){
			double w3_ = 1 - w1_ - w2_;

			double w1 = 1/w1_;
			double w2 = 1/w2_;
			double w3 = 1/w3_;

			double f1 = sqrt(1 / (1 + (w1/w2)*(w1/w2) + (w1/w3)*(w1/w3)));
			double f2 = w1/w2*f1;
			double f3 = w1/w3*f1;
			cout << f1 << " " << f2 << " " << f3 << endl;
		}
	}
}
