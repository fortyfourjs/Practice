#include <iostream>
#include <vector>
using namespace std;

void calculare_medie(vector<float>& v){
    float suma_note = 0;
    for(int i = 0;i<v.size();i++){
        suma_note += v[i];
    }
    cout << "Media=" << suma_note/v.size() << '\n';
}
void introducere_note(vector<float>& v){
    int n;
    cout << "cate note introduci?" << '\n';
    cin >> n;

    for(int i=0;i<n;i++){
        float nota;
        cin >> nota;

        v.push_back(nota);
    }
}
int main(){
    vector<float> nota;
    introducere_note(nota);
    
    calculare_medie(nota);

    return 0;
    
}