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
    int count = 0;
    
    cin >> count;
    
    std::vector<int> v;
    
    int value = 0;
    
    for(int i = 0; i < count; i++)
    {
        cin >> value;
        v.push_back(value);
    }
    
    sort(v.begin(), v.end());
    
    bool first = true;
    
    std::vector<int>::const_iterator it = v.begin();
    std::vector<int>::const_iterator end = v.end();
    
    for(; it != end; ++it)
    {
        if(!first)
        {
            cout << " ";
        }
        
        cout << *it;
        
        first = false;
    }
        
    return 0;
}
