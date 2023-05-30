#include <iostream>
#include <omp.h>

using namespace std;

void merge(int arr[], int left[], int leftSize, int right[], int rightSize) {
    int i = 0, j = 0, k = 0;
    while (i < leftSize && j < rightSize) {
        if (left[i] <= right[j]) {
            arr[k++] = left[i++];
        } else {
            arr[k++] = right[j++];
        }
    }
    while (i < leftSize) {
        arr[k++] = left[i++];
    }
    while (j < rightSize) {
        arr[k++] = right[j++];
    }
}

void mergeSort(int arr[], int size) {
    if (size <= 1) {
        return;
    }

    int mid = size / 2;
    int left[mid];
    int right[size - mid];

    #pragma omp parallel sections
    {
        #pragma omp section
        {
            // Copying elements to the left half
            for (int i = 0; i < mid; i++) {
                left[i] = arr[i];
            }
            // Sorting the left half in parallel
            mergeSort(left, mid);
        }

        #pragma omp section
        {
            // Copying elements to the right half
            for (int i = mid; i < size; i++) {
                right[i - mid] = arr[i];
            }
            // Sorting the right half in parallel
            mergeSort(right, size - mid);
        }
    }

    merge(arr, left, mid, right, size - mid);
}

int main() {
    int size;
    cout << "Enter length of the array: ";
    cin >> size;

    int arr[size];
    cout << "Enter array elements: " << endl;
    for (int i = 0; i < size; i++) {
        cin >> arr[i];
    }

    mergeSort(arr, size);

    cout << "Sorted array: ";
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }

    return 0;
}
