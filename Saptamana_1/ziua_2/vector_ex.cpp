#include <iostream>
#include <vector>
using namespace std;

void min_max(vector<int>& v){
    int n = v.size();
    int min = v[0];
    int max = v[0];
    for(int i=0; i<n; i++){
        if(v[i] < min){
            min = v[i];
        }
        if(v[i] > max){
            max = v[i];
        }
    }
    cout << "min=" << min << " " << "max=" << max << '\n';
}

void media_aritmetica(vector<float>& v){
    int n = v.size();
    float suma = 0;
    for(int i=0; i<n; i++){
        suma += v[i];
    }
    cout << "media aritmetica=" << suma/n << '\n';
}

void adauga_elemente(vector<int>& v){
    vector<int> copie = v;
    int n = copie.size();
    for(int i=0; i<n; i++){
        v.push_back(copie[i]);
        cout << "capacitate=" << copie.capacity() << '\n';
    }
    
}
void sterge_element(vector<int>& v, int pozitie){
    int n = v.size();
    for(int i=pozitie; i<n-1; i++){
        v[i] = v[i+1];
    }
    v.pop_back();
}

int main(){
    vector lista_random {6,3,8,56,4,7,85,73,26,86,54,38,95,11,18,43,67};

    cout << "size=" << lista_random.size() << '\n';
    cout << "capacity before running out=" << lista_random.capacity() << '\n'; 

    min_max(lista_random);

    vector<float> lista_float {6.3, 6.31, 2.3, 2.40, 10.6, 11.53, 12.3, 10.9};
    media_aritmetica(lista_float);

    lista_float.erase(lista_float.begin() + 0); //sterge elementul lista_float[0] 
    for(auto i: lista_float){
        cout << i << '\n'; //afisare elemente vector
    }
    adauga_elemente(lista_random);
    for(auto i : lista_random){
        cout << i << '\n';
    }
    cout << lista_random.size() << '\n';

    cout << "CAPACITATE=" << lista_random.capacity() << '\n';

    sterge_element(lista_random, 7);
    for(auto i : lista_random){
        cout << i << '\n';
    } 
    
    return 0;
}