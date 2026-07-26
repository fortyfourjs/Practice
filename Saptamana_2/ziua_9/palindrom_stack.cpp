#include <iostream>
#include <stack>
using namespace std;

bool estePalindrom(string& s){
    stack<char> stack;
    for(int i=0;i<s.size();i++){
        stack.push(s[i]);
    }
    for(int i=0;i<s.size();i++){
        if(s[i] == stack.top()){
            stack.pop();
        }else{
            return false;
        }
    }
    return true;
}

int main(){
    string s = "kook";
    cout << estePalindrom(s);

    return 0;
}