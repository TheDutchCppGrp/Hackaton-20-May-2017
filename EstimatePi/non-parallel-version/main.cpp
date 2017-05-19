#include <iostream>
#include <chrono>

unsigned long long int circleCount { 0 };
unsigned long long numberOfPoints { 300000000ull };
unsigned long long int numberOfPoints { 150000000 };

int main() {

    std::cout << "Start calculating pi." << std::endl;

    srand(std::time(NULL));

    auto startTime = std::chrono::steady_clock::now();
    for (int i = 0; i < numberOfPoints; ++i) {
        auto r = (double)rand() / RAND_MAX;
        auto x = (2.0 * r) - 1;
        r = (double)rand() / RAND_MAX;
        auto y = (2.0 * r) - 1;
        // For a visualisation of this estimation at work, see:
        // https://academo.org/demos/estimating-pi-monte-carlo/
        if ( ((x * x) + ( y * y)) <= 1.0) {
            circleCount++;
        }
    }
    auto endTime = std::chrono::steady_clock::now();
    auto diff = std::chrono::duration_cast<std::chrono::seconds>(endTime-startTime).count();
    std::cout.precision(20);
    std::cout << "Pi " << std::fixed << (4.0 * (double)circleCount/(double)numberOfPoints)
              << " took " <<  diff << " seconds." << std::endl;
    return 0;
}
