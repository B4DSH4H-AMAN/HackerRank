/* https://www.hackerrank.com/challenges/c-tutorial-stringstream/problem */

#include <sstream>
#include <vector>
#include <iostream>
using namespace std;
/*
 * 
 * Aman Upadhyay
 * Amity University Kolkata
 *  
*/
vector<int> parseInts(string str){
   stringstream s(str);
   vector <int> a;
   char ch;
   int t;
   while(s>>t)
  { a.push_back(t);
  s>>ch;}
  return a;
}
int main() {
    string str;
    cin >> str;
    vector<int> integers = parseInts(str);
    for(int i = 0; i < integers.size(); i++) {
        cout << integers[i] << "\n";
    }
    
    return 0;
}
