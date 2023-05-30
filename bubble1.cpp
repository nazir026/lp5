#include <iostream>
#include <omp.h>

using namespace std;

void bubbleSort(int arr[], int n){
	int i, j;
	bool swapped;
	
	for(i=0; i<n-1; i++){
		swapped = false;
	
		#pragma omp parallel for shared(arr, n, swapped)
		for(j=0; j<n-i-1; j++){
			if(arr[j]>arr[j+1]){
				#pragma omp critical
				{
					swap(arr[j], arr[j+1]);
					swapped = true;
				}			
			}
		}
			
		if(!swapped){
			break;
		}	
	}
}


int main(){
	int n;
	cout << "Enter length of array: " << endl;
	cin >> n;

	int arr[n];
	cout << "Enter array elements: " << endl;
	
	for(int i=0; i<n; i++){
		cin >> arr[i];
	}
	
	bubbleSort(arr, n);
	
	cout << "Sorted array is: " << endl;
	for(int i=0; i<n; i++){
		cout << arr[i]<<" ";
	}

	return 0;
}
