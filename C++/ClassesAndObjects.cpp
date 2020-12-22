/* https://www.hackerrank.com/challenges/classes-objects/problem */

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cassert>
using namespace std;
/**
 * 
 * Aman Upadhyay
 * Amity University Kolkata
 * 
*/
class Student
{
private:
    int scores[5];
    int sum;
public:
    void input(){
        sum = 0;
        for(int& score : scores){
            cin >> score;
            sum += score;
        }
    }
    int calculateTotalScore()
    {
        return sum;
    }
};
int main()
{
    int n;
    cin >> n;
    Student *s = new Student[n];

    for (int i = 0; i < n; i++)
    {
        s[i].input();
    }
    int kristen_score = s[0].calculateTotalScore();

    int count = 0;
    for (int i = 1; i < n; i++)
    {
        int total = s[i].calculateTotalScore();
        if(total > kristen_score)
        {
            count++;
        }
    }
    cout << count;
    return 0;
}

