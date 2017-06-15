#include<iostream>
#include<string>
#include<stack>
#include<vector>
using namespace std;

enum Type {NUMBER, PLUS, MINUS, MULTIPLY, DIVIDE, BRACKET_HEAD, BRACKET_TAIL, END};

struct Token {
    Type type;
    union {
        double number;
    } value;
};

vector<Token> polishize(vector<Token> tokens)
{
    int length=tokens.size();
    int priority[length];
    vector<Token> polishizedtokens[length];
    stack<Token> stack[length+1];   int sp1=0; //stackpointer
    stack<Token> polish[length+1];  int sp2=0; //stackpointer

    for(int i=0;i<length;++i){
        if(tokens[i].type==NUMBER) priority[i]=3;
        if(tokens[i].type==PLUS||tokens[i].type=='MINUS') priority[i]==1;
        if(tokens[i].type==MULTIPLY||tokens[i].type=='DIVIDE') priority[i]==2;
        if(tokens[i].type==BRACKET_HEAD) priority[i]=0;
        if(tokens[i].type==BRACKET_TAIL) priority[i]=0;
    }

    stack[0].type='NUMBER'; stack.value=0;
    priority[0]=0;

    for(int i=1;i<=length;++i){
        if(tokens[i].type=='BRACKET_HEAD'){ //transact (
            stack[++sp1]=tokens[i];
        } else if(tokens[i].type=='BRACKET_TAIL'){ //transact )
            while(stack[sp1].type=='BRACKET_HEAD')
                polish[++sp2]==stack[sp1--];
            sp1--;
        } else { //transact numbers & operators
            while(priority[i]<=priority[sp1])
                polish[++sp2]=stack[sp1--];
            stack[++sp1]=tokens[i];
        }
    }

    for(i=sp1;i>0;i--){
        polish[++sp2]=stack[i];
    }

    int i=0;
    while(!polish.empty()){
        polishizedtokens[i]=polish[i];
        ++i;
    }

    return polishizedtokens;

}

int main()
{
    vector<Token> a, b;
    a[0].type=NUMBER; a[0].value=10.2;
    a[1].type=PLUS;
    a[2].type=NUMBER; a[2].value=4.8;

    b=polishize(a);
    cout<<b<<endl;
    return 0;
}
