#include <bits/stdc++.h>

using namespace std;

const int DIM = 3;
struct Point {
	double x[DIM];
};

double getDistanceIGD(Point &p, Point &ref){
	double d = 0;
	for (int i = 0; i < DIM; i++){
		if (p.x[i] < ref.x[i]){
			d += (p.x[i] - ref.x[i]) * (p.x[i] - ref.x[i]);
		}
	}
	return sqrt(d);
}

double getDistance(Point &p, Point &ref){
	double d = 0;
	for (int i = 0; i < DIM; i++){
		d += ((p.x[i] - ref.x[i]) * (p.x[i] - ref.x[i]));
	}
	return sqrt(d);
}

int main(){
	vector<Point> allPoints;
	vector<Point> points;
	for (int i = 0; i < 100000; i++){
		Point p;
		for (int j = 0; j < DIM; j++){
			p.x[j] = ((double)(random())/RAND_MAX);
		}
		double mod = 0;
		for (int j = 0; j < DIM; j++){
			mod += p.x[j] * p.x[j];
		}
		mod = sqrt(mod);
		for (int j = 0; j < DIM; j++){
			p.x[j] /= mod;
			p.x[j] *= (j+1.0)*10.0;
		}
		points.push_back(p);
		allPoints.push_back(p);
	}
	vector<Point> selected;
	for (int i = 0; i < DIM; i++){
		double best = DBL_MAX;
		int bestIndex = -1;
		for (int j = 0; j < points.size(); j++){
			if (points[j].x[i] < best){
				bestIndex = j;
				best = points[j].x[i];
			}
		}
		selected.push_back(points[bestIndex]);
		points[bestIndex] = points.back();
		points.pop_back();
	}
	for (int i = 0; i < 200; i++){
		cerr << "Va por " << i << endl;
		double largestDistance = 0;
		int bestIndex = -1;
		for (int j = 0; j < points.size(); j++){
			double closestDistance = DBL_MAX;
			for (int k = 0; k < selected.size(); k++){
				double d = getDistance(points[j], selected[k]);
				closestDistance = min(closestDistance, d);
			}
			if (closestDistance > largestDistance){
				largestDistance = closestDistance;
				bestIndex = j;
			}
		}
		selected.push_back(points[bestIndex]);
		points[bestIndex] = points.back();
		points.pop_back();
	}
	for (int i = 0; i < selected.size(); i++){
		for (int j = 0; j < DIM; j++){
			cout << selected[i].x[j] << " ";
		}
		cout << endl;
	}

	//Calculamos el IGD+
	double totalDistance = 0;
	for (int i = 0; i < allPoints.size(); i++){
		double distance = DBL_MAX;
		for (int j = 0; j < selected.size(); j++){
			distance = min(distance, getDistanceIGD(allPoints[i], selected[j]));
		}
		totalDistance += distance;
	}
	cerr << "IGD: " << totalDistance / allPoints.size() << endl;
}
