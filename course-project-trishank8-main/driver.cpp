#include <iostream>
#include "hash.hpp"
#include "PriorityQueue.hpp"
#include <vector>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <chrono>

using namespace std;
using namespace std::chrono;

void displayMenu() // do not modify
{
    cout << "------------------" << endl;
    cout << "1: Build the data structure (execute this option one time)" << endl;
    cout << "2: Add a review" << endl;
    cout << "3: Retrieve most recent review for a restaurant" << endl;
    cout << "4: Pop most recent review for a restaurant" << endl;
    cout << "5: Print reviews for a restaurant" << endl;
    cout << "6: Display number of collisions" << endl;
    cout << "7: Display table results" << endl;
    cout << "8: Exit" << endl;
    cout << "------------------" << endl;
}

int main(int argc, char* argv[])
{
    if (argc <3)
    {
        cout<<"need correct number of arguments"<<endl;
    }
	
    string fname = argv[1];
    int tableSize = stoi(argv[2]);
    int ch = 0;
    bool built = false;
    string chs;
    HashTable ht(5);
	
    while(ch!=8)
    {
        displayMenu();
        cout << "Enter your choice >>";
        getline(cin, chs);
        ch = stoi(chs);
        switch (ch)
        {
            case 1:
			{
                
				// checking and creating a data structure if not built 
                if(!built) 
                {
                    ht.setup(fname);
                    built = true;
                    cout << "Data structure build successfully." << endl;
                    //built++;
                    break;
                }
                else 
                {
                    cout << "The data structure has already been built." << endl;
                }
				break;
            }
            case 2:
			{
                // this can add a review and will insert it into the hash table 
                string restaurantName; 
                string customer; 
                string review; 
                int time; 
                string time_string; 

                cout << "Restaurant name: " ; 
                getline(cin, restaurantName);

                cout << "Customer: "; 
                getline(cin, customer);

                cout << "Review: "; 
                getline(cin, review);

                cout << "Time: "; 
                getline(cin, time_string);  
        
                time = stoi(time_string); 
                ReviewInfo newReview{restaurantName, customer, review, time}; 
                ht.insertItem(newReview); // inserts into the hash table 
				break;
            }
            case 3:
			{
                // this will get the most recent review for a restaurant 
                string restaurantName;
                cout << "Restaurant name: ";
                getline(cin, restaurantName);
                node *restaurantNode = ht.searchItem(restaurantName); // searches for the restaurant 

                if(restaurantNode != nullptr)
                {
                    restaurantNode->pq.peek();
                }
                else
                {
                    cout << "no record found" << endl;
                }
				break;
            }
            case 4:
			{
                //pop most recent review for a restaurant (so largest element)
                string restaurantName;
                cout << "Restaurant Name: ";
                getline(cin, restaurantName);
                node *restaurantNode = ht.searchItem(restaurantName);
                if (restaurantNode != NULL)
                {
                    restaurantNode->pq.pop(); // pops the element using the pop function
                }
                else
                {
                    cout << "no record found" << endl; 
                }
				break;
            }
            case 5:
			{
				// ask for restaurant name, read then search for it -> if found then print it from the pq
                string restaurantName;
                cout << "Restaurant Name: "; 
                getline(cin, restaurantName);
                node *restaurantNode = ht.searchItem(restaurantName);

                if(restaurantNode != nullptr)
                {
                    restaurantNode->pq.print(); // accesing the priority queue with the restaurant in restaurantNode which is the input value (the value/thing we input to ) 
                }
                else 
                {
                    cout << "no record found" << endl; // if there is no record found
                }
				break;
			}
            case 6:
                // displays the number of collisions
                cout << "Number of collisions: " << ht.getNumCollision() << endl;
                break;
            case 7:
                // displays the table result sby calling displayTable 
                ht.displayTable();
                break;
            case 8:
				break;
            default:
                cout << "Enter a valid option." << endl;
                break;
        }
    }
}
