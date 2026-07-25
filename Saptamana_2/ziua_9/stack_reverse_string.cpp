#include <iostream>
#include <string>
#include <stack>
using namespace std;

void inverseaza_string(string& s){
    stack<char> st;
    int n = s.size();
    for(int i=0;i<n;i++){
        st.push(s[i]);
    }
while(!st.empty()){
    cout << st.top();
    st.pop();
}
}

int main(){

    string s = "hello";
    inverseaza_string(s);

    return 0;
}