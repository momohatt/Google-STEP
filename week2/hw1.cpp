#include<iostream>
#include<vector>
#include<string>
using namespace std;

int time();

int main (void)
{
    int n;
    cout<<"配列の大きさを入力：";
    cin>>n;
    vector< vector<int> > a,b,c;
    a=b=c=vector< vector<int> >(n, vector<int>(n));

    //input
    cout<<"配列Aの要素を入力："<<endl;
    for(int i=0;i<n;++i){
        for(int j=0;j<n;++j){
            cin>>a[i][j];
        }
    }

    cout<<"配列Bの要素を入力："<<endl;
    for(int i=0;i<n;++i){
        for(int j=0;j<n;++j){
            cin>>b[i][j];
        }
    }

    //計算
    for(int i=0;i<n;++i){
        for(int j=0;j<n;++j){
            c[i][j]=0;
            for(int k=0;k<n;++k){
                c[i][j]+=a[i][k]*b[k][j];
            }
        }
    }

    //output
    cout<<"配列AB="<<endl;
    for(int i=0;i<n;++i){
        for(int j=0;j<n;++j){
            cout<<c[i][j]<<" ";
        }
        cout<<endl;
    }

    cout<<"計算時間"<<endl;

    return 0;

}

