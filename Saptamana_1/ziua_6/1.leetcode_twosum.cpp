class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        vector<int> lista_complement = {};
        for(int i=0;i<nums.size();i++){
            int complement = target - nums[i];
            lista_complement.push_back(complement);
        }
        for(int i=0; i<nums.size();i++){
            for(int j=i+1;j<nums.size();j++){
                if(nums[i] == lista_complement[j]){
                    return{i,j};
                }
            }
        }
    return {};
    }
};