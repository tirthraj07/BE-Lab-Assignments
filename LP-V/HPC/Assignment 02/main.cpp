/*
Assignment 02: Parallel Sorting Algorithms

Problem Statement:
Write a program to implement Parallel Bubble Sort and Merge sort 
using OpenMP. Use existing algorithms and measure the 
performance of sequential and parallel algorithms.
*/


#include <iostream>
#include <vector>
#include <omp.h>
#include <ctime>
using namespace std;

void init_array(vector<int>& arr){
    // arr = {5,2,1,4,6,2,6,4,8,2,1,4,6,3};
    arr.clear(); 
    srand(time(0));
    for(int i=0; i<100000; i++){
        arr.push_back(rand() % 1000000);
    }

}

void print_array(vector<int>& arr){
    for(int i=0; i<arr.size(); i++){
        cout << arr[i] << " ";
    }
    cout << endl;
}

bool is_array_sorted(vector<int>& arr){
    for(int i=0; i<arr.size()-1; i++){
        if(arr[i] > arr[i+1]) return false;
    }
    return true;
}

void measure_time(void (*sort_function)(vector<int>&), vector<int>& arr){
    double start_time = omp_get_wtime();
    sort_function(arr);
    double end_time = omp_get_wtime();
    cout << "Time taken: " << (end_time - start_time) << " seconds" << endl;
}


void bubble_sort(vector<int>& arr){
    int n = arr.size();
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n - i - 1; j++) {
            if(arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

/*
Problem with parallelizing bubble sort
Why naive parallel bubble sort doesn't work:
    Regular bubble sort compares (0,1), then (1,2), then (2,3)...
    These overlap — j=1 touches arr[1] and arr[2]
                    j=2 touches arr[2] and arr[3]
    arr[2] is shared → race condition if parallelized


This is where we use odd-even transpositions
    By stepping j += 2, every pair is disjoint:
    Even phase (start=0): compares (0,1), (2,3), (4,5), (6,7)...
                                    ↑         ↑         ↑
                        no index is shared between any two pairs

    Odd phase  (start=1): compares (1,2), (3,4), (5,6), (7,8)...
                                    ↑         ↑         ↑
                        again, completely disjoint


Concrete execution with arr = [5, 3, 8, 1, 9, 2], 3 threads:
Phase 0 (even, start=0): pairs (0,1), (2,3), (4,5)
  Thread 0: compares arr[0],arr[1] → 5>3 → swap → [3,5,...]
  Thread 1: compares arr[2],arr[3] → 8>1 → swap → [...,1,8,...]
  Thread 2: compares arr[4],arr[5] → 9>2 → swap → [...,2,9]
  Result: [3, 5, 1, 8, 2, 9]

Phase 1 (odd, start=1): pairs (1,2), (3,4)
  Thread 0: compares arr[1],arr[2] → 5>1 → swap → [3,1,5,...]
  Thread 1: compares arr[3],arr[4] → 8>2 → swap → [...,2,8,9]
  Result: [3, 1, 5, 2, 8, 9]

Phase 2 (even, start=0): pairs (0,1), (2,3), (4,5)
  Thread 0: compares arr[0],arr[1] → 3>1 → swap → [1,3,...]
  Thread 1: compares arr[2],arr[3] → 5>2 → swap → [...,2,5,...]
  Thread 2: compares arr[4],arr[5] → 8<9 → no swap
  Result: [1, 3, 2, 5, 8, 9]

Phase 3 (odd, start=1): pairs (1,2), (3,4)
  Thread 0: compares arr[1],arr[2] → 3>2 → swap → [1,2,3,...]
  Thread 1: compares arr[3],arr[4] → 5<8 → no swap
  Result: [1, 2, 3, 5, 8, 9]

Phase 4 (even): no swaps needed
Phase 5 (odd):  no swaps needed
→ sorted ✓
*/

void bubble_sort_parallel(vector<int>& arr){
    int n = (int)arr.size();
    for(int phase = 0; phase < n; phase++){
        int start = phase % 2;
        int pairs = (n - start) / 2;  // number of disjoint pairs in this phase

        #pragma omp parallel for schedule(static)
        for(int p = 0; p < pairs; p++){
            int j = start + p * 2;     // map pair index back to array index
            if(arr[j] > arr[j + 1]){
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

void merge(vector<int>& arr, int l, int m, int r){
    vector<int> left(arr.begin() + l, arr.begin() + m + 1);
    vector<int> right(arr.begin() + m + 1, arr.begin() + r + 1);

    int i = 0, j = 0, k = l;
    while(i < left.size() && j < right.size()){
        if(left[i] <= right[j]) arr[k++] = left[i++];
        else arr[k++] = right[j++];
    }
    while(i < left.size()) arr[k++] = left[i++];
    while(j < right.size()) arr[k++] = right[j++];
}


void merge_sort_(vector<int>& arr, int low, int high){
    if (low >= high) return;

    int mid = low + (high-low)/2;

    // Partition
    merge_sort_(arr, low, mid);
    merge_sort_(arr, mid+1, high);

    // Merge
    merge(arr, low, mid, high);
}

void merge_sort(vector<int>& arr){
    merge_sort_(arr, 0, arr.size()-1);
}

void merge_sort_task(vector<int>& arr, int l, int r){
    if(l >= r) return;

    if(r - l + 1 <= 2048){         // below this, sequential is faster
        merge_sort_(arr, l, r);    // plain recursive, no tasks
        return;
    }
    
    int m = l + (r - l) / 2;

    #pragma omp task shared(arr) firstprivate(l, m)
    merge_sort_task(arr, l, m);

    #pragma omp task shared(arr) firstprivate(m, r)
    merge_sort_task(arr, m + 1, r);

    #pragma omp taskwait
    merge(arr, l, m, r);
}

void merge_sort_parallel(vector<int>& arr){
    #pragma omp parallel
    {
        #pragma omp single
        merge_sort_task(arr, 0, arr.size() - 1);
    }
}


int main(){
    vector<int> arr;
    cout <<"Bubble Sort: \n";
    init_array(arr);
    //print_array(arr);
    cout << "Is array sorted: " << is_array_sorted(arr) << endl;
    measure_time(bubble_sort, arr);
    cout << "Is array sorted: " << is_array_sorted(arr) << endl;
    //print_array(arr);

    cout << "Bubble Sort Parallel: \n";
    init_array(arr);
    //print_array(arr);
    cout << "Is array sorted: " << is_array_sorted(arr) << endl;
    measure_time(bubble_sort_parallel, arr);
    cout << "Is array sorted: " << is_array_sorted(arr) << endl;
    //print_array(arr);

    cout << "Merge Sort: \n";
    init_array(arr);
    //print_array(arr);
    cout << "Is array sorted: " << is_array_sorted(arr) << endl;
    measure_time(merge_sort, arr);
    cout << "Is array sorted: " << is_array_sorted(arr) << endl;
    //print_array(arr);

    cout << "Merge Sort Parallel: \n";
    init_array(arr);
    //print_array(arr);
    cout << "Is array sorted: " << is_array_sorted(arr) << endl;
    measure_time(merge_sort_parallel, arr);
    cout << "Is array sorted: " << is_array_sorted(arr) << endl;
    //print_array(arr);

}