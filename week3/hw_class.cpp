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

        //constructor
        Token(Type t){
            type = t;
            //value = NULL;
        }

        Token(double d){
            type = NUMBER;
            value = d;
        }

        Token(const Token &obj){
            type = obj.type;
            value = obj.value;
        }
};


class Formula{
    public:
        void setString(string formula){
            formula_str = formula;
        }

        double evaluate(){
        }

    private:
        Token readNumber(int indx)
        {
            double number = 0.0;
            while (indx < formula_str.length() && isdigit(formula_str[indx])){
            number = number * 10 + stoi(formula_str[indx]);
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
        
        Token readOperator(int indx)
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
                    throw exception; //
            }
        }

        void tokenize()
        {
            int indx = 0;
            while(indx < formula_str.length()){
                if(isdigit(formula_str[indx])){
                        tokens.push_back[readNumber(indx)];
                } else {
                    tokens.push_back[readOperator(indx)];
                }
            }
            return;
        }

    private:
        string formula_str;
        vector<Token> tokens;

};

vector<Token> polishize(vector<Token> tokens)
{
    int length=tokens.size();
    int priority[length];
    stack<Token> 

    for(int i=0;i<length;++i){
        if(tokens[i].type=='NUMBER') priority[i]=3;
        if(tokens[i].type=='PLUS'||tokens[i].type=='MINUS') priority[i]==1;
        if(tokens[i].type=='MULTIPLY'||tokens[i].type=='DIVIDE') priority[i]==2;
        if(tokens[i].type=='BRACKET_HEAD') priority[i]=4;
        if(tokens[i].type=='BRACKET_TAIL') priority[i]=0;
    }

    stack[0];

}

int main()
{
    Formula form;
    form.setString(cin);
    int answer = form.evaluate;
    cout<<"answer:"<<answer<<endl;
    return 0;
}

