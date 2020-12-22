/* https://www.hackerrank.com/challenges/c-tutorial-strings/problem */

#include <iostream>
#include <string>
using namespace std;
/*
 *
 *  Aman Upadhyay
 *  Amity Kolkata University
 *  
*/
int main()
{
    string a, b;
    char Temp;
    cin >> a >> b;
    cout << a.size();
    cout << " ";
    cout << b.size();
    cout << "\n";
    cout << a << b;
    Temp = a[0];
    a[0] = b[0];
    b[0] = Temp;
    cout << "\n" << a << " " << b;
    return 0;
}