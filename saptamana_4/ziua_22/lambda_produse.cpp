#include <iostream>
#include <vector>
#include <algorithm>

struct Produse{
    std::string nume;
    double pret;
} listaProduse;

int main(){
    double prag;
    std::cin >> prag;
    struct Produse P[] = {{"Produs1", 300},
                          {"Produs2", 100},
                          {"Produse3", 455},
                            {"Produs4", 76}};
    std::vector<Produse> vectorProduse;
    for(int i=0; i<sizeof(P)/sizeof(P[0]); i++){
        vectorProduse.push_back(P[i]);
    }
    for(auto& Produse : vectorProduse){
        std::cout << Produse.nume << " ";
        std::cout << Produse.pret << '\n';
    }
    std::cout << "Produse sortate crescator" << '\n';
    std::sort(vectorProduse.begin(), vectorProduse.end(), [](const Produse& p1, const Produse& p2) {return p1.pret < p2.pret;});
    for(auto& Produse : vectorProduse){
        std::cout << Produse.nume << " ";
        std::cout << Produse.pret << '\n';
    }
    std::cout << std::count_if(vectorProduse.begin(), vectorProduse.end(),[prag](const Produse& p1){return p1.pret > prag;}) << " Produse peste " << prag;

    return 0;
}