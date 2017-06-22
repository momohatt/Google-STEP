#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<algorithm>

#define NEW_MAX_V 763995 //双方向エッジを持つノードだけ扱う
#define OLD_MAX_V 1483277

using namespace std;

int renumberingTable[OLD_MAX_V]; //再ナンバリングしていく時の旧番号と新番号の対応表，renumberingTable[old_number] = new_number

string newNodesTitle[NEW_MAX_V]; //新番号とページタイトルの対応表
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
        newID1 = renumberingTable[id1];
        newID2 = renumberingTable[id2];
        adjacencyList[newID1].push_back(newID2);
        adjacencyList[newID2].push_back(newID1);
        //注：隣接リストは番号が若い順に並ぶはず
    }
    cout<<"readLinks finished"<<endl;
    
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
{
    if (U.size() == 0) {
        if (size > max_size) {
            max_size = size;
            
            cout<<"Max Clique Components:"<<endl;
            for (int i = 0; i < cliqueComponent.size(); ++i) {
                cout<<newNodesTitle[cliqueComponent[i]]<<endl;
            }
            cout<<endl;
        }
        return;
    }
    while (U.size() != 0){
        if (size + U.size() <= max_size)
            return;

        int newCliqueComponent = U[0]; //Uの成分の中で最小のもの

        U.erase( U.begin() );
        U = defineCommonAdjacentNodes(U, newCliqueComponent);
        cliqueComponent.push_back(newCliqueComponent);

        makeClique(U, size + 1, cliqueComponent);
    }
    return;
}

int main ()
{
    readPages("mutualPage.txt");
    readLinks("mutualLink.txt");

    for (int i = 0; i < NEW_MAX_V; ++i){
        vector<int> U = adjacencyList[i];
        vector<int> cliqueComponent;
        cliqueComponent.push_back(i);
        makeClique(U, 1, cliqueComponent);
        cliqueComponent. clear();
    }

    cout<<"Max Clique Size: "<<max_size<<endl;
    
    return 0;
}
