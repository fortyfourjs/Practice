#include <iostream>
#include <queue>
using namespace std;

int findKthLargest(vector<int>& nums, int k){
    int k_pozitie;
    priority_queue<int> lista_numere;
    for(int i=0; i<nums.size();i++){
        lista_numere.push(nums[i]);
    }
    for(int i=0;i<k-1;i++){
        lista_numere.pop();
    }
    return lista_numere.top();
    }


int main(){
    vector<int> nums = {3,2,1,5,6,4}; // 6 5 4 3 2 1
    cout << findKthLargest(nums, 4);


    return 0;

}