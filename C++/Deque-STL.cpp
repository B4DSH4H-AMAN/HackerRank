#include<bits/stdc++.h>
using namespace std;
/*
 *
 * Aman Upadhyay
 * Amity University Kolkata
 *  
*/
int main(){

  int t;
  cin >> t;
  while(t--){
       int n , k , x ;
       cin >> n >> k ;

       vector<int> vec;
       for(int i =  0 ; i < n ; ++i ){
          cin >> x;
          vec.push_back(x);
       }
        int mx = 0;
        vector<int> nval;
       for(int i =  0 ; i < n ; ++i ){

                  if(i%k == 0)
                   mx = vec[i];
                else
                mx = max( mx , vec[i] );
                nval.push_back(mx);
       }
       mx = 0;
       vector<int> val;
       for(int i = n-1 ; i >= 0 ; --i ){
             if(i%k == (k-1))
               mx = vec[i];
               else
               mx = max( mx , vec[i]);
               val.push_back(mx);

       }
       for(int i = 0 ; i < vec.size()-k+1  ; ++i )
             cout << max( nval[i+k-1] , val[val.size()-i-1]) <<" ";
             cout << endl;
             }
             return 0;

}
