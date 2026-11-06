cmake_minimum_required(VERSION 3.23)
project(MaxHeap)

set(CMAKE_CXX_STANDARD 17)

add_executable(MaxHeap
		"AVLTree/AVLTree.cpp"
		"AVLTree/AVLTree.h"
		"AVLTree/AVLNode.h"
)

target_sources(MaxHeap
	PRIVATE
	main.cpp
)

target_link_libraries(MaxHeap
	PRIVATE
	Heap
	AVLTree
)

add_library(Heap)
target_sources(Heap
	PRIVATE
	Heap/MaxHeap.cpp
	PUBLIC
	FILE_SET HEADERS
	BASE_DIRS
	Heap
	FILES
	Heap/MaxHeap.h
)

add_library(AVLTree)
target_sources(AVLTree
		PRIVATE
		AVLTree/AVLTree.cpp
		PUBLIC
		FILE_SET HEADERS
		BASE_DIRS
		AVLTree
		FILES
		AVLTree/AVLTree.h
)
