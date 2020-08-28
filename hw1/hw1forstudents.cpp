#include <cmath>
#include <chrono>
#include <iostream>
#include <unistd.h>

#include <vector>

#include <thread>

using std::chrono::duration_cast;
using std::chrono::high_resolution_clock;
using std::chrono::microseconds;
using std::chrono::nanoseconds;

using std::cerr;
using std::cout;
using std::endl;

using std::log2;

using std::vector;
using std::thread;

#define MAX_ARRAY_SIZE 10000000

void cache_locality_test() {
    int num_times = log2(MAX_ARRAY_SIZE);
    int *times = new int[num_times];
    int times_index = 0;

    for(auto size = 1; size < MAX_ARRAY_SIZE; size *= 2) {
        int *arr = new int[size];
        for(auto i = 0; i < size; ++i) {
            arr[i] = rand();
        }
        auto start = high_resolution_clock::now();
        int acc = 0;
        for(auto i = 0; i < size; ++i) {
            acc += arr[i];
        }
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<nanoseconds>(stop - start).count();
        times[times_index++] = duration;
        delete[] arr;
    }

    for(auto i = 0; i < num_times; ++i) {
        cout << times[i] << ' ';
    }
    cout << endl;
    delete[] times;
}

int main(int argc, char **argv) {
    cout << "LOCALITY: " << endl;
    cache_locality_test();
    return 1;
}
