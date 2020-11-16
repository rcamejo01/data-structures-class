#include <iostream>
#include "support.h"
#include <iomanip>
#include <fstream>
#include <string>

using namespace std;

int countLines(string fname)
{
	ifstream file;
	file.open(fname);
	if (file.is_open())
	{
		int val;
		int count = 0;
		while (file >> val)
			count++;
		file.close();
		return count;
	}
	else
		return 0;
}

int* readFile(string fname, int count){
	ifstream file;
	file.open(fname);
	int* arr = new int[count]; //allocating memory in new arr
	for(int j=0;j<count;j++)
	{
		file>>arr[j];
	}
	return arr; 
}

void printVector(int arr[], int count)
{
	for(int i=0;i<count;i++)
	{
		cout << arr[i] << " " ;
	}
	cout << endl;
}

void swap(int &a, int &b){
	int temp = a;
	a = b;
	b = temp;
}

void bubbleSort(int arr[], int n){
	for(int i=0;i<n-1;i++)
	{
		for(int j=0;j<n-i-1;j++)
		{
			if(arr[j] > arr[j+1])
			{
				swap(arr[j],arr[j+1]);
			}
		}
	}
}

void selectionSort(int arr[], int n){
	for(int i=0;i<n-1;i++)
	{
		int smallest = i;
		for(int j=i+1;j<n;j++)
		{
			if(arr[j]<arr[smallest])
				smallest =j;
		}
		swap(arr[smallest],arr[i]);
	}
}

void insertionSort(int arr[], int n){
	for(int i=1;i<n;i++)
	{
		int current = arr[i];
		int j=i-1;
		while(j>=0 && arr[j] > current)
		{
			arr[j+1] = arr[j];
			j--;
		}
		arr[j+1]=current;
	}
}

int quickSort(int arr[], int start, int end){
	int pivot = arr[end]; //making partitions around the pivot (last element)
	int i = start - 1; //index of start
	for(int j=start;j<=end-1;j++)
	{
		//go through array to see if smaller than pivot
		if(arr[j]<pivot)
		{
			i++; //increment index of start
			swap(arr[i],arr[j]);
		}
	}
	swap(arr[i+1],arr[end]);
	i++;
	return i;
}

//recursive function for quickSort
void recursiveQuick(int arr[], int start, int end){
	if(start<end)
	{
		int a = quickSort(arr,start,end);
		recursiveQuick(arr,start,a-1);
		recursiveQuick(arr,a+1,end);
	}
}

void mergeSort(int arr[], int leftmost, int median, int rightmost)
{
	int left_half=median-leftmost+1;
	int right_half=rightmost-median;

	int* left = new int[left_half];
	int* right = new int[right_half];
	

	for(int i=0;i<left_half;i++)
	{
		left[i]=arr[leftmost+i];
	}
	for(int j=0;j<right_half;j++)
	{
		right[j]=arr[median+1+j];
	}

	//merge back into array
	int i=0, j=0, k=leftmost;

	while(i<left_half && j<right_half)
	{
		if(left[i]<=right[j])
		{
			arr[k]=left[i];
			i++;
		}
		else
		{
			arr[k]=right[j];
			j++;
		}
		k++;
	}
	
	//copy elements of Left subarray
	while(i<left_half)
	{
		arr[k]=left[i];
		i++;
		k++;
	}

	//copy elements of Right subarray
	while(j<right_half)
	{
		arr[k]=right[j];
		j++;
		k++;
	}
}

//recursive function for mergeSort
void recurseMerge(int arr[], int leftmost, int rightmost)
{
	if (leftmost<rightmost)
	{
		int median=leftmost+(rightmost-1)/2;
		recurseMerge(arr,leftmost,rightmost);
		recurseMerge(arr,median+1,rightmost);
		mergeSort(arr,leftmost,median,rightmost);
	}
}

void main(){
	
	int size = countLines("unsort1.txt");

	int* vec = readFile("unsort1.txt",size);
	double start = getCPUTime();
	bubbleSort(vec, size);
	double end = getCPUTime();
	double bubbleTime = end - start;
	cout<<"Sorted bubble array:" << endl;
	printVector(vec,size);

	cout << "Bubble sort took: " << scientific << bubbleTime << " seconds " << endl;
	
	int* vec2 = readFile("unsort1.txt", size);

	start = getCPUTime();
	selectionSort(vec2, size);
	end = getCPUTime();
	double selectionTime = end - start;
	cout << "Sorted selection array:" << endl;
	printVector(vec2,size);
	cout << endl;

	cout << "Selection sort took: " << scientific << setprecision(6) << selectionTime << endl;

	int* vec3 = readFile("unsort1.txt", size);

	start = getCPUTime();
	insertionSort(vec3,size);
	end = getCPUTime();
	double insertionTime = end - start;
	cout << "Sorted insertion array: " << endl;
	printVector(vec3,size);

	cout << "Insertion sort took: " << scientific << setprecision(6) << insertionTime << endl;

	int* vec4 =readFile("unsort1.txt", size);
	
	double start=getCPUTime();
	recursiveQuick(vec4, 0,size-1);
	double end=getCPUTime();
	double quickTime = end-start;
	
	cout<< "Quick sort took: " << scientific << quickTime << endl;
	cout<<"Sorted quick array: " << endl;
	printVector(vec4,size);

	int* vec5 = readFile("unsort1.txt", size);

	start=getCPUTime();
	recurseMerge(vec5, 0, size-1);
	end=getCPUTime();
	double mergeTime = end-start;
	cout<<"Sorted quick array: " << endl;
	printVector(vec5,size);
	
	cout<< "Merge sort took: " << scientific << setprecision(6) << mergeTime << endl;
}
