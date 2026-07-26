#include <iostream>
#include <queue>
using namespace std;

int findKthLargest(vector<int>& nums, int k){
    int k_pozitie;
    priority_queue<int> lista_numere;
    for(int i=0; i<nums.size();i++){
        lista_numere.push(nums[i]);
    }
    vector<int> rezultat;
    while(!lista_numere.empty()){
        rezultat.push_back(lista_numere.top());
        lista_numere.pop();
    }
    for(int i=1;i<rezultat.size();i++){
        if(k == rezultat[i]){
            k_pozitie = i+1;
        }
    }

return k_pozitie;
}

int main(){
    vector<int> nums = {3,2,1,5,6,4}; // 6 5 4 3 2 1
    cout << findKthLargest(nums, 2);


    return 0;

}