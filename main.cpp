#include <iostream>
#include <MaxHeap.h>

int main()
{
    MaxHeap storeHeap;
    std::cout <<"Heap has been created"<< std::endl;

    // 3. Insert them into the heap
    std::cout << "Inserting apps..." << std::endl;
    storeHeap.Insert("Flappy Bird", 3.2);
    storeHeap.Insert("Angry Birds", 4.5);
    storeHeap.Insert("Candy Crush", 4.8);
    storeHeap.Insert("Among Us", 4.1);

    return 0;
}