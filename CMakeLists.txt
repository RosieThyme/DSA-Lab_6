cmake_minimum_required(VERSION 3.23)
project(MaxHeap)

set(CMAKE_CXX_STANDARD 17)

add_executable(Vaca_Camilla_Noel_Hildline_Sagesse_Samuel
		main.cpp
)

target_sources(Vaca_Camilla_Noel_Hildline_Sagesse_Samuel
	PRIVATE
	"AVLTree/AVLTree.cpp"
	"AVLTree/AVLTree.h"
	"AVLTree/AVLNode.h"
	"Heap/MaxHeap.cpp"
	"Heap/MaxHeap.h"
)

target_link_libraries(Vaca_Camilla_Noel_Hildline_Sagesse_Samuel
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
