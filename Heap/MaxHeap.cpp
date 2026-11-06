#include "MaxHeap.h"
#include <string>
void MaxHeap::ResizeArray()
{
	int newAllocationSize = allocationSize * 2;
	App** newArray = new App*[newAllocationSize];
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
	heapArray = new App*[allocationSize];
	heapSize = 0;

}

// sorting by name
void MaxHeap::PercolateUp(int nodeIndex)
{
	while (nodeIndex > 0)
	{
		int parentIndex = (nodeIndex - 1)/2;
		//max-heap property check
		if (heapArray[nodeIndex]->appName <= heapArray[parentIndex]->appName)
		{
			return;
		}
		else
		{
			// swap the values
			App* temp = heapArray[nodeIndex];
			heapArray[nodeIndex] = heapArray[parentIndex];
			heapArray[parentIndex] = temp;
			nodeIndex = parentIndex;
		}
	}
}
void MaxHeap::PercolateDown(int nodeIndex)
{
	// get child's index from array
	int childIndex = 2 * nodeIndex + 1;
	// sorting by name
	// std::string value = heapArray[nodeIndex].appName;
	float value = heapArray[nodeIndex]->rating;
	while (childIndex < heapSize)
	{
		float maxValue = 0;
		int maxIndex = -1;
		for (int i = 0;i < 2 && i + childIndex < heapSize; i++)
		{
			if (heapArray[i + childIndex]->rating > maxValue)
			{
				maxValue = heapArray[i + childIndex]->rating;
				maxIndex = i + childIndex;
			}
		}
		// is there a violation for the max-heap property
		if (maxValue == value)
		{
			return;
		}
		else
		{
			//swap the values heapArray[nodeIndex] and heapArray[maxIndex]
			float temp = heapArray[nodeIndex]->rating;
			heapArray[nodeIndex]->rating = heapArray[maxIndex]->rating;
			heapArray[maxIndex]->rating = temp;

			//Continue loop from the max index node
			nodeIndex = maxIndex;
			childIndex = 2 * nodeIndex + 1;
		}

	}
}
void MaxHeap::Insert(const std::string &name, const float &rating)
{
	//resize the value 
	if (heapSize == allocationSize)
	{
		ResizeArray();
	}

	//Add rating to the end of the array
	App* newApp = new App(name,rating);
	*(heapArray + heapSize) = newApp;
	newApp->index = heapSize;

	//percolate up from the last index
	PercolateUp(heapSize - 1);

}
float MaxHeap::Delete()
{
	float maxValue = heapArray[0]->rating;
	float replaceValue = heapArray[heapSize-1]->rating;
	heapSize--;
	if(heapSize > 0)
	{
		heapArray[0]->rating = replaceValue;
		PercolateDown(0);
	}
return maxValue;
}
MaxHeap::~MaxHeap()
{
	delete[] heapArray;
}
