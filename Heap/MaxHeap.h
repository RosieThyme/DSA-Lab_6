#ifndef MAXHEAP_H
#define MAXHEAP_H
#include <string>
#include "../AVLTree/AVLTree.h"

class MaxHeap
{
	App** heapArray;
	int allocationSize;
	int heapSize;
	void ResizeArray();
	friend class AppStore;
public:
	MaxHeap();
	void PercolateUp(int nodeIndex);
	void PercolateDown(int nodeIndex);
	void Insert(const std::string &name, const float &rating);
	void Update(App* app, float newRating);
	void getTopKApps(int k);
	App* Delete();
	~MaxHeap();
};
#endif