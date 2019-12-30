#ifndef BLACK_SCHOLES_GENERATOR_H
#define BLACK_SCHOLES_GENERATOR_H

class BlackScholesGenerator {
public:
	BlackScholesGenerator(double stockPrice, double exercisePrice, double interestRate, double volatility, double timeLength);
	double operator()();

private:
	double stockPrice_;
	double exercisePrice_;
	double interestRate_;
	double volatility_;
	double timeLength_;
};

double normalCDF2(double);

#endif