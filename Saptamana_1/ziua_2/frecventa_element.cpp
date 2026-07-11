#include <iostream>
#include <vector>
using namespace std;

void frecventa(vector<int>& v, int n){
    int i = 0;
    int count = 0;
    while(i < v.size()){
        if(n == v[i]){
            count++;
        }
        i++;
    }
    cout << count;
}

int main(){
    vector<int> vector_random;
    int n;
    cout << "nr elemente vector:" << '\n';
    cin >> n;
    for(int i=0;i<n;i++){
        int nr_citit;
        cin >> nr_citit;
        vector_random.push_back(nr_citit);
    }
    for(int i : vector_random){
        cout << i;
    }
    int numar_cautat;
    cout << "ce element cauti?" << '\n';
    cin >> numar_cautat;

    frecventa(vector_random, numar_cautat);

return 0;
}