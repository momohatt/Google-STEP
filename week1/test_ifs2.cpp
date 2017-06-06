#include<iostream>
#include<string>
#include<fstream>
#include<sstream> //istringstream
using namespace std;

int main()
{
	//string filename=argv[1];
	
	ifstream reading_file("minidict.txt", ios::in);

	string reading_line_buffer;

	cout<<"reading"<<"minidict.txt"<<"..."<<endl;

	while(!reading_file.eof()){
		getline(reading_file, reading_line_buffer);
		cout<<reading_line_buffer<<endl;

		const char delimiter=' ';
		string separated_string_buffer;
		istringstream line_separater(reading_line_buffer); //?
		getline(line_separater, separated_string_buffer);

		cout<<separated_string_buffer<<endl;
	}

	return 0;
}
