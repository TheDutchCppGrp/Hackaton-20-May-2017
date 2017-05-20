// BS_hackaton.cpp : Defines the entry point for the console application.
#include <iostream>
#include <iomanip>
#include <cmath>

#define M_PI 3.14159265358979323846
//for gcc use:
//#define M_SQRT1_2 0.707106781186547524401

double norm_cdf(double value)
{
    return 0.5 * erfc(-value * M_SQRT1_2);
}

double d1(double S, double K, double r, double v, double T)
{
    return (log(S / K) + r*T) / (v*(pow(T, 0.5))) + 0.5*v*(pow(T, 0.5));
}

double d2(double S, double K, double r, double v, double T)
{
    return d1(S, K, r, v, T) - v*(pow(T, 0.5));
}

// vanilla european call price based on
// underlying S, strike K, risk-free rate r, volatility of
// underlying sigma and time to maturity T
double call_price(double S, double K, double r, double v, double T) 
{
    return S * norm_cdf(d1(S, K, r, v, T)) - K*exp(-r*T) * norm_cdf(d2(S, K, r, v, T));
}

// vanilla european put price based on
// underlying S, strike K, risk-free rate r, volatility of
// underlying sigma and time to maturity T
double put_price(double S, double K, double r, double v, double T) 
{
    return -S * norm_cdf(-d1(S, K, r, v, T)) + K*exp(-r*T) * norm_cdf(-d2(S, K, r, v, T));
}

int main(int argc, char **argv) 
{
    double S = 100.0; // underlying price
    double K = 500.0; // strike price
    double r = 0.02; // risk-free interest rate (2%)
    double v = 0.2; // volatility of the underlying (20%)
    double T = 1.0; // 1 year to expiry

    double call = call_price(S, K, r, v, T);
    double put = put_price(S, K, r, v, T);

    std::cout << std::fixed << std::setprecision(15) 
              << "call = " << call << ", "       //   0.000000000000005
              << "put  = " << put << std::endl;  // 390.099336653377634

    // Exercise 1: read the CSV file and execute above formulas (call_price, put_price)
    //  on each listed option price. Then leverage the Xeon Phi to do it in parallel.
    //

    // Exercise 2: try to find 'v' (volatility) by reversing the call_price function.
    //  Say you start with the value for 'call', S, K, r, T, but not v. And try to 
    //  solve what the input value 'v' should be to get the value for 'call'. 
    //
    // This means you need to invoke call_price() many times (trying different
    //  values for volatility) until you find a return value that matches the
    //  call value.

    return 0;
}
