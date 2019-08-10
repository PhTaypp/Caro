#include<iostream>
using namespace std ;
long solve(int n){

    long i = 1 ;
    long value = 0;
    long ans = 0;
    while(1){
        if(value+i == n){
            break;
        }
        if(value+i > n ){
            i = 1;
            //ans++;

            continue ;
        }
        if(value+i < n){
            ans++;

            value+=i;

            i++;

        }
    }
    return ans+1;
}
int STT = 1 ;
int main()
{
    int test; cin >> test ;
    while(test--){
        int l , r ; cin >> l >> r ;
        int max = 0 ;
        for(long i = l ; i<= r ; i++ ){
            if(max < solve(i)){
                max = solve(i);
            }
        }
        cout <<"Case #"<< STT << endl;
        cout << max << endl;
        STT++;
    }
}
