#include<iostream>
#include<vector>
#include<ctime>
#include<omp.h>
#define VEC_SIZE 10000
using namespace std;

vector<int> init_vector(vector<int>& vec){
    vec.clear();
    vec.reserve(VEC_SIZE);
    for(int i=0; i<VEC_SIZE; i++){
        vec.push_back(rand()%VEC_SIZE);
    }
    return vec;
}       

bool is_sorted(vector<int> &vec){
    for(int i=1; i<vec.size(); i++){
        if(vec[i] < vec[i-1]) return false;
    }
    return true;
}

void capture_time(void (*func)(vector<int>&), vector<int>& arr){
    cout << "Is sorted? " << is_sorted(arr) << endl;
    cout << "Starting sorting function... " << endl;
    double start_time = omp_get_wtime();
    func(arr);
    double end_time = omp_get_wtime();
    cout << "Function Stopped" << endl;
    cout << "Time Taken : " << end_time - start_time << " seconds" << endl;
    cout << "Is sorted? " << is_sorted(arr) << endl;
}

// -------

void bubble_sort(vector<int>& arr){
    int n = arr.size();
    for(int i=0; i<n; i++){
        for(int j=0; j<n-i-1; j++){
            if(arr[j] > arr[j+1]){
                swap(arr[j], arr[j+1]);
            }
        }
    }
}


void bubble_sort_parallel(vector<int>& arr){
    int n = arr.size();
    for(int i=0; i<n; i++){
        int start = i % 2;
        int num_pairs = (n-start)/2;
        
        #pragma omp parallel for schedule(static)
        for(int p=0; p<num_pairs; p++){
            int j = start + p * 2;
            if(arr[j] > arr[j+1]) swap(arr[j], arr[j+1]);
        }
    }
}

void merge(vector<int>& arr, int low, int mid, int high){
    vector<int> left;
    vector<int> right;
    left.insert(left.end(), arr.begin()+low, arr.begin()+mid+1);
    right.insert(right.end(), arr.begin()+mid+1, arr.begin()+high+1);

    int i = 0, n = left.size();
    int j = 0, m = right.size();
    int k = low;

    while(i < n && j < m){
        if(left[i] <= right[j]) arr[k++] = arr[i++];
        else arr[k++] = arr[j++];
    }

    while(i < n) arr[k++] = arr[i++];
    while(j < m) arr[k++] = arr[j++];
}

void merge_sort_(vector<int>& arr, int low, int high){
    if(low >= high) return;    
    int mid = low + (high-low)/2;

    merge_sort_(arr, low, mid);
    merge_sort_(arr, mid+1, high);

    merge(arr, low, mid, high);
}

void merge_sort(vector<int>& arr){
    merge_sort_(arr, 0, arr.size()-1);
}

void merge_sort_parallel_(vector<int>& arr, int low, int high){
    if(low > high) return;

    int len = high - low + 1;
    if(len <= 2048){
        merge_sort_(arr, low, high);
        return;
    }

    int mid = low + (high-low)/2;
    #pragma omp task firstprivate(low, mid) shared(arr)
    merge_sort_parallel_(arr, low, mid);

    #pragma omp task firstprivate(mid, high) shared(arr)
    merge_sort_parallel_(arr, mid+1, high);

    #pragma omp taskwait
    merge(arr, low, mid, high);
}

void merge_sort_parallel(vector<int>& arr){
    #pragma omp parallel
    {
        #pragma omp single
        merge_sort_parallel_(arr, 0, arr.size() - 1);
    }
}

int main(){
    srand(time(0));

    vector<int> arr;
    init_vector(arr);
    capture_time(bubble_sort, arr);    

    init_vector(arr);
    capture_time(bubble_sort_parallel, arr);

    init_vector(arr);
    capture_time(merge_sort, arr);

    init_vector(arr);
    capture_time(merge_sort_parallel, arr);
}