#include <iostream>
#include <string>
using namespace std;

void inversare(string& s){
    int n = s.length();
    int temp;
    for(int i=0;i<n/2;i++){
        temp = s[i];
        s[i] = s[n-i-1];
        s[n-1-i] = temp;
    }
    cout << s << "\n";
}

int main(){

    string c = "abcdef";
    inversare(c);
    
}