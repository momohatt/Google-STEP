#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<algorithm> //for sort

using namespace std;

#define MAX_V 1483277
int V = 1483277;

vector<int> adjacencyList[MAX_V];
int numOfPathOut[MAX_V] = {}; //そのノードから出ているパスの数
double score[MAX_V];
string page[MAX_V]; //番号と名前との対応

void readPages()
{
    int id;
    string name;

    ifstream ips("pages.txt");
    if (ips.fail())
        perror("couldn't open pages.txt");
    while (!ips.eof()) {
        ips >> id >> name;
        page[id] = name;
        //cout<<id<<" "<<name<<endl;
    }
    return;
}

void readLinks()
{
    int from, to;
    ifstream ifs("links.txt");
    if (ifs.fail())
        perror("couldn't open links.txt");
    while (!ifs.eof()) {
        ifs >> from >> to;
        adjacencyList[from].push_back(to);
        //cout << from << to << endl;
        numOfPathOut[from] += 1;
    }
    return;
}

void evalScore(double *score)
{
    double tmpScore[MAX_V];

    for (int i = 0; i < MAX_V; ++i){
        for (int j = 0; j < numOfPathOut[i]; ++j){
            tmpScore[j] += (double) score[i] / numOfPathOut[i];
        }
    }
    return;
}

void printHighScores(double score[])
{
    double tmp[MAX_V];
    for(int i = 0; i < MAX_V; ++i) tmp[i] = score[i];

    sort(tmp, tmp + MAX_V);

    for(int i = 0; i < 20; ++i){
        cout<<i+1<<"位: "<<tmp[i]<<"点, "<<endl;
    }
    return;
}

int main()
{
    readPages();
    readLinks();

    //scoreの初期化
    for (int i = 0; i < MAX_V; ++i){
        score[i] = 100;
    }

    for(int i = 0; i < 20; ++i){
        evalScore(score);
    }

    return 0;
}
