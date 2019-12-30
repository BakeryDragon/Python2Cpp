import subprocess
subprocess.check_call(['pip', 'install', './cmake_example'], shell=True)

import cmake_example as m

a = m.add(3.0, 1.3232)
print("the sum of two double is " + str(a))

b = m.square(4)
print("the square of one double is " + str(b))

maturity = 0.5
BS = m.BS(maturity)
print("the option price calculated by BS formula is " + str(BS))

initEquityPrice = 10
numTimeSteps = 6
timetoExpiry = 6
drift = 0.1
volatility = 0.1
EPG = m.EquityPriceGenerator(initEquityPrice, numTimeSteps, timetoExpiry, drift, volatility)
print("EquityPriceGenerator initiated")
print(EPG)
price1 = EPG.operator(1)
print("the sequence of prices calculated by Monte Carlo formula is " + str(price1))

strikePrice = 42
exercisePrice = 40
interestRate = 0.1
volatility = 0.2
BSG = m.BlackScholesGenerator(strikePrice, exercisePrice, interestRate, volatility, maturity)
print("BlackScholesGenerator initiated")
print(BSG)
price2 = BSG.operator()
print("the option price calculated by BS formula is " + str(price2))

vector1 = [2, 0.1, 1.734]
vector2 = [2.43, 4.32, 9]
innerproduct = m.innerproduct(vector1, vector2)
print("the inner product of two vectors are " + str(innerproduct))

strike = 102
spot = 100
riskFreeRate = 0.25
volatility = 0.06
quantity = 7000
tau = 1.0
numTimeSteps = 12
numScenarios = 10000
initSeed = 1
MCP = m.MCEuroOptPricer(strike, spot, riskFreeRate, volatility, tau, m.CALL, \
numTimeSteps, numScenarios, False, initSeed, quantity)
print("the price given by the Monte Carlo Pricer is " + str(MCP.operator()))
print("the time used is " + str(MCP.time()))