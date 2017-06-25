#include<iostream>
#include<vector>
#include<string>
#include<time.h> //for clock()
using namespace std;

int time();

int main (void)
{
    int n;
    for(n=0;n<100;++n){
        vector< vector<int> > a,b,c;
        a=b=c=vector< vector<int> >(n, vector<int>(n));

        for(int i=0;i<n;++i){
            for(int j=0;j<n;++j){
                a[i][j]=1;
            }
        }

        for(int i=0;i<n;++i){
            for(int j=0;j<n;++j){
                b[i][j]=1;
            }
        }

        clock_t start=clock();

        //計算
        for(int i=0;i<n;++i){
            for(int j=0;j<n;++j){
                c[i][j]=0;
                for(int k=0;k<n;++k){
                    c[i][j]+=a[i][k]*b[k][j];
                }
            }
        }

        clock_t end=clock();

        cout<<n<<"    "<<(double)(end-start)<<endl;
    }

    return 0;

}

