// CPP program to implement hashing with chaining
#include <iostream>
#include "hash.hpp"
#include <sstream>
using namespace std;

node* HashTable::createNode(string restaurantName, node* next)
{
    node *newNode = new node{restaurantName, PriorityQ(50), next};
    return newNode;
}


HashTable::HashTable(int bsize)
{
    numCollision = 0;
    tableSize = bsize;
    table = new node*[tableSize]; 
    for (int i = 0; i < tableSize; i++)
    {
        table[i] = nullptr; 
    } 
}


HashTable::~HashTable() // destructor
{
    for (int i = 0; i < tableSize; i++) // loops through the buckets in the hash table
    {
        node *temp = table[i]; // this gets the first item/head of the linked list in the bucket that we are currently on
        while (temp != nullptr)
        {
            node *prev = temp; // thi will keep track of the previous node
            temp = temp->next; // this will move to the next node
            delete prev; // delete the current node since we moved from our current to new so our current is now previous 

        }
    }
    delete[] table; // this will deallocate memory for the array of the pointers
}


void HashTable::displayTable()
{
    for (int i = 0; i < tableSize; i++)
    {
        cout << i << "|";
        node *temp = table[i];
        while (temp != nullptr)
        {
            cout << temp->restaurantName << "-->";
            temp = temp->next;
        }
        cout << "NULL" << endl;
    }
}


unsigned int HashTable::hashFunction(string restaurantName) // gets the hashValue/ the bucket to put the value in 
{
    unsigned int hashValue = 0; // we will initialize the hash value to 0
    for (int i = 0; i < restaurantName.length(); i++)
    {
        char c = restaurantName[i]; // gets the char that is at the ith index
        hashValue += c; // this will add the ascii value of the char to the hash value so that it can mod 
    }
    unsigned int index = hashValue % tableSize; // this will calculate the index for the bucket -> used unsigned int since we cannot get negative, etc and it is used in this function -> lowkey do not ask me 
    return index; // returns the computed index for the bucket 
}


node* HashTable::searchItem(string restaurantName)
{
    int index; 
    index = hashFunction(restaurantName); // this has to be done so we can cal the hash value and get the index of the bucket 
    //cout << "entered search hash function" << endl; 
    node *curr_node = table[index];  // gets the first/head of the linked list in the bucket 
    while(curr_node != nullptr)
    {
        if (curr_node->restaurantName == restaurantName) // checks to see if the current restaurantName == the target retaurantName we want 
        {
            return curr_node; // only if they match then the current node is returned 
        }
        curr_node = curr_node->next; // it now will move to the next node in the linked list so it can keep moving
    }
    return nullptr; // if the retaurant is not found at all then we will just return nullptr
}


void HashTable::insertItem(ReviewInfo restaurant)
{

    int index; 
    index = hashFunction(restaurant.restaurantName); 
    node *restaurant_new = searchItem(restaurant.restaurantName); 
    if(restaurant_new == nullptr)
    {
        node *head = table[index];  
        node *currentInsert = createNode(restaurant.restaurantName, head); // creates new node to store the restaurant
        currentInsert->pq.insertElement(restaurant); // inserts info of review into pq of node 
        if(head == nullptr) // if this then update table with new node 
        {
            table[index] = currentInsert; // if bucket is empty the assign new node as the head
        }
        else 
        {
            numCollision++; // if there is a collision then the collision counter is incremented 
            table[index] = currentInsert; // then the head is updated 
        }
    }
    else 
    {
        restaurant_new->pq.insertElement(restaurant); // this will insert into the pq if the restaurant already exists 
    }
}


void HashTable::setup(string fname)
{
    ifstream file;
    file.open(fname); 
    string line; 
    string time_string; 

    while(getline(file,line))
    {
        ReviewInfo restaurant; // create review info object so that is stores restaurant info 
        stringstream ss(line); 
        getline(ss, restaurant.restaurantName,';'); 
        getline(ss, restaurant.review,';'); 
        getline(ss, restaurant.customer,';'); 
        getline(ss,time_string,';');
        restaurant.time = stoi(time_string); // converts time string into int 
        insertItem(restaurant); // inserts restaurant info into the hash table 
    }   
}