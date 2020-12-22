#include <iostream>
#include <iomanip> 
using namespace std;
/*
 *
 * Aman Upadhyay
 * Amity University Kolkata
 *  
*/
int main() {
	int T; cin >> T;
	cout << setiosflags(ios::uppercase);
	cout << setw(0xf) << internal;
	while(T--) {
		double A; cin >> A;
		double B; cin >> B;
		double C; cin >> C;

        printf("0x%llx\n",(long long int)A);

        char q[100];
        sprintf(q,"%+.2lf",B);
        int i=0; while (q[i]!=0) i++;
        while (i<15) {printf("_");i++;}
        printf("%s\n",q);
        printf("%.9lE\n",C);
	}
	return 0;

}