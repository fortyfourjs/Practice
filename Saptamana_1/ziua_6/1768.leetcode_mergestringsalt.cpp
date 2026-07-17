class Solution {
public:
    string mergeAlternately(string word1, string word2) {
        string merge =  "";
        int n1 = word1.size();
        int n2 = word2.size();
        int limita_max = max(n1, n2);
        for(int i=0; i<limita_max;i++){
            if(i<n1){
                merge += word1[i];
            }
            if(i<n2){
                merge += word2[i];
            }
        }
    return merge;
    }
};
