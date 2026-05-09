/*
Assignment 03: 
(Note: In Lab Manual they have mentioned CUDA but we are supposed to use OpenMP)
Implement Min, Max, Sum and Average operations using Parallel Reduction 
Measure the performance of sequential and parallel algorithms. 
*/

#include <iostream>
#include <vector>
#include <omp.h>
#include <climits>
#include <ctime>
using namespace std;

void init_array(vector<int>& arr){
    arr.clear();
    srand(time(0));
    for(int i=0; i<100000; i++){
        arr.push_back(rand() % 1000000);
    }
}

// Sequential
int min_seq(vector<int>& arr){
    int min = INT_MAX;
    for(int i=0; i<arr.size(); i++){
        if(arr[i] < min) min = arr[i];
    }
    return min;
}

int max_seq(vector<int>& arr){
    int max = INT_MIN;
    for(int i=0; i<arr.size(); i++){
        if(arr[i] > max) max = arr[i];
    }
    return max;
}

long long sum_seq(vector<int>& arr){
    long long sum = 0;
    for(int i=0; i<arr.size(); i++){
        sum += arr[i];
    }
    return sum;
}

double avg_seq(vector<int>& arr){
    return (double)sum_seq(arr) / arr.size();
}

// Parallel
int min_parallel(vector<int>& arr){
    int min = INT_MAX;
    #pragma omp parallel for reduction(min:min)
    for(int i=0; i<arr.size(); i++){
        if(arr[i] < min) min = arr[i];
    }
    return min;
}

int max_parallel(vector<int>& arr){
    int max = INT_MIN;
    #pragma omp parallel for reduction(max:max)
    for(int i=0; i<arr.size(); i++){
        if(arr[i] > max) max = arr[i];
    }
    return max;
}

long long sum_parallel(vector<int>& arr){
    long long sum = 0;
    #pragma omp parallel for reduction(+:sum)
    for(int i=0; i<arr.size(); i++){
        sum += arr[i];
    }
    return sum;
}

double avg_parallel(vector<int>& arr){
    return (double)sum_parallel(arr) / arr.size();
}

int main(){
    vector<int> arr;
    init_array(arr);

    cout << "Sequential:" << endl;
    double start = omp_get_wtime();
    cout << "Min: " << min_seq(arr) << endl;
    cout << "Max: " << max_seq(arr) << endl;
    cout << "Sum: " << sum_seq(arr) << endl;
    cout << "Avg: " << avg_seq(arr) << endl;
    cout << "Time: " << omp_get_wtime() - start << "s" << endl;

    cout << "\nParallel:" << endl;
    start = omp_get_wtime();
    cout << "Min: " << min_parallel(arr) << endl;
    cout << "Max: " << max_parallel(arr) << endl;
    cout << "Sum: " << sum_parallel(arr) << endl;
    cout << "Avg: " << avg_parallel(arr) << endl;
    cout << "Time: " << omp_get_wtime() - start << "s" << endl;

    return 0;
}