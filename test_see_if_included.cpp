#include<iostream>
#include<string>
using namespace std;

int m=16;

bool see_if_included(string word, string str)
{
    int l=word.length();
    int counter=0;
    //string str_prsv=str;//preserve
    
    for(int i=0;i<l;++i){ //for all the letters in the word
        //int num=0;//=0(if no matching) or =1(matched)
        
        for(int j=0;j<m;++j){ //for all the letters in the str
            if(word.substr(i,1)==str.substr(j,1)){
                str.replace(j,1, "0"); //replace it with non-alphabet
		//cout<<"current str: "<<str<<endl;
                //num=1;
		//cout<<num<<endl;
		++counter;
		//cout<<str<<" "<<str_prsv.substr(j,1)<<" "<<counter<<endl;
                break;
            }
	    //cout<<"hi!"<<endl;
        }
    }
    
    //str=str_prsv; //to restore not necessary?
    
    if(counter==l){
	return true;
    } else {
	    return false;
    }
    
}

int main()
{
	string word, str;
	cin>>word>>str;
	
	if(see_if_included(word,str)){
		cout<<"Included!!"<<endl;
	} else {
		cout<<"Not included."<<endl;
	}

	return 0;
}
