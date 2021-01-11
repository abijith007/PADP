#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main() {

	int threads;


	int **arr1, **arr2, **arr3;
	int size;
	int i, j, k;
	
	printf("Enter the number of threads: ");
	scanf("%d",&threads);

	printf("Enter the size: ");
	scanf("%d",&size);
	

	arr1 = (int**) malloc(size * sizeof(int*));

	for(i = 0; i < size; i++)
		arr1[i] = (int*) malloc(size * sizeof(int));

	arr2 = (int**) malloc(size * sizeof(int*));

	for(i = 0; i < size; i++)
		arr2[i] = (int*) malloc(size * sizeof(int));

	arr3 = (int**) malloc(size * sizeof(int*));

	for(i = 0; i < size; i++)
		arr3[i] = (int*) malloc(size * sizeof(int));

	for(i = 0; i < size; i++) 
	{
		for(j = 0; j < size; j++)
		{	
			arr1[i][j] = (i+1)*(j+1);
		}
	}

	for(i = 0; i < size; i++) 
	{
		for(j = 0; j < size; j++)
		{
			arr2[i][j] = (i+1)*(j+1);
		}
	}

	for(i = 0; i < size; i++) 
	{
		for(j = 0; j < size; j++)
		{
			arr3[i][j] = 0;
		}
	}

	 

	double t1 = omp_get_wtime();
	omp_set_num_threads(threads);
	#pragma omp parallel for private(j, k)
	

	for(i = 0; i < size; i++) 
	{
		for(j = 0; j < size; j++) 
		{
			int sum = 0;
			for(k = 0;  k < size; k++) 
			{
				sum += arr1[i][k] * arr2[k][j];
			}
			arr3[i][j] = sum;
		}
	}


	double t2 = omp_get_wtime();
	printf("Time taken: %lf\n", t2-t1);
}
