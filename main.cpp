#include <iostream>
#include <MaxHeap.h>

class AppStore
{
private:
    AVLTree avlTree;
    MaxHeap maxHeap;

public:
    AppStore(int heapCapacity)
    {
        maxHeap.allocationSize = heapCapacity;
    }

    // 1. ADD NEW APP: Inserts the SAME pointer into both structures
    void AddApp(std::string name, float rating) {
        // Allocate the object exactly ONCE in memory
        App* newApp = new App(name, rating);

        // Insert into AVL Tree (for quick searching by name)
        avlTree.InsertKey(newApp->appName);

        // Insert into Max Heap (for quick fetching of top ratings)
        maxHeap.Insert(name, rating);
    }

    // 2. updates the ratings
    void UpdateRating(std::string name, float newRating)
    {
        //goes through the AVL Tree to see if the app is there
        bool hasTargetApp = avlTree.Contains(name);
        App* TargetApp = new App(name, 0.00);
        //if the app is not there, update the Heap so that the app is there
        if (hasTargetApp != false)
        {
            maxHeap.Update(TargetApp, newRating);
            std::cout << "Successfully updated rating for " << name << "\n";
        } else {
            std::cout << "Error: App not found!\n";
        }
        delete TargetApp;
    }

    // 3. FETCH HIGHEST RATED
    void PrintTopApps(int k) {
        maxHeap.getTopKApps(k);
    }
};

int main()
{
    // MaxHeap storeHeap;
    AppStore storeHeap(5);
    std::cout <<"Heap has been created"<< std::endl;

    // 3. Insert them into the heap
    std::cout << "Inserting apps..." << std::endl;
    storeHeap.AddApp("Flappy Bird", 3.2);
    storeHeap.AddApp("Angry Birds", 4.5);
    storeHeap.AddApp("Candy Crush", 4.8);
    storeHeap.AddApp("Among Us", 4.1);
    storeHeap.UpdateRating("Flappy Bird", 3.2);
    // storeHeap.PrintTopApps(3);


    return 0;
}