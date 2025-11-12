"""
Quick Sort
"""

import random

def fixed_partition(nums, low, high):
    pivot = nums[high]
    j = low
    for i in range(low, high):
        if nums[i] < pivot:
            nums[i], nums[j] = nums[j], nums[i]
            j += 1
    
    nums[j], nums[high] = nums[high], nums[j]
    return j

def randomized_partition(nums, low, high):
    pivotIdx = random.randint(low, high)
    nums[high], nums[pivotIdx] = nums[pivotIdx], nums[high]
    pivot = nums[high]
    j = low
    for i in range(low, high):
        if nums[i] < pivot:
            nums[i], nums[j] = nums[j], nums[i]
            j += 1
    
    nums[j], nums[high] = nums[high], nums[j]
    return j

def quicksort(nums, low, high):
    if high <= low:
        return
    
    pivot = randomized_partition(nums, low, high)
    quicksort(nums, low, pivot - 1)
    quicksort(nums, pivot + 1, high)



def main():
    arr = [10, 1, 4 , 5, 8, 2, 3]
    quicksort(arr, 0, len(arr)-1)
    print(arr)

if __name__ == '__main__':
    main()