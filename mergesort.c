#include <stdio.h>
#define MAX 30

void mergeSort(int arr[], int n) {
	int temp[MAX], i, j, k, size, l1, h1, l2, h2;
	/*l1 lower bound of first pair and so on*/
	for (size = 1; size < n; size = size * 2) {
		l1 = 0;
		k = 0; /*Index for temp array*/
		while (l1 + size < n) {
			h1 = l1 + size - 1;
			l2 = h1 + 1;
			h2 = l2 + size - 1;
			/* h2 exceeds the limlt of arr */
			if (h2 >= n)
				h2 = n - 1;

			/*Merge the two pairs with lower limits l1 and l2*/
			i = l1;
			j = l2;

			while (i <= h1 && j <= h2) {
				if (arr[i] <= arr[j])
					temp[k++] = arr[i++];
				else
					temp[k++] = arr[j++];
			}

			while (i <= h1)
				temp[k++] = arr[i++];
			while (j <= h2)
				temp[k++] = arr[j++];
			/*Merging completed*/
			/*Take the next two pairs for merging */
			l1 = h2 + 1;
		}/*End of while*/

		/*any pair left */
		for (i = l1; k < n; i++)
			temp[k++] = arr[i];

		for (i = 0; i < n; i++)
			arr[i] = temp[i];

	}
}

void group3(int array[], int array_size, int *output){
#pragma HLS INTERFACE mode=s_axilite port= group3
#pragma HLS INTERFACE mode=s_axilite port= array
#pragma HLS INTERFACE mode=s_axilite port= array_size
#pragma HLS INTERFACE mode=s_axilite port= output

	mergeSort(array, array_size);

	for(int i=0; i<array_size; i++){
		output[i] = array[i];
	}
}
