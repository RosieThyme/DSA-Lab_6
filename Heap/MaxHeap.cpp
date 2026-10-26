#include "MaxHeap.h"
void MaxHeap::ResizeArray()
{
	int newAllocationSize = allocationSize * 2;
	int* newArray = new int[newAllocationSize];
	if (newArray)
	{
		for (int i = 0; i < allocationSize; i++)
		{
			newArray[i] = heapArray[i];
		}
		delete[] heapArray;
		heapArray = newArray;

		allocationSize = newAllocationSize;
	}
}

MaxHeap::MaxHeap()
{
	allocationSize = 1;
	heapArray = new int[allocationSize];
	heapSize = 0;

}
void MaxHeap::PercolateUp(int nodeIndex)
{
	while (nodeIndex > 0)
	{
		int parentIndex  =(nodeIndex - 1)/2;
		//max-heap property check
		if (heapArray[nodeIndex] <= heapArray[parentIndex])
		{
			return;
		}
		else
		{
			int temp = heapArray[nodeIndex];
			heapArray[nodeIndex] = heapArray[parentIndex];
			heapArray[parentIndex] = temp;
			nodeIndex = parentIndex;
		}
	}
}
void MaxHeap::PercolateDown(int nodeIndex)
{
	int childIndex = 2 * nodeIndex + 1;
	int value = heapArray[nodeIndex];
	
	while (childIndex < heapSize)
	{
		int maxValue = 0;
		int maxIndex = -1;
		for (int i = 0;i < 2 && i + childIndex < heapSize; i++)
		{
			if (heapArray[i + childIndex] > maxValue)
			{
				maxValue = heapArray[i + childIndex];
				maxIndex = i + childIndex;
			}
		}
		// is there a violation fo tthe max-heap property
		if (maxValue == value)
		{
			return;
		}
		else
		{
			//swap the values heapArray[nodeIndex] and heapArray[maxIndex]
			int temp = heapArray[nodeIndex];
			heapArray[nodeIndex] = heapArray[maxIndex];
			heapArray[maxIndex] = temp;

			//Continue loop from the max index node
			nodeIndex = maxIndex;
			childIndex = 2 * nodeIndex + 1;
		}

	}
}
void MaxHeap::Insert(int value)
{
	//resize the value 
	if (heapSize == allocationSize)
	{
		ResizeArray();
	}

	//Add value to the end of the array
	heapArray[heapSize] = value;
	heapSize++;
	
	//percolate up from the last index
	PercolateUp(heapSize - 1);

}
int MaxHeap::Delete()
{
	int maxValue = heapArray[0];
	int replaceValue = heapArray[heapSize-1];
	heapSize--;
	if(heapSize > 0)
	{
		heapArray[0] = replaceValue;
		PercolateDown(0);
	}
return maxValue;
}
MaxHeap::~MaxHeap()
{
	delete[] heapArray;
}
