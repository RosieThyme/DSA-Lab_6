#ifndef MAXHEAP_H
#define MAXHEAP_H
class MaxHeap
{ 	private:
	int* heapArray;
	int allocationSize;
	int heapSize;
	void ResizeArray();
	public:
	MaxHeap();
	void PercolateUp(int nodeIndex);
	void PercolateDown(int nodeIndex);
	void Insert(int value);
	int Delete();
	~MaxHeap();
};
#endif