class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        unordered_set<int> set_nums1(nums1.begin(),nums1.end());
        unordered_set<int> rezultat_set;
        for(auto x : nums2){
            if(set_nums1.count(x)){
                rezultat_set.insert(x);
            }
        }
        return vector<int>(rezultat_set.begin(),rezultat_set.end());
    }
};