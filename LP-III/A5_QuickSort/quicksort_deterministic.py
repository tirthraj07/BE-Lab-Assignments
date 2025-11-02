def lomuto_partition(arr, low, high):
    pivot = arr[high]
    i = low - 1
    for j in range(low, high):
        if arr[j] <= pivot:
            i += 1
            arr[i], arr[j] = arr[j], arr[i]
    arr[i + 1], arr[high] = arr[high], arr[i + 1]
    return i + 1


def hoare_partition(arr, low, high):
    pivot = arr[low]
    i = low - 1
    j = high + 1

    while True:
        i += 1
        while arr[i] < pivot:
            i += 1

        j -= 1
        while arr[j] > pivot:
            j -= 1

        if i >= j:
            return j

        arr[i], arr[j] = arr[j], arr[i]


def quicksort(arr, low, high, method='lomuto'):
    if low < high:
        if method == 'lomuto':
            pi = lomuto_partition(arr, low, high)
            quicksort(arr, low, pi - 1, method)         # Here we pass pi - 1
            quicksort(arr, pi + 1, high, method)

        elif method == 'hoare':
            pi = hoare_partition(arr, low, high)
            quicksort(arr, low, pi, method)             # Here we use pi directly
            quicksort(arr, pi + 1, high, method)
        else:
            raise ValueError("Method must be 'lomuto' or 'hoare'")


def main():
    arr = [10, 7, 8, 9, 1, 5]
    quicksort(arr, 0, len(arr) - 1, method='lomuto')    # choose 'lomuto' or 'hoare'
    print("Sorted array is:", arr)


if __name__ == "__main__":
    main()
