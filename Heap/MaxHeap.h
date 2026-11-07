#ifndef MAXHEAP_H
#define MAXHEAP_H
#include <string>
#include "../AVLTree/AVLTree.h"

class MaxHeap
{
	App** heapArray;
	AVLTree* tree = new AVLTree();
	int allocationSize;
	int heapSize;
	void ResizeArray();
public:
	MaxHeap();
	void PercolateUp(int nodeIndex);
	void PercolateDown(int nodeIndex);
	void Insert(const std::string &name, const float &rating);
	void UpdateApp(const std::string &name, const float &rating);
	float Delete();
	int Contains(const std::string &key);
	void PrintHeap();
	void GetAppInfo(const std::string &appName);
	void getTopKApps(const int &numberOfApps);
	~MaxHeap();
};
#endif