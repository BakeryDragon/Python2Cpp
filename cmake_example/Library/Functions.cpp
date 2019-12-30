#include <cmath>
#include <numeric>
#include "Functions.h"

using std::vector;

double add(double i, double j) {
	return i + j;
}

double square(double i) {
	return i * i;
}

double normalCDF(double value)
{
	return 0.5 * erfc(-value * sqrt(0.5));// cdf of normal distribution
}

double BS(double T) {
	double S0 = 42;// the stock price at time 0
	double K = 40;// the exercise
	double r = 0.1;// the risk free interest rate
	double sigma = 0.2;// the volatility
	double d1 = (log(S0 / K) + (r + sigma * sigma / 2) * T) /
		(sigma * sqrt(T));
	double d2 = d1 - sigma * sqrt(T);
	return S0 * normalCDF(d1) - K * exp(-r * T) * normalCDF(d2);
}

double innerproduct(vector<double> a, vector<double> b) {
	double* c = &a[0];
	double* d = &b[0];
	int n = sizeof(c);
	double result = std::inner_product(c, c + n, d, 0.0);
	return result;
}