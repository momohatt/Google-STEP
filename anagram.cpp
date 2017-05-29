#include<algorithm>
#include<iostream>
#include<string>
#include<fstream> //ifstream, ofstream
using namespace std;

int n=72412;
int m=16; //16
string str[16];//input //16
string str_sorted;
string dict[72412];//72412
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

	/* //I think I made a mistake here so decided to discard it
	while(!reading_file.eof()){
		for(int i=0;i<n;++i){
			getline(reading_file, dict[i]);
			int length=dict[i].length(); //length of the word
			//cout<<dict[i]<<" "<<dict[i].length()<<endl;
			if(length>16) continue;
			string letters[16]; //ex) apple -> a p p l e

			for(int j=0;j<length;++j){
				letters[j]=dict[i].substr(j,1);
				//cout<<letters[j]<<" ";
			}
			//cout<<endl;

			sort(letters, letters+length);

			for(int j=0;j<length;++j){
				dict_sorted[i]+=letters[j];
			}

			cout<<"End of the while sentence"<<endl;
			cout<<dict_sorted[i]<<endl;
		}
	}*/

	int i=0;
	while(!reading_file.eof()){
		getline(reading_file, dict[i]);
		int length=dict[i].length();
		if(length>m){
			//cout<<dict[i]<<endl;
			continue;
		}
		string letters[16];

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

	//try 2^16 cases

	//search phase&output
	for(int k=0;k<n;++k){
		//cout<<"In the searching phase"<<endl;
		//cout<<dict_sorted[k]<<endl;
		if(dict_sorted[k]==str_sorted){
			cout<<"Answer: "<<dict[k]<<endl;
		}
	}

	return 0;
}
