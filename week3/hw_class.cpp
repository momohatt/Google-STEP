#include<iostream>
#include<string>
#include<vector>
#include<stack>
using namespace std;

enum Type {NUMBER, PLUS, MINUS, MULTIPLY, DIVIDE, BRACKET_HEAD, BRACKET_TAIL};


class Token{
    public:
        Type type;
        double value;
        int priority;

        //constructor
        Token(Type t){
            type = t;
            //value = NULL;
            if(t=='PLUS'||t=='MINUS') priority = 1;
            if(t=='MULTIPLY'||t=='DIVIDE') priority = 2;
            if(t=='BRACKET_HEAD'||t=='BRACKET_TAIL') priority = 0;
        }

        Token(double d){
            type = NUMBER;
            value = d;
            priority = 3;
        }

        Token(const Token &obj){
            type = obj.type;
            value = obj.value;
        }

};


class Formula{
    private:
        string formula_str;
        vector<Token> tokens;
        stack<Token> postPrefixTokens;
        int indx=0;

    public:
        void setString(string formula){
            formula_str = formula;
        }

        double evaluate(){
            int i = 0; //index
            stack<Token> S;

            while (i<postPrefixTokens.size()){
                if (postPrefixTokens.top().type == 'NUMBER'){
                    S.push(postPrefixTokens.top());
                    postPrefixTokens.pop();
                } else if (postPrefixTokens.top().type == 'PLUS'){
                    Token tmp(0.0);
                    tmp.value = S.top().value; S.pop();
                    tmp.value += S.top().value; S.pop();
                    S.push(tmp);
                } else if (postPrefixTokens.top().type == 'MINUS'){
                    Token tmp(0.0);
                    tmp.value = -1.0 * S.top().value; S.pop();
                    tmp.value += S.top().value;
                    S.push(tmp);
                } else if (postPrefixTokens.top().type == 'MULTIPLY'){
                    Token tmp(0.0);
                    tmp.value = S.top().value; S.pop();
                    tmp.value *= S.top().value; S.pop();
                    S.push(tmp);
                } else if (postPrefixTokens.top().type == 'DIVIDE'){
                    Token tmp(0.0);
                    tmp.value = 1.0 / S.top().value; S.pop();
                    tmp.value *= S.top().value; S.pop();
                    S.push(tmp);
                } else {
                    cout<<"Calculation Error!!"<<endl;
                }

                ++indx;
            }

            return S.top().value;
        }

    private:
        Token readNumber(int& indx)
        {
            double number = 0.0;
            while (indx < formula_str.length() && isdigit(formula_str[indx])){
            number = number * 10 + (formula_str[indx] - '0');
            indx++;
            }
            if (indx < formula_str.length() && formula_str[indx] == '.'){
                double keta = 0.1;
                number += (formula_str[indx]) * keta;
                keta *= 0.1;
                indx++;
            }

            return Token(number);
        }

        Token readOperator(int& indx)
        {
            switch (formula_str[indx]){
                case '+':
                    return Token('PLUS');
                case '-':
                    return Token('MINUS');
                case '*':
                    return Token('MULTIPLY');
                case '/':
                    return Token('DIVIDE');
                case '(':
                    return Token('BRACKET_HEAD');
                case ')':
                    return Token('BRACKET_TAIL');
                default:
                    cout<<"Invalid character found."<<endl;
                    Token error('ERROR');
                    exit(1);
            }
        }

        void tokenize(int& indx)
        {
            while(indx < formula_str.length()){
                if(isdigit(formula_str[indx])){
                        tokens.push_back(readNumber(indx));
                } else {
                    tokens.push_back(readOperator(indx));
                }
            }
            return;
        }

        void convertToPostPrefixFormat() //incomplete
        {
            stack<Token> S;
            Token tmp(0.0);
            tmp.priority = -1;
            S.push(tmp);
            int length=tokens.size();

            int i = 0; //index
            while (i < length ){
                if (tokens[i].type == 'BRACKET_HEAD'){
                    S.push(tokens[i]);
                } else if (tokens[i].type == 'BRACKET_TAIL'){
                    while (S.top().type != 'BRACKET_HEAD'){
                        postPrefixTokens.push(S.top());
                        S.pop();
                    }
                    S.pop();
                } else {
                    while (tokens[i].priority <= S.top().priority){
                        postPrefixTokens.push(S.top());
                        S.pop();
                    }
                    S.push (tokens[i]);
                }
                i++;
            }

            while (S.top().priority != -1){
                postPrefixTokens.push(S.top());
                S.pop();
            }
            return;
        }
};


int main()
{
    string tmp;
    Formula form;
    for(;;){
        cout<<"> "<<endl;
        cin>>tmp;
        form.setString(tmp);
        int answer = form.evaluate();
        cout<<"answer:"<<answer<<endl;
    }
    return 0;
}
