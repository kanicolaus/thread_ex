#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>
#include <future>
#include <numeric>

#include "e2.h"

//create shortcut
namespace sc = std::chrono;

int main() {
    // Testing git!
    // Just added more stuff
    std::vector<int> myVec (50000000);
    std::srand(0);

    //another, better option would be to use std::generate and a c++11ish random generator
    for(int i = 0; i < myVec.capacity(); ++i) {
        myVec[i] = std::rand() % 1000;
    }

    //http://en.cppreference.com/w/cpp/chrono
    auto start = sc::high_resolution_clock::now();

    int minVal;
    int maxVal;
    long sum;
    double average;

    /* MY CODE HERE */
    std::future<int> f1 = std::async(std::launch::async, [&] { return *std::min_element(myVec.begin(), myVec.end());} );
    std::future<int> f2 = std::async(std::launch::async, [&] { return *std::max_element(myVec.begin(), myVec.end());} );
    std::future<long> f3 = std::async(std::launch::async, [&] { return (long) std::accumulate(myVec.begin(), myVec.end(), 0);} );
    std::future<double> f4 = std::async(std::launch::async, [&] { return (double) std::accumulate(myVec.begin(), myVec.end(), 0)/myVec.capacity();} );

    

    minVal = f1.get();
    maxVal = f2.get();
    sum = f3.get();
    average = f4.get();
    //*/

    auto end = sc::high_resolution_clock::now();

    std::cout << "Min: " << minVal << std::endl;
    std::cout << "Max: " << maxVal << std::endl;
    std::cout << "Sum: " << sum << std::endl;
    std::cout << "Average: " << average << std::endl;

    std::cout << "Elapsed Time: " << sc::duration_cast<sc::milliseconds>(end - start).count() << "ms" << std::endl;
}
