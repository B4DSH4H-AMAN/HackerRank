#include <bits/stdc++.h>
using namespace std;
/*
 *
 * Aman Upadhyay
 * Amity University Kolkata
 *  
*/
int main() {
    set<long long> s;
    set<long long>::iterator it;
    long long q,x;
    int qt;
    cin>>q;
    while(q--){
        cin>>qt>>x;
        switch(qt){
            case 1:s.insert(x);
                    break;
            case 2:s.erase(x);
                    break;
            case 3:it=s.find(x);
                    if(it==s.end())
                        cout<<"No"<<endl;
                    else
                        cout<<"Yes"<<endl;
                    break;
        }
    }
    return 0;
}
