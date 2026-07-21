#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

int frecventa(vector<int>& nums){
    unordered_map<int, int> hashmap;
    for(int i=0;i<nums.size();i++){
        hashmap[nums[i]]++;
    }
    for(auto& [numar, frecventa] : hashmap){
        if(frecventa >= nums.size()/2){
            return numar;
        }
    }
return -1;
}

int frecventa2(vector<int>& nums){
    unordered_map<int, int> hashmap;
    for(int i=0;i<nums.size();i++){
        hashmap[nums[i]]++;
        if(hashmap[nums[i]] >=  nums.size()/2){
            return nums[i];
        }
    }
return -1;
}

int main(){
    vector<int> nums = {1,2,3,4,5,6,6,6,6,6,1,1,1,1,1,1,1,1,6};
    cout << frecventa2(nums) << '\n';
    cout << frecventa(nums);
    return 0;

}