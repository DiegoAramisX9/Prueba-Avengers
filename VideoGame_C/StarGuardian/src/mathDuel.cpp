#include <iostream>
#include <cstdlib>
#include <ctime>
#include "mathDuel.h"

using namespace std; 

bool MathDuel()
{
    int correctAnswers = 0;
    
    cout<<"Welcome to Math Duel"<<endl;
    cout<<"You hace to solve the following mathematical exercises.."<<endl;
    cout << "Solve at least 3 out of 5 to win!" << endl;

    for(int i = 0; i <= 5; i++)
    {
         int num1 = rand() % 10 + 1;
         int num2 = rand() % 10 + 1; 
         
         int operation = rand() % 3;

         int result;
         char symbol;

         switch (operation) {
            case 0:
                result = num1 + num2;
                symbol = '+';
                break;
            case 1:
                result = num1 - num2;
                symbol = '-';
                break;
            case 2:
                result = num1 * num2;
                symbol = '*';
                break;
        }

        cout << "Question " << i << ": " << num1 << " " << symbol << " " << num2 << " = ";
        int answer;
        cin >> answer;

        if(answer == result)
        {
            cout<<"Correct!"<<endl;
            correctAnswers++; 
        }else {
            cout << "Wrong. The correct answer was " << result << ".\n";
        }

    }
    cout << "\nYou got " << correctAnswers << " out of 5 right." << endl;

    if(correctAnswers > 3)
    {
        cout << "You win the math duel!" << endl;
        return true;
    }else {
        cout << "You lost the math duel..." << endl;
        return false;
    }

}