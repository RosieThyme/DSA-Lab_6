#include "MaxHeap.h"
#include <string>
#include <iostream>
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
void MaxHeap::Update(App* app, float newRating)
{
	if (!app)
	{
		return;
	}

	float oldRating = app->rating;
	int appIndex = app->index;

	if (newRating > oldRating)
	{
		PercolateUp(appIndex);
	}
	else if (newRating< oldRating)
	{
		PercolateDown(appIndex);
	}

}
void MaxHeap::getTopKApps(int k)
{
	{
		if (heapSize == 0 || k <= 0) return;

		// Cap k to the actual number of elements available
		if (k > heapSize) k = heapSize;

		std::cout << "\n--- Displaying Top " << k << " Highest Rated Apps ---\n";

		// 1. Create a shallow temporary array to hold the pointers
		App** tempHeapArray = new App*[heapSize];

		// Copy the pointers exactly as they are ordered using pointer arithmetic
		for (int i = 0; i < heapSize; i++)
		{
			*(tempHeapArray + i) = *(heapArray + i);
		}

		// Save the original heap configuration variables
		App** originalHeapArray = heapArray;
		int originalHeapSize = heapSize;

		// 2. Hijack the heap array pointer temporarily to use your existing Delete method
		heapArray = tempHeapArray;

		// 3. Extract and print the top K apps
		for (int i = 0; i < k; i++)
		{
			App* topApp = Delete(); // This safely runs on tempHeapArray now
			if (topApp != nullptr)
			{
				std::cout << (i + 1) << ". " << topApp->appName
						  << " | Rating: " << topApp->rating << "\n";
			}
		}

		// 4. Restore the original heap state
		delete[] tempHeapArray; // Clean up our temporary pointer index array
		heapArray = originalHeapArray;
		heapSize = originalHeapSize;

		// 5. CRUCIAL: Reset the correct heap_indices in the original array layout
		for (int i = 0; i < heapSize; i++)
		{
			(*(heapArray + i))->index = i;
		}
	}

}
App* MaxHeap::Delete()
{
	//if the heap has nothing inside of it go back
	if (heapSize == 0)
	{
		return nullptr;
	}
	//set the maxApp at the begining of the Array
	App* maxApp = *heapArray;
	App* replaceApp = *(heapArray + (heapSize - 1));
	heapSize--;
	//if the heapSize value is greater than 0, set the heapArray value as replaceApp
	if(heapSize > 0)
	{
		*heapArray = replaceApp;
		PercolateDown(0);
	}
return maxApp;
}
MaxHeap::~MaxHeap()
{
	delete[] heapArray;
}
