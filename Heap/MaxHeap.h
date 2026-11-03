#ifndef MAXHEAP_H
#define MAXHEAP_H
#include <string>
struct App {
	std::string appName;
	float rating;
	int frequency;
	
	App(std::string name = "Default", float rating = 0) {
		appName = name;
		this->rating = rating;
		this->frequency = 1;
	}
};

class MaxHeap
{
	App* heapArray;
	int allocationSize;
	int heapSize;
	void ResizeArray();
public:
	MaxHeap();
	void PercolateUp(int nodeIndex);
	void PercolateDown(int nodeIndex);
	void Insert(const std::string &name, const int &rating);
	int Delete();
	~MaxHeap();
};
#endif