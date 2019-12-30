#include "EquityPriceGenerator.h"
#include <random>
#include <algorithm>	
#include <ctime>
#include <cmath>
#include <numeric>
#include <vector>
#include <future>
#include <limits>
using std::vector;
using std::mt19937_64;
using std::normal_distribution;
using std::exp;

EquityPriceGenerator::EquityPriceGenerator(double initEquityPrice, unsigned numTimeSteps, double timeToExpiry, double drift, double volatility) :
	initEquityPrice_(initEquityPrice), numTimeSteps_(numTimeSteps), drift_(drift), volatility_(volatility),
	dt_(timeToExpiry / numTimeSteps) {}

vector<double> EquityPriceGenerator::operator()(int seed) const
{
	vector<double> v;

	mt19937_64 mtEngine(seed);
	normal_distribution<> nd;

	auto newPrice = [this](double previousEquityPrice, double norm)
	{
		double price = 0.0;

		double expArg1 = (drift_ - ((volatility_ * volatility_) / 2.0)) * dt_;
		double expArg2 = volatility_ * norm * sqrt(dt_);
		price = previousEquityPrice * exp(expArg1 + expArg2);

		return price;
	};

	v.push_back(initEquityPrice_);				// put initial equity price into the 1st position in the vector
	double equityPrice = initEquityPrice_;

	for (int i = 1; i <= numTimeSteps_; ++i)	// i <= numTimeSteps_ since we need a price at the end of the
	{											// final time step.
		equityPrice = newPrice(equityPrice, nd(mtEngine));	// norm = nd(mtEngine)
		v.push_back(equityPrice);
	}

	return v;

}