#include "PriorityQueue.hpp"
#include <limits.h>

using namespace std;

void swap(ReviewInfo *a, ReviewInfo *b)
{
    ReviewInfo temp = *a; // this will store the value of a in temp 
    *a = *b; // this will assign the value of b to a 
    *b = temp; // store the value stored 
}

/*
Constructor for our MinHeap implementation
*/
PriorityQ::PriorityQ(int cap)
{
    capacity = cap; // this sets the capacity of the pq
    currentSize = 0; // sets the current size to 0 initially as there are no elements in the heap
    heapArr = new ReviewInfo[cap]; // this allocates the memory for the array heap
}

/*
Destructor
*/
PriorityQ::~PriorityQ()
{   
    delete[] heapArr; // deallocates the memory so that there is no memory leak 
}

/*
Finds the parent of a node, given its index.
*/
int PriorityQ::parent(int index)
{
    return (index - 1)/2;  // this is the formula for the parent index 
}

/*
Returns the left child of a node.
*/
int PriorityQ::leftChild(int index)
{
    return 2 * (index + 1); // formula for left child  
}

/*
Returns the right child of a node.
*/
int PriorityQ::rightChild(int index)
{
    return 2 * (index + 2); // formula for right child
}

void PriorityQ::peek() 
{
    if(isEmpty())
    {
        cout << "no record found" << endl;
    }
    else
    {
        ReviewInfo rw = heapArr[0]; // this defines rw to be the top of the priority queue
        cout << "Restaurant: " << rw.restaurantName << endl;
        cout << "Customer: " << rw.customer << endl;
        cout << "Review: " << rw.review << endl;
        cout << "Time: " << rw.time << endl;
    }

}

void PriorityQ::heapify(int i)
{
    int parentVal = parent(i); // sets the first/initial index (parent) to the current node 
    while((parentVal != i) && (heapArr[i].time > heapArr[parentVal].time)) // this loop will happen only if the current index is equal to the parent index or if the current index has a higher priority
    {
        swap(&heapArr[i], &heapArr[parentVal]); // swap the current node with the parent node since it has a higher priority 
        i = parentVal; // updating the current index we have to the parent index
        parentVal = parent(i); // this will get the parent index of the updated node 
    }
}

void PriorityQ::insertElement(ReviewInfo restaurant)
{
    if (currentSize == capacity)
    {
        cout << "Maximum heap size is reached. Cannot insert anymore." << endl;
    }
    else 
    {
        heapArr[currentSize] = restaurant; // if the max heap size hasn't reached then the new restaurant is inserted into the current size index 
        heapify(currentSize); // this performs the heapify so that the max heap is maintained 
        currentSize++; // increments the current size since it was added to the heap 
    }
}

/*
Prints the elements in the heap
*/
void PriorityQ::print()
{
    if (isEmpty()) // checks if that record exists and if it does not then it prints the below statement 
    {
        cout << "no record found" << endl;
        return;
    }
    else
    {
        for (int i = 0; i < currentSize; i++) // to print the reviews
        {
            cout << "\t" << "Customer: " << heapArr[i].customer << endl;
            cout << "\t" << "Review: " << heapArr[i].review << endl;
            cout << "\t" << "Time: " << heapArr[i].time << endl;
            cout << "\t" << "=====" << endl;
        } 
    }
}

// Method to remove minimum element (or root) from min heap
void PriorityQ::pop()
{
    if (isEmpty()) // check if the heap is empty 
    {
        cout << "no record found" << endl; // prints if empty 
    }

    if(currentSize == 1) // if the current seize is 1 then we decrement the size 
    {
        currentSize--; 
        return; 
    }
    swap(heapArr[0], heapArr[currentSize-1]); // swap root (this is the highest since max heap and has the highest priority) with last element in the heap 
    currentSize--; 

    int biggest_value = 0;  
    int current = 0; 

    while(biggest_value < currentSize) // this is the heapify for the pop after the element is removed 
    {
        int right_child = rightChild(biggest_value); 
        int left_child = leftChild(biggest_value); 
    
        // this will compae the left child with the highest value 
        if ((left_child < currentSize) && (heapArr[left_child].time > heapArr[biggest_value].time))
        {
            biggest_value = left_child;
        }

        // compares the right child with the highest value
        if ((right_child < currentSize) && (heapArr[right_child].time > heapArr[biggest_value].time))
        {
            biggest_value = right_child;
        }

        // swaps the current element with the highest value 
        if (biggest_value != current) 
        {
            swap(&heapArr[current], &heapArr[biggest_value]);
            current = biggest_value; 
        }
        else 
        {
            break; // no swap then breaks 
        } 
    }
}
