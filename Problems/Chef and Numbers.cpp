/*
Author: Pritam Pathak
https://github.com/Priprocks
*/
#include<iostream> //For standard i/o stream
#define ll long long
#define ull unsigned long long
#define ld long double
#define pii pair <int, int>
#define mp make_pair
using namespace std; //Pulling everything defined in the std namespace into the global namespace


int main()
{
    /*
        N= Integer range (1 to N)
        K= Number of allowed integers
        Q= Number of queries.
    */
    int N,K,Q;
    cin>>N>>K>>Q;

    int F_array[K]; //Stores K distinct integers in the range 1 to N
    for(int i=0;i<K;i++)
        cin>>F_array[i];
    /*
        This forms the polynomial of the form:
        a0+ a1*x + a2*x^2 + .... + a(k-1)*x^(k-1)=y
        y is given in each query and we have to figure out x.
    */
    return 0;
}
