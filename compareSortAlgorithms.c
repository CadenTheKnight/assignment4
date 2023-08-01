#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int extraMemoryAllocated;

//helper function
void swap(int* a, int* b){
	int temp = *a;
	*a = *b;
	*b = temp;
}

int* merge(int* arr, int l, int m, int h){
    int p1 = 0;
    int p2 = 0;

	int n1 = m - l + 1;
	int n2 = h - m;

    //malloc new arr to return
    int* leftArr = (int*)malloc(sizeof(int)*(n1));
	int* rightArr = (int*)malloc(sizeof(int)*(n1));

	//copy into temp arrays
	for(int i = 0; i < n1; i++){
		leftArr[i] = arr[l + i];
	}
	for(int i = 0; i < n2; i++){
		rightArr[i] = arr[m + 1 + i];
	}

    while(p1 < n1 && p2 < n2){
        if(leftArr[p1] < rightArr[p2]){
            arr[p1 + p2] = leftArr[p1++];
        } else {
            arr[p1 + p2] = rightArr[p2++];
        }
    }

    //at this point, one of the smaller arrays has emptied
    //if arr1 has emptied, empty the rest of arr2 into arr
	for(int i = p2; i < n2; i++){
		arr[p1 + i] = leftArr[i];
	}

    //if arr2 has emptied, empty the rest of arr1 into arr
	for(int i = p1; i < n1; i++){
		arr[p2 + i] = rightArr[i];
	}

    free(leftArr);
    free(rightArr);

    return arr;
}

void mergeSort(int* arr, int l, int h) {
    if(l < h){

        int m = (l+h)/2;

        mergeSort(arr, l, m);

        mergeSort(arr, m+1, h);

        arr = merge(arr, l, m, h);
    }
}

// implement insertion sort
// extraMemoryAllocated counts bytes of memory allocated
void insertionSort(int* pData, int n)
{
	for(int i = 1; i < n; i++){
		if(pData[i] < pData[i-1]){

			//start sliding
			int temp = pData[i];
			for(int j = i-1; j > 0; j--){
				if(pData[j] > temp){
					//slide
					pData[j+1] = pData[j];
				} else {

					//insert
					pData[j] = temp;
					break;
				}
			}
		}
	}
}

// implement bubble sort
// extraMemoryAllocated counts bytes of extra memory allocated
void bubbleSort(int* pData, int n)
{
	for(int j = 0; j < n-1; j++){
		for(int i = 0; i < n-1; i++){
			if(pData[i] > pData[i+1]){
				swap(&pData[i], &pData[i+1]);
			}
		}
	}
}

// implement selection sort
// extraMemoryAllocated counts bytes of extra memory allocated
void selectionSort(int* pData, int n)
{
	//implemented recursively

	//base case
	if(n == 0 || n == 1 || pData == NULL) return;

	int min = pData[0];
	int minIdx = 0;

	//loop to find minimum value's index
	for(int i = 1; i < n; i++){
		if(pData[i] < min){
			min = pData[i];
			minIdx = i;
		}
	}

	//swap minimum to first spot
	swap(&pData[0], &pData[minIdx]);

	//recursive call
	pData++;
	return selectionSort(pData, n-1);
}

// parses input file to an integer array
int parseData(char *inputFileName, int **ppData)
{
	FILE* inFile = fopen(inputFileName,"r");
	int dataSz = 0;
	*ppData = NULL;
	
	if (inFile)
	{
		fscanf(inFile,"%d\n",&dataSz);
		*ppData = (int *)malloc(sizeof(int) * dataSz);
		// Implement parse data block

		//printf("whatchup, data size: %d\n", dataSz);
		/*
		for(int i = 0; i < dataSz; i++){
			fscanf(inFile, "%d", &ppData[i]);
			//printf("%d ", ppData[i]);
		}*/
	}
	//printf("\nout of file\n");
	fclose(inFile);
	return dataSz;
}

// prints first and last 100 items in the data array
void printArray(int pData[], int dataSz)
{
	int i, sz = dataSz - 100;
	printf("\tData:\n\t");
	for (i=0;i<100;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\t");
	
	for (i=sz;i<dataSz;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\n");
}

int main(void)
{
	clock_t start, end;
	int i;
    double cpu_time_used;
	char* fileNames[] = {"input1.txt", "input2.txt", "input3.txt"};
	
	for (i=0;i<3;++i)
	{
		int *pDataSrc, *pDataCopy;
		int dataSz = parseData(fileNames[i], &pDataSrc);
		//printf("blah balh\n");
		if (dataSz <= 0)
			continue;
		
		pDataCopy = (int *)malloc(sizeof(int)*dataSz);
	
		printf("---------------------------\n");
		printf("Dataset Size : %d\n",dataSz);
		printf("---------------------------\n");
		
		printf("Selection Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		selectionSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		printf("Insertion Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		insertionSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);

		printf("Bubble Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		bubbleSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		/*
		printf("Merge Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		mergeSort(pDataCopy, 0, dataSz - 1);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		*/
		
		free(pDataCopy);
		free(pDataSrc);
	}
	
}