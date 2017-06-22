#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<algorithm>

#define NEW_MAX_V 763995 //num of nodes
#define OLD_MAX_V 1483277

using namespace std;

string newNodesTitle[NEW_MAX_V]; //新番号とページタイトルの対応表
int renumberingTable[OLD_MAX_V]; //再ナンバリングしていく時の旧番号と新番号の対応表，renumberingTable[old_number] = new_number
//map<int, string> newNodesTable; //新番号とページタイトルの対応表
vector<int> adjacencyList[NEW_MAX_V]; //新番号により登録する

int max_size = 0; //maximum size of a clique
vector<int> maxCliqueComponent;

void readPages(string fileName)
{
    int indx = 0; //これが新番号になる
    int id;
    string name;

    ifstream ips(fileName);
    if (ips.fail())
        perror("couldn't open the page file");
    while (!ips.eof()) {
        ips >> id >> name;
        newNodesTitle[indx] = name;
        renumberingTable[id] = indx;
        indx++;
        //cout<<"new id:"<<indx<<" old id:"<<id<<" name:"<<name<<endl;
    }

    cout<<"readPages finished"<<endl;
    return;
}

void readLinks(string fileName)
{
    int id1, id2;
    int newID1, newID2;

    ifstream ifs(fileName);
    if(ifs.fail())
        perror("couldn't open the link file");
    while (!ifs.eof()) {
        ifs >> id1 >> id2;
        //cout<<"id1:"<<id1<<" id2:"<<id2<<endl;
        newID1 = renumberingTable[id1];
        newID2 = renumberingTable[id2];
        //cout<<"newID1:"<<newID1<<" newID2:"<<newID2<<endl;
        adjacencyList[newID1].push_back(newID2);
        adjacencyList[newID2].push_back(newID1);
        //注：隣接リストは番号が若い順に並ぶはず
    }
    cout<<"readLinks finished"<<endl;
    
    //for(int i = 0;i < 8; ++i){
    //    cout<<i<<": ";
    //    for (int j = 0; j < adjacencyList[i].size(); ++j){
    //        cout<<adjacencyList[i][j];
    //    }
    //    cout<<endl;
    //} 

    return;
}

vector<int> defineCommonAdjacentNodes(const vector<int>& U, int v)
{
    vector<int> commonAdjacentNodes;
    for (int i = 0; i < U.size(); ++i){
        for (int j = 0; j < adjacencyList[v].size(); ++j){
            if (U[i] == adjacencyList[v][j])
                commonAdjacentNodes.push_back(U[i]);
        }
    }
    return commonAdjacentNodes;
}

void makeClique(vector<int>& U, int size, vector<int>& cliqueComponent) //Uは候補節点集合，sizeは今のクリークのサイズ
///vector<int> makeClique(vector<int>& U, vector<int>& cliqueComponent) //Uは候補節点集合，sizeは今のクリークのサイズ
{
    if (U.size() == 0) {
        if (size > max_size) {
        ///if (cliqueComponent.size() > max_size) {
            max_size = size;
            
            cout<<"Max Clique Components:";
            for (int i = 0; i < cliqueComponent.size(); ++i) {
                cout<<newNodesTitle[cliqueComponent[i]]<<endl;
            }
            cout<<endl;

            ///max_size = cliqueComponent.size();
            ///maxCliqueComponent = cliqueComponent;
        }
        return;
        ///return cliqueComponent;
    }
    while (U.size() != 0){
        if (size + U.size() <= max_size)
        ///if (cliqueComponent.size() + U.size() <= max_size)
        //cliqueComponent.clear();
            return;
            ///return cliqueComponent;

        int newCliqueComponent = U[0]; //Uの成分の中で最小のもの
        //for (int j = 1; j < U.size(); ++j) {
        //    if (i < U[j]) i = U[j];
        //}

        //cout<<"U = ";
        //for(int i = 0; i < U.size(); ++i){
        //    cout<<U[i];
        //}
        //cout<<"\t\t size:"<<size<<endl;

        U.erase( U.begin() );
        U = defineCommonAdjacentNodes(U, newCliqueComponent);
        cliqueComponent.push_back(newCliqueComponent);

        makeClique(U, size + 1, cliqueComponent);
        ///makeClique(U, cliqueComponent);
    }
    return;
    ///return cliqueComponent;
}

int main ()
{
    readPages("mutualPage_data.txt");
    readLinks("mutualLink_data.txt");
    vector<int> empty;

    //max_size = 0;
    for (int i = 0; i < NEW_MAX_V; ++i){
        vector<int> U = adjacencyList[i];
        vector<int> cliqueComponent;
        cliqueComponent.push_back(i);
        makeClique(U, 1, cliqueComponent);
        cliqueComponent. clear();
        //maxCliqueComponent = makeClique(U, empty);
    }

    //for(int i = 0; i < adjacencyList[0].size(); ++i){
    //    cout<<"adjacencyList[0]["<<i<<"]= "<<adjacencyList[0][i]<<endl;
    //}
    cout<<"Max Clique Size: "<<max_size<<endl;
    ///cout << "Max Clique Size: " << maxCliqueComponent.size() <<endl;
    ///cout<< "Components: " <<endl;
    ///for (int i = 0; i < maxCliqueComponent.size(); ++i){
    ///    cout<< newNodesTitle[maxCliqueComponent[i]] <<endl;
    ///}
    return 0;
}
