#include <atomic>
#include <iostream>
#include <random>
#include <chrono>
#include "tbb/tbb.h"
#include "tbb/parallel_reduce.h"
#include "tbb/blocked_range.h"

size_t circleCount { 0 };
size_t numberOfPoints { 300000000ull }; // ull is unsigned long long

// For a visualisation of this estimation at work, see:
// https://academo.org/demos/estimating-pi-monte-carlo/
bool calculatePi(double random_number, double random_number2) {
    auto x = (2.0 * random_number) - 1;
    auto y = (2.0 * random_number2) - 1;
    return ( ((x * x) + ( y * y)) <= 1.0);
}

int main() {

    std::cout << "Start calculating pi." << std::endl;

    auto startTime = std::chrono::steady_clock::now();
    
    circleCount = tbb::parallel_reduce(
        // reduce on a range of 0.. numberOfPoints with stepsize 1
        tbb::blocked_range<size_t>(0ull, numberOfPoints, 1ull),
        // initial value is zero
        0ull,
        // lambda that does calculation for part of the range
        [](const tbb::blocked_range<size_t>& r, size_t value) -> size_t {
            // rand() uses hidden state and is not thread safe
            // we need to have a random number generator per thread
            std::uniform_real_distribution<double> unif(0.0, 1.0);
            std::default_random_engine re;

            for (size_t i=r.begin(); i<r.end(); i++) {
                double random_number = unif(re);
                double random_number2 = unif(re);
                // do the estimation test and increment local per thread counter
                if (calculatePi(random_number, random_number2))
                    value++;
            }
            return value;
        },
        // accumulate all the local (per thread) counters with std::plus to get
        // the absolute total
        std::plus<size_t>()
    );

    auto endTime = std::chrono::steady_clock::now();
    auto diff = std::chrono::duration_cast<std::chrono::seconds>(endTime-startTime).count();
    std::cout.precision(20);
    std::cout << "Pi " << std::fixed << (4.0 * (double)circleCount/(double)numberOfPoints)
              << " took " <<  diff << " seconds." << std::endl;
    return 0;
}
