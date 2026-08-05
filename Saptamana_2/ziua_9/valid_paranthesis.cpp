#include <iostream>
#include <string>
#include <stack>
using namespace std;

bool paranteze_corecte(string s){
    stack<char> paranteze;
    for(int i=0;i<s.size();i++){
        if(s[i] == '(' || s[i] == '[' || s[i] == '{'){
            paranteze.push(s[i]);
        }
        else{
            if(paranteze.empty()){
                return false;
        }
        if((paranteze.top() == '(' && s[i] == ')') ||
           (paranteze.top() == '[' && s[i] == ']') ||
           (paranteze.top() == '{' && s[i] == '}')){
            paranteze.pop();
        }
        else{
            return false;
        }
    }
}
    
    return paranteze.empty();
}



int main(){
    string s = "({[]})";
    cout << boolalpha <<  paranteze_corecte(s);
    return 0;
}