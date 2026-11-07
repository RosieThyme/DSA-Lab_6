#include <iostream>
#include <MaxHeap.h>
#include <AVLTree.h>

int main()
{
    MaxHeap storeHeap;
    std::cout <<"Heap and AVL Tree have been created"<< std::endl;

    // 3. Insert them into the heap
    std::cout << "Inserting apps..." << std::endl;
    storeHeap.Insert("Flappy Bird", 3.2);
    storeHeap.Insert("Angry Birds", 4.5);
    storeHeap.Insert("Candy Crush", 4.8);
    storeHeap.Insert("Candy Crush", 4.8);
    storeHeap.Insert("Among Us", 4.1);
    storeHeap.Insert("Wordle", 4.6);

    storeHeap.GetAppInfo("Flappy Bird");
    storeHeap.GetAppInfo("Candy Crush");


    return 0;
}