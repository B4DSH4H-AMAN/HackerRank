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

  vector<int> vecNumbers(count);

  int i = 0;
  int temp;
  while (i < count)
  {
    cin >> temp;
    vecNumbers[i] = temp;
    i++;
  }
    
    int indextodelete;
    cin >> indextodelete;
    
    vecNumbers.erase(vecNumbers.begin() + (indextodelete - 1));
    
    int start, end;
    
    cin >> start >> end;
    
    start--;
    end--;
    
    vecNumbers.erase (vecNumbers.begin() + start, vecNumbers.begin() + end);
    
    cout << vecNumbers.size() << endl;
    
    auto Itr = vecNumbers.begin();
    while (Itr != vecNumbers.end())
    {
        cout << *Itr << " ";
        Itr++;
    }        
    
    return 0;
}
