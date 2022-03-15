/* 
 * Multithreaded merge sort. 
 * Adapted from https://www.geeksforgeeks.org/merge-sort/
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/* data shared by all threads */
int *arr_left;
int *arr_right;
int arr_size;

/* thread functions */
void *mergeSortThread(void *mergeSortArgs);

/* helper functions */
void merge(int arr[], int left, int mid, int right);
void mergeSort(int arr[], int left, int right);

struct mergeSortArgs {
	int *arr;
	int left;
	int right;
};

int main(int argc, char *argv[]) {

	/* check usage */
	if (argc < 2) {
		fprintf(stderr, "Usage: ./sort <positive_integer> ... <positive_integer>\n");
		exit(1);
	}

	/* initialize thread data and check all arguments are positive integers */
	arr_size = argc - 1;
	arr_left = (int *) malloc(arr_size/2 * sizeof(int));
	arr_right = (int *) malloc((arr_size - arr_size/2) * sizeof(int));
	int arg;
	for (int i = 0; i < arr_size; i++) { 
		if ((arg = atoi(argv[i+1])) < 1) {
			fprintf(stderr, "Argument %s is not a positive integer\n", argv[i+1]);
			exit(1);
		}
		if (i < arr_size/2) {
			arr_left[i] = arg;
		}
		else {
			arr_right[i - arr_size/2] = arg;
		}
	}

	/* create threads to sort left and right halves */
	pthread_t tid_1, tid_2;
	pthread_attr_t attr;

	pthread_attr_init(&attr);
	
	struct mergeSortArgs *ms_args_1 = malloc(sizeof(struct mergeSortArgs));
	ms_args_1->arr = arr_left;
	ms_args_1->left = 0;
	ms_args_1->right = arr_size/2 - 1;
 
	struct mergeSortArgs *ms_args_2 = malloc(sizeof(struct mergeSortArgs));
	ms_args_2->arr = arr_right;
	ms_args_2->left = 0;
	ms_args_2->right = arr_size - 1 - arr_size/2;

	pthread_create(&tid_1, &attr, mergeSortThread, (void *) ms_args_1);
	pthread_create(&tid_2, &attr, mergeSortThread, (void *) ms_args_2);

	pthread_join(tid_1, NULL);
	pthread_join(tid_2, NULL);
	
	/* merge sorted left and right halves */
	int arr[arr_size];
	for (int i = 0; i < arr_size; i++) { 
		if (i < arr_size/2) {
			arr[i] = arr_left[i];
		}
		else {
			arr[i] = arr_right[i - arr_size/2];
		}
	}
	merge(arr, 0, arr_size/2 - 1, arr_size-1);

	printf("Sorted array is: ");
	for (int i = 0; i < arr_size; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");

	/* free resources */
	free(arr_left);
	free(arr_right);
	free(ms_args_1);
	free(ms_args_2);

	return 0;
}

/* merges two subarrays of arr[].
 * first subarray is arr[left, ..., mid]
 * second subarray is arr[mid+1, ...., right] */
void merge(int arr[], int left, int mid, int right) {

	int i, j, k;
	int n1 = mid - left + 1;
	int n2 = right - mid;

	/* create temp arrays */
	int left_sub[n1], right_sub[n2];

	/* copy data to temp arrays left_sub[] and right_sub[] */
	for (i = 0; i < n1; i++)
		left_sub[i] = arr[left + i];
	for (j = 0; j < n2; j++)
		right_sub[j] = arr[mid + 1 + j];

	/* merge the temp arrays back into arr[left, ..., right] */
	i = 0; /* initial index of first subarray */
	j = 0; /* initial index of second subarray */
	k = left; /* initial index of merged subarray */
	while (i < n1 && j < n2) {
		if (left_sub[i] <= right_sub[j]) {
			arr[k] = left_sub[i];
			i++;
		}
		else {
			arr[k] = right_sub[j];
			j++;
		}
		k++;
	}

	/* copy the remaining elements of left_sub[], if there are any */
	while (i < n1) {
		arr[k] = left_sub[i];
		i++;
		k++;
	}

	/* copy the remaining elements of right_sub[], if there are any */
	while (j < n2) {
		arr[k] = right_sub[j];
		j++;
		k++;
	}
}

/* left is left index and right is right index of the sub-array of arr to be 
 * sorted */
void mergeSort(int arr[], int left, int right) {

	if (left < right) {
		/* same as (left+right)/2, but avoids overflow for large left 
		 * and right */
		int mid = left + (right-left)/2;

		/* sort first and second halves */
		mergeSort(arr, left, mid);
		mergeSort(arr, mid + 1, right);

		merge(arr, left, mid, right);
	}
}

/* mergeSortThread merely calls mergeSort */
void *mergeSortThread(void *mergeSortArgs) {
	
	struct mergeSortArgs *msa = (struct mergeSortArgs *) mergeSortArgs;
	mergeSort(msa->arr, msa->left, msa->right);

	pthread_exit(0);
}
