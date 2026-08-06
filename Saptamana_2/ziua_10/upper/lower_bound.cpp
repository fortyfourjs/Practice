#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;


int main(){
    vector<int> v = {1,2,4,4,4,6,8};
    vector<int> unsorted_v = {89, 23, 65, 12, 76, 54, 3, 18};
    sort(unsorted_v.begin(),unsorted_v.end());
    cout << *lower_bound(unsorted_v.begin(), unsorted_v.begin() + 3, 30) << '\n';
    
    auto it = lower_bound(v.begin(),v.end(), 4);

    if(it != v.end() && *it == 4){
        int index = it - v.begin();
        cout << "valoarea " << *it << " se afla la indexul:" << index << '\n';
    }else{
        cout << "elementul nu a fost gasit" << '\n';
    }
    v.erase(remove_if(v.begin(),v.end(), [](int x){
        return x % 2 == 0;}), v.end());
    for(auto i : v){
        cout << i;
    }
    return 0;
}
