/* https://www.hackerrank.com/challenges/arrays-introduction/problem */

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
/*
 * 
 * Aman Upadhyay
 * Amity University Kolkata
 *  
*/
int main() {
    int n, arr[10000];
    cin >> n;
    for(int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
    for(int i = n-1; i >= 0; i--)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
    return 0;
}
