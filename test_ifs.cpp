#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main() {

	//ifstreamの場合
	cout << "ifstream" << endl;

	ifstream ifs("data.txt");
	string str;
	if(ifs.fail()) {
		cerr << "File do not exist.\n";
		exit(0);
	}

	int a=0, b=0, c=0;

	while(getline(ifs, str)) {
		a=0; b=0; c=0;
		sscanf(str.data(), "%d,%d,%d", &a, &b, &c);
		cout << "a = " << a << endl;
		cout << "b = " << b << endl;
		cout << "c = " << c << endl;
		cout << "a+b+c = " << a+b+c << endl;
	}
	return 0;
}
