// **************************************************************************
//  File       [sort_tool.cpp]
//  Author     [Yu-Hao Ho]
//  Synopsis   [The implementation of the SortTool Class]
//  Modify     [2020/9/15 Mu-Ting Wu]
// **************************************************************************

#include "sort_tool.h"
#include<iostream>
#include <vector>
#include <random>
using std::vector;

// Constructor
SortTool::SortTool() {}

// Insertsion sort method
void SortTool::InsertionSort(vector<int>& data) {
    // Function : Insertion sort
    // TODO : Please complete insertion sort code here
    for (int i = 1; i < data.size(); i++)
    {
        int key = data[i];
        int j = i - 1;
        while (key < data[j] && j >= 0)
        {
            data[j+1] = data[j];
            j--;
        }
        data[j+1] = key;
    }
}

// Quick sort method
void SortTool::QuickSort(vector<int>& data){
    QuickSortSubVector(data, 0, data.size() - 1);
}
// Sort subvector (Quick sort)
void SortTool::QuickSortSubVector(vector<int>& data, int low, int high) {
    // Function : Quick sort subvector
    // TODO : Please complete QuickSortSubVector code here
    // Hint : recursively call itself
    //        Partition function is needed
    if (low < high)
    {
        int pivot = Partition(data, low, high);
        QuickSortSubVector(data, low, pivot - 1);
        QuickSortSubVector(data, (pivot + 1), high);
    }
}

int SortTool::Partition(vector<int>& data, int low, int high) {
    // Function : Partition the vector 
    // TODO : Please complete the function
    // Hint : Textbook page 171

    // produce random pivot
    std::random_device rd;
    std::default_random_engine generator( rd() );
    std::uniform_real_distribution<float> unif(0.0, 1.0);
    float x = unif(generator);
    int y = x * (high-low) + low;
    int pivot = data[y];
    data[y] = data[high];
    data[high] = pivot;

    int i = low - 1;
    for (int j = low; j < high; j++)
    {
        if (data[j] <= pivot)
        {
            i++;
            int temp = data[i];
            data[i] = data[j];
            data[j] = temp;
        }
    }
    int temp = data[i+1];
    data[i+1] = data[high];
    data[high] = temp;
    return i+1;
}

// Merge sort method
void SortTool::MergeSort(vector<int>& data){
    MergeSortSubVector(data, 0, data.size() - 1);
}

// Sort subvector (Merge sort)
void SortTool::MergeSortSubVector(vector<int>& data, int low, int high) {
    // Function : Merge sort subvector
    // TODO : Please complete MergeSortSubVector code here
    // Hint : recursively call itself
    //        Merge function is needed
    if ((high - low) >= 1)
    {
        int middle1 = (high + low) / 2;
        int middle2 = middle1 + 1;
        MergeSortSubVector(data, low, middle1);
        MergeSortSubVector(data, middle2, high);
        Merge(data, low, middle1, middle2, high);
    }
}

// Merge
void SortTool::Merge(vector<int>& data, int low, int middle1, int middle2, int high) {
    // Function : Merge two sorted subvector
    // TODO : Please complete the function
    int leftIndex = low;
    int rightIndex =  middle2;
    int combinedIndex =  low;
    vector <int> combined(data.size());
    while (leftIndex <= middle1 && rightIndex <= high)
    {
        if (data[leftIndex] <= data[rightIndex])
            combined[combinedIndex++] = data[leftIndex++];
        else
            combined[combinedIndex++] = data[rightIndex++];
    }
    if (leftIndex == middle2)
    {
        while (rightIndex <= high)
        {
            combined[combinedIndex++] = data[rightIndex++];
        }
    }
    else
    {
		while (leftIndex <= middle1)
        {
			combined[combinedIndex++] = data[leftIndex++];
        }
    }
    for (int i = low; i <= high; ++i)
    {
        data[i] = combined[i];
    }
}

// Heap sort method
void SortTool::HeapSort(vector<int>& data) {
    // Build Max-Heap
    BuildMaxHeap(data);
    // 1. Swap data[0] which is max value and data[i] so that the max value will be in correct location
    // 2. Do max-heapify for data[0]
    for (int i = data.size() - 1; i >= 1; i--) {
        swap(data[0],data[i]);
        heapSize--;
        MaxHeapify(data,0);
    }
}

//Max heapify
void SortTool::MaxHeapify(vector<int>& data, int root) {
    // Function : Make tree with given root be a max-heap if both right and left sub-tree are max-heap
    // TODO : Please complete max-heapify code here
    int left = root * 2;
    int right =  root * 2 + 1;
    int largest;
    if (left < heapSize && data[left] > data[root])
    {
        largest = left;
    }
    else
    {
        largest = root;
    }
    if (right < heapSize && data[right] > data[largest])
    {
        largest = right;
    }
    if (largest != root)
    {
        int temp = data[root];
        data[root] = data[largest];
        data[largest] = temp;
        MaxHeapify(data, largest);
    }
}

//Build max heap
void SortTool::BuildMaxHeap(vector<int>& data) {
    heapSize = data.size(); // initialize heap size
    // Function : Make input data become a max-heap
    // TODO : Please complete BuildMaxHeap code here
    for (int i = data.size() / 2; i >= 1; i--)
    {
        MaxHeapify(data, i);
    }
}
