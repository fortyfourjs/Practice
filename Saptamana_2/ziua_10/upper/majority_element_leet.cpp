class Solution {
public:
    int majorityElement(vector<int>& nums) {
        sort(nums.begin(),nums.end());
        int counter = 1;
        if(nums.size() == 1){
            return nums[0];
        }
        for(int i=1; i<nums.size();i++){
            if(nums[i] == nums[i-1]){
                counter++;
            }else{
                counter = 1;
            }
            if(counter > nums.size()/2){
                return nums[i];
            }
        }
        return nums[0];
    }
};

// boyer-moore
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int counter=0;
        int candidate=0;
        for(int num : nums){
            if(counter == 0){
                candidate = num;
            }
            if(num == candidate){
                counter++;
            }else{
                counter--;
            }
        }
        return candidate;
    }
};