#include <iostream>
#include <iomanip>
#include <string>
#include "MaxHeap.h"
#include "../AVLTree/AVLTree.h"

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
void MaxHeap::PercolateDown(int nodeIndex, App** &array)
{
	// get child's index from array
	int childIndex = 2 * nodeIndex + 1;
	// sorting by name
	// std::string value = heapArray[nodeIndex].appName;
	float value = array[nodeIndex]->rating;
	while (childIndex < heapSize)
	{
		float maxValue = value;
		int maxIndex = -1;
		for (int i = 0;i < 2 && i + childIndex < heapSize; i++)
		{
			if (array[i + childIndex]->rating > maxValue)
			{
				maxValue = array[i + childIndex]->rating;
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
			App* temp = array[nodeIndex];
			array[nodeIndex] = array[maxIndex];
			array[maxIndex] = temp;

			//Continue loop from the max index node
			nodeIndex = maxIndex;
			childIndex = 2 * nodeIndex + 1;
		}

	}
}
void MaxHeap::Insert(const std::string &name, const float &rating)
{
	App* newApp = new App(name,rating);

	// if already existing in heap, updates existing
	if (Contains(newApp->appName) > -1) {
		std::cout << "Must update existing app" << std::endl;
	} else {
		heapSize++;
		// insert into AVL tree
		tree->InsertKey(newApp->appName);

		//resize the array
		if (heapSize == allocationSize)
		{
			ResizeArray();
		}
		//Add rating to the end of the array
		heapArray[heapSize] = newApp;
		newApp->index = heapSize;

		//percolate up from the last index
		PercolateUp(heapSize);
		std::cout << "Inserted " << name << " with rating " << rating << std::endl;
	}
}
void MaxHeap::UpdateApp(const std::string &name, const float &rating) {
	int appIndex = Contains(name);
	heapArray[appIndex]->frequency++;
	heapArray[appIndex]->rating = rating;
	PercolateUp(appIndex);
}
float MaxHeap::Delete()
{
	float maxValue = heapArray[0]->rating;
	float replaceValue = heapArray[heapSize-1]->rating;
	heapSize--;
	if(heapSize > 0)
	{
		heapArray[0]->rating = replaceValue;
		PercolateDown(0, heapArray);
	}
return maxValue;
}

// returns array of pointers to apps
App** MaxHeap::Heapsort() {
	// copy old array into new array
	auto newArray = new App*[heapSize+1];

	for (int i = 0; i <= heapSize; i++) {
		newArray[i] = heapArray[i];
	}
	// -------------------------------------------
	// Heapify numbers array
	for (int i = ((heapSize + 1) / 2 )- 1; i >= 0; i--) {
		PercolateDown(i, newArray);
	}

	for (int i = heapSize; i > 0; i--) {
		// Swap numbers[0] and numbers[i]
		App* temp = newArray[0];
		newArray[0] = newArray[i];
		newArray[i] = temp;

		PercolateDown(i, newArray);
	}

	std::cout << std::endl;

	return newArray;
}

void MaxHeap::PrintHeap() {
	std::cout << std::endl;
	for (int i = 0; i <= heapSize; i++) {
		std::cout << std::setw(20) << std::left << heapArray[i]->appName << heapArray[i]->rating << std::endl;
	}
}

// returns the index of the requested key
// if requested key doesn't exist, returns -1
int MaxHeap::Contains(const std::string &name) {
	for (int i = 0; i <= heapSize; i++) {
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



void MaxHeap::getTopKApps(const int &numberOfApps) {
	if (numberOfApps > heapSize+1) {
		throw std::runtime_error("More apps than are in the database");
	}
	App** sortedHeap = Heapsort();

	std::cout << std::endl << "[";
	for (int i = heapSize; i > heapSize - numberOfApps; i--) {
		std::cout << "\"" << sortedHeap[i]->appName << "\" ";
	}
	std::cout << "]" << std::endl;
}

MaxHeap::~MaxHeap()
{
	delete[] heapArray;
}
