#include <iostream>
#include <vector>
using namespace std;

void citire_vector(vector<int>& v){
    int n;
    cout << "cate numere introduci in vector: " << '\n';
    cin >> n;
    for(int i=0;i<n;i++){
        int numar_citit;
        cin >> numar_citit;
        v.push_back(numar_citit);
    }
    for(auto i : v){
        cout << i << " ";
    }
}

void inversare_vector(vector<int>& v){
    int n = v.size();
    int swap;
    for(int i=0;i<n/2;i++){
        swap = v[i];
        v[i] = v[n-i-1];
        v[n-i-1] = swap;
    }
    for(auto i : v){
        cout << i <<" ";
    }
}

void sterge_impar(vector<int>& v){
    int i = 0;
    while(i<v.size()){
        if(v[i] % 2 != 0){
            v.erase(v.begin() + i);

        }else{
            i++;
        }
    }
    for(auto i : v){
        cout << i << " ";
}
}
int main(){

    vector<int> v{1,2,3,4,5};
    sterge_impar(v);
    cout << '\n';
    vector<int> c{2,4,1,3,10,7,5,4};
    cout << '\n';
    inversare_vector(c);
    vector<int> s;
    citire_vector(s);

    return 0;
}