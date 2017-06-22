#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<map>

#define NODE_NUM 1483277
#define EDGE_NUM 52973671

using namespace std;

map<string, int> titles;
vector<int> adjacencyList[NODE_NUM];

void readPages(string fileName)
{
    int id;
    string name;

    ifstream ips(fileName);
    if (ips.fail())
        perror("couldn't open the page file");
    while (!ips.eof()) {
        ips >> id >> name;
        titles[name] = id;
    }
    cout<<"readPages finished"<<endl;
    return;
}

void readLinks(string fileName)
{
    int from, to;

    ifstream ifs(fileName);
    if(ifs.fail())
        perror("couldn't open the link file");
    while (!ifs.eof()) {
        ifs >> from >> to;
        adjacencyList[from].push_back(to);
    }
    cout<<"readLinks finished"<<endl;
    
    return;
}

bool confirmAdjacency(string from, string to)
{
    int from_id = titles[from];
    int to_id = titles[to];
    cout<<from_id<<" "<<to_id<<endl;
    for (int i = 0; i < adjacencyList[from_id].size(); ++i){
        if (adjacencyList[from_id][i] == to_id)
            return true;
    }
    return false;
}

int main()
{
    readPages("mutualPage_data.txt");
    readLinks("mutualLink_data.txt");
    
    string from, to;
    for(;;){
        cout << "出発点と到達点を入力: ";
        cin >> from >> to;
        if (confirmAdjacency(from, to)){
            cout<<"Adjacency confirmed!"<<endl;
        } else {
            cout<<"Not adjacent"<<endl;
        }
    }

    return 0;
}
