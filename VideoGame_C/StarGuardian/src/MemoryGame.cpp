#include <iostream>
#include "MemoryGame.h"
#include <vector>
#include <random>    // for random_device
#include <chrono>    // for seeding
#include <algorithm> // for shuffle

using namespace std;

bool memoryGame()
{
   cout<<"== This is the Memory Game =="<<endl;
   
   cout << "Match at least one pair in 3 tries to win!" << endl;

   //prepare card pairs
   vector<int> cards {1,1,2,2,3,3};

    // Shuffle cards
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    shuffle(cards.begin(), cards.end(), default_random_engine(seed));

    //track revealed cards 
    vector<bool> revealed(6, false);
    int tries = 3;
    int pairsFound = 0;

    while(tries > 0)
    {
        // Show card positions
        cout << "\nCards: ";
        for(int i = 0; i < 6; ++i)
        {
            if(revealed[i])
            {
               cout<<"["<<cards[i] << "] ";
            }else 
            {
                cout<< "["<< i + 1<< "] ";
            }
        }
        cout<<endl; 

        int pos1, pos2;
        cout<<"Choose two different cards (1-6): ";
        cin >> pos1 >> pos2;

        // Convert to 0-based index
         pos1--; pos2--;

        if(pos1 == pos2 || pos1 < 0 || pos1 >= 6 || pos2 < 0 || pos2 >= 6 || revealed[pos1] || revealed[pos2])
        {
             cout<<"Invalid positions, try again." << endl;
             continue; 
        }

        if(cards[pos1] == cards[pos2])
        { 
            cout<<"Its a match!!!" << endl;
            revealed[pos1] = true;
            revealed[pos2] = true;
            pairsFound++;
        }else
        {
            cout<<"Not a match" << endl;
        }

        tries--; 
    }
    cout << "\nTotal pairs found: " << pairsFound << endl;
    return pairsFound >= 1;
}