/* https://www.hackerrank.com/challenges/c-tutorial-for-loop/problem */

#include <iostream>
#include <cstdio>
using namespace std;
/*
 * 
 * Aman Upadhyay
 * Amity University Kolkata
 * 
*/
int main() {
    
    int num1, num2;
    cin >> num1 >> num2;

    string arr[9] = {"one","two","three","four","five","six","seven","eight","nine"};

    for(int i = num1; i <= num2; i++)
    {
        if(i<=9)
        {
            cout << arr[i-1] << endl;
        }
        else
        {
            if(i%2==0)
            {
                cout << "even" << endl;
            }
            else
            {
                cout << "odd" << endl;
            }
        }
    }
    return 0;
}
