/* https://www.hackerrank.com/challenges/variable-sized-arrays */

#include <iostream>
using namespace std;
/*
 * 
 * Aman Upadhyay
 * Amity University Kolkata
 *  
*/
int main(int argc, char *argv[]) 
{
    int n;
    int q;
    cin >> n >> q;
    int** outer = new int*[n];
    for(int i = 0; i < n; i++) {
        int k;
        cin >> k;
        outer[i] = new int[k];
        for(int j = 0; j < k; j++) {
            cin >> outer[i][j];
        }
    }
    while(q-- > 0) {
        int outer_index;
        int inner_index;
        cin >> outer_index >> inner_index;        
        cout << outer[outer_index][inner_index] << endl;
    }
    return 0;
}