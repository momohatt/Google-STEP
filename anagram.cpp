#include<algorithm>
#include<iostream>
#include<string>
#include<fstream> //ifstream, ofstream
using namespace std;

bool see_if_included(string, string);
int score(string);

int n=72412;
int m=16; //16
string str[16];//input //16
string str_sorted;
string dict[72412];//72412(the number of words in the dict)
string dict_sorted[72412];//72412

int main(){
	
	//input&sort
	for(int i=0;i<m;++i){
		cin>>str[i];
	}
	sort(str,str+m);
	for(int i=0;i<m;++i){
		str_sorted+=str[i];
	}

	//cout<<str_sorted<<endl;

	//load dictionary
	ifstream reading_file("dict.txt", ios::in);
	
	if(reading_file.fail()){
		cout<<"File does not exist."<<endl;
		exit(0);
	}

	int i=0;
	while(!reading_file.eof()){
		getline(reading_file, dict[i]);
		int length=dict[i].length();

		if(length>m) continue;

		string letters[16];

		transform(dict[i].begin(), dict[i].end(), dict[i].begin(), ::tolower);
		for(int j=0;j<length;++j){
			letters[j]=dict[i].substr(j,1);
		}

		sort(letters, letters+length);

		for(int j=0;j<length;++j){
			dict_sorted[i]+=letters[j];
		}

		//cout<<"the end"<<endl;
		//cout<<i+1<<" "<<dict_sorted[i]<<" "<<dict[i]<<endl;
		++i;
	}

	//search phase&output

	int highest_score=0;
	int memory; //indicate which word scores most
	for(int i=0;i<n;++i){ //for all the words in dict

		//cout<<"In the searching phase"<<endl;
		//cout<<dict_sorted[i]<<endl;
		if(dict_sorted[i].empty()) continue;

		if(see_if_included(dict_sorted[i], str_sorted)){
			if(score(dict_sorted[i])>highest_score){
				highest_score=score(dict_sorted[i]);
				memory=i;
			}
		}
	}

	cout<<"Answer: "<<dict[memory]<<endl;

	return 0;
}

int score(string word)
{
   	string letter[26]={"a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z"};
    	int point[26]={1,1,2,1,1,2,1,2,1,3,3,2,2,1,1,2,3,1,1,1,1,2,2,3,2,3};
    	int score=0;
	int l=word.length();

    	for(int i=0;i<l;++i){
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


bool see_if_included(string word, string str)
{
    	int l=word.length();
    	int counter=0;
    	string str_prsv=str;//preserve
        
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
        	}	
    	}
        
    	//str=str_prsv; //to restore not necessary?
        
    	if(counter==l){
        	return true;
    	} else {
        	return false;
    	}
        
}
