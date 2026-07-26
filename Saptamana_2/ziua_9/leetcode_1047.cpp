#include <iostream>
#include <stack>
#include <string>
using namespace std;

void sterge_dubluri(string& s){
    stack<char> stack;
    for(int i=0;i<s.size();i++){
        if(!stack.empty() && s[i] == stack.top()){
            stack.pop();
        }else{
            stack.push(s[i]);
        }
    }
    string rezultat = "";
    while(!stack.empty()){
        rezultat += stack.top();
        stack.pop();
    }
    for(int i=rezultat.size()-1;i>=0;i--){
        cout << rezultat[i];
    }
    cout << endl;
}

int main(){
    string s = "aabccbbd";
    sterge_dubluri(s);

    return 0;
}