#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_set>
using namespace std;
/*
 *
 * Aman Upadhyay
 * Amity University Kolkata
 *  
*/
unordered_set<long long> all;
int main() {

    long long n, s, p, q, M = (((long long) 1) << 31) - 1;
    scanf("%lld%lld%lld%lld", &n, &s, &p, &q);
    all.insert(s);
    if ((p & 1) == 0) {
        for (int i = 1; i < n; ++i) {
            s = (s * p + q) & M;
            if (all.find(s) != all.end()) {
                break;
            }
            all.insert(s);
            
        }
        printf("%d\n", (int) all.size());
    }
    else {
        long long t;
        if (p == 1) {
            for (t = q; (t & 1) == 0; t >>= 1)
            ;
            t <<= 31;
        }
        else {
            long long pp = p, qq = q;
            for (t = 1; t < n; t <<= 1) {
                if (s == ((s * pp + qq) & M)) {
                    break;
                }
                qq = ((pp + 1) * qq) & M;
                pp = (pp * pp) & M;
            }
        }
        printf("%lld\n", (t < n)?t : n);
    }
   
    return 0;
}
