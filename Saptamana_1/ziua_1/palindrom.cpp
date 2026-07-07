#include <iostream>
#include <string>
using namespace std;

bool palindrom(string& s){
    int n = s.length();
    for(int i=0; i<n/2; i++){
        if(s[i] != s[n-i-1]){
            return false;
        }
    }
return true;
}

int main(){

    string s;
    cin >> s;

    if (palindrom(s)){
        cout << s << " este palindrom\n";
    }
    else{
        cout << s << " nu este palindrom\n";
    }

}