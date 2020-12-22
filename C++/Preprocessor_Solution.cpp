/* Enter your macros here */
#define INF 100000001
#define FUNCTION(f, op) void f(int& x, int v){ if ( v op x ) x = v; }
#define io(v) cin >> v
#define toStr(x) #x
#define foreach(v, i) for(int i=0; i<v.size(); i++)
#include <iostream>
#include <vector>
using namespace std;
/*
 *
 * Aman Upadhyay
 * Amity University Kolkata
 *  
*/
#if !defined toStr || !defined io || !defined FUNCTION || !defined INF
#error Missing preprocessor definitions
#endif 

FUNCTION(minimum, <)
FUNCTION(maximum, >)

int main(){
	int n; cin >> n;
	vector<int> v(n);
	foreach(v, i) {
		io(v)[i];
	}
	int mn = INF;
	int mx = -INF;
	foreach(v, i) {
		minimum(mn, v[i]);
		maximum(mx, v[i]);
	}
	int ans = mx - mn;
	cout << toStr(Result =) <<' '<< ans;
	return 0;

}