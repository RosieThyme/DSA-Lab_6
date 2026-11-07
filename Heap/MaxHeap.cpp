#include "MaxHeap.h"
#include "../AVLTree/AVLTree.h"

#include <iostream>
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
	heapSize = -1;

}

// sorting by name
void MaxHeap::PercolateUp(int nodeIndex)
{
	while (nodeIndex > 0)
	{
		int parentIndex = (nodeIndex - 1)/2;
		//max-heap property check
		if (heapArray[nodeIndex]->rating <= heapArray[parentIndex]->rating)
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
	heapSize++;
	App* newApp = new App(name,rating);

	// if not a duplicate, inserts into AVL tree
	if (Contains(newApp->appName) == -1) {
		tree->InsertKey(newApp->appName);
	}

	//resize the value
	if (heapSize == allocationSize)
	{
		ResizeArray();
	}
	//Add rating to the end of the array
	heapArray[heapSize] = newApp;
	newApp->index = heapSize;

	//percolate up from the last index
	PercolateUp(heapSize);

	PrintHeap();
	tree->PrintTree();


}
void MaxHeap::Update() {

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

void MaxHeap::PrintHeap() {
	std::cout << std::endl;
	for (int i = 0; i < heapSize + 1; i++) {
		std::cout << heapArray[i]->appName << " | " << heapArray[i]->rating << std::endl;
	}
}

// returns the index of the requested key
int MaxHeap::Contains(const std::string &name) {
	for (int i = 0; i < heapSize; i++) {
		if (heapArray[i]->appName == name) {
			return i;
		}
	}
	return -1;
}

void MaxHeap::GetAppInfo(const std::string &appName) {
	int appIndex = Contains(appName);
	if (appIndex > -1) {
		std::cout << appName << " -- Rating: " << heapArray[appIndex]->rating << ", Frequency: " << heapArray[appIndex]->frequency << std::endl;
	}
}

MaxHeap::~MaxHeap()
{
	delete[] heapArray;
}
