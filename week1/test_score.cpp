#include<iostream>
#include<string>
using namespace std;

int score(string word)
{
    string letter[26]={"a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z"};
    int point[26]={1,1,2,1,1,2,1,2,1,3,3,2,2,1,1,2,3,1,1,1,1,2,2,3,2,3};
    int score=0;
    
    for(int i=0;i<16;++i){
        for(int j=0;j<26;++j){
            if(word.substr(i,1)==letter[j]){
                score+=point[j];
                break;
            }
        }
    }
    
    ++score;
    score=score*score;
    
    return score;
}

int main(void)
{
	string word;
	cin>>word;
	cout<<score(word)<<endl;
	return 0;
}
