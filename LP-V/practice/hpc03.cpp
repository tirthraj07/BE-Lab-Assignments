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
#define VEC_SIZE 10000000
using namespace std;

vector<int> init_array(){
    vector<int> arr;
    arr.reserve(VEC_SIZE);
    for(int i=0; i<VEC_SIZE; i++){
        arr.push_back(rand() % VEC_SIZE);
    }
    return arr;
}

void wrapper(int (*func)(vector<int>&),vector<int>& arr){
    cout << "[START]" << endl;
    double start_time = omp_get_wtime();
    int res = func(arr);
    double end_time   = omp_get_wtime();
    cout << "Result : " << res << endl;
    cout << "[END] Total Time : " << end_time - start_time << endl;
    return;
}

int min_seq(vector<int>& arr){
    int min = INT_MAX;
    for(int i = 0; i < arr.size(); i++){
        if(arr[i] < min) min = arr[i];
    }
    return min;
}

int max_seq(vector<int>& arr){
    int max = INT_MIN;
    for(int i = 0; i < arr.size(); i++){
        if(arr[i] > max) max = arr[i];
    }
    return max;
}


int sum_seq(vector<int>& arr){
    int sum = 0;
    for(int i = 0; i < arr.size(); i++){
        sum += arr[i];
    }
    return sum;
}

int min_parallel(vector<int>& arr){
    int min = INT_MAX;
    #pragma omp parallel for reduction(min:min)
    for(int i = 0; i < arr.size(); i++){
        if(arr[i] < min) min = arr[i];
    }
    return min;
}

int max_parallel(vector<int>& arr){
    int max = INT_MIN;
    #pragma omp parallel for reduction(max:max)
    for(int i = 0; i < arr.size(); i++){
        if(arr[i] > max) max = arr[i];
    }
    return max;
}


int sum_parallel(vector<int>& arr){
    int sum = 0;
    #pragma omp parallel for reduction(+:sum)
    for(int i = 0; i < arr.size(); i++){
        sum += arr[i];
    }
    return sum;
}

int main(){
    vector<int> arr = init_array();

    wrapper(sum_seq, arr);
    wrapper(max_seq, arr);
    wrapper(min_seq, arr);

    wrapper(sum_parallel, arr);
    wrapper(max_parallel, arr);
    wrapper(min_parallel, arr);

}