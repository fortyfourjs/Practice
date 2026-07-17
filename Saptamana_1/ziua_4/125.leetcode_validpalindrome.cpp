class Solution {
public:
string curata_sir(const string& s){
    int n = s.size();
    string rezultat = "";
    for(int i=0;i<n;i++){
        if(isalnum(s[i])){
            rezultat.push_back(tolower(s[i]));
        }
    }
return rezultat;
}
    bool isPalindrome(string s) {
        string sir_curat = curata_sir(s);
        int n = sir_curat.size();
        for(int i = 0; i<n/2; i++){
            if(sir_curat[i] != sir_curat[n-i-1])
                return false;
        }
    return true;
    }
};