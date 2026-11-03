#ifndef MAXHEAP_H
#define MAXHEAP_H
#include <string>
struct App {
	std::string appName;
	int rating;
	int frequency;

	App(std::string name, int rating) {
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