#include "BlackScholesGenerator.h"
#include <cmath>

double normalCDF2(double value)
{
	return 0.5 * erfc(-value * sqrt(0.5));// cdf of normal distribution
}

BlackScholesGenerator::BlackScholesGenerator(double stockPrice, double exercisePrice, double interestRate, double volatility, double timeLength) :
	stockPrice_(stockPrice), exercisePrice_(exercisePrice), interestRate_(interestRate), volatility_(volatility), timeLength_(timeLength) {}

double BlackScholesGenerator::operator()()
{
	double d1 = (log(stockPrice_ / exercisePrice_) + (interestRate_ + volatility_ * volatility_ / 2) * timeLength_) /
		(volatility_ * sqrt(timeLength_));
	double d2 = d1 - volatility_ * sqrt(timeLength_);
	return stockPrice_ * normalCDF2(d1) - exercisePrice_ * exp(-interestRate_ * timeLength_) * normalCDF2(d2);
}