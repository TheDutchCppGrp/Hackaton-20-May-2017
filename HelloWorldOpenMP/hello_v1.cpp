#include <omp.h>
#include <iostream>

void expensive_function()
{
    size_t counter = 0;
    for (size_t j=0; j<10000; j++) {
        for (size_t k=0; k<10000; k++) {
            counter++;
        }
    }
}

int main()
{
    std::cout << "Maximum number of threads is " << omp_get_max_threads() << "\n";

    #pragma omp parallel for
    for (int i=0; i<5000; i++) {
        std::cout << "Calling an expensive function 5000 times, i = " << i << std::endl;
        expensive_function();
    }
}
