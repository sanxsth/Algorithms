#include<bits/stdc++.h>
using namespace std;

void max_heapify(int arr[], int node, int size)
{
	int left = node * 2, right = node * 2 + 1, largest = node;

	if (left <= size && arr[left] > arr[largest])
		largest = left;
	if (right <= size && arr[right] > arr[largest])
		largest = right;

	if (largest != node)
	{
		int tmp = arr[node];
		arr[node] = arr[largest];
		arr[largest] = tmp;

		max_heapify(arr, largest, size);
	}
}

void build_max_heap(int arr[], int size)
{
	// We build the heap bottom up
	// No need to heapify the leaf; elements from index (n/2 + 1) - n are leaf nodes

	for(int i = size/2; i > 0; i--)
	{
		max_heapify(arr, i, size);
	}	
}

void sort_heap(int heap[], int size)
{
	// In each iteration, we select the largest element, swap it with the last index of the heap, reduce the size of heap by one and call heapify-
	// on the root.
	for(int i=size; i>1; i--)
	{
		int tmp = heap[i];
		heap[i] = heap[1];
		heap[1] = tmp;

		size--;
		max_heapify(heap, 1, size);
	}
} 

int main()
{

	int heap[11] = {-1, 2, 4, 2, 1, 0, 3, 8 , 11, 7, 1}; // input array; we won't consider the first element, -1,  as part of the input.
	int n = 10; // size of the heap

	build_max_heap(heap, n); // O(nlogn)
	
	sort_heap(heap, n); // O(nlogn)

	// print sorted values
	for(int i=1; i<=n; i++)
	{
		cout<<heap[i]<<" ";
	}

	return 0;
}
