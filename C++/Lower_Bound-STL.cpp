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
    int n;
    vector<int> data;
    cin >> n;
    while (n--) {
        int x;
        cin >> x;
        data.push_back(x);
    }
    
    cin >> n;
    while (n--) {
        int x;
        cin >> x;
        int index = lower_bound (data.begin(), data.end(), x) - data.begin();
        if (data[index] == x)
            cout << "Yes ";
        else
            cout << "No ";
        
        cout << index + 1 << endl;
    }
    return 0;
}
