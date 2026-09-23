#include <iostream>


double imparte(double a, double b){
    if(b == 0){
        throw std::invalid_argument("Numitorul nu poate fi 0!");
    }else{
        return a/b;
    }
}

int main(){
    while(true){
        try{
            double a, b;
            std::cout << "introdu a si b" << '\n';
            std::cin >> a >> b;
            double rezultat = imparte(a, b);
            std::cout << rezultat << '\n';
            break;
        }catch(const std::invalid_argument& err){
            std::cout << err.what();
        }
    }
return 0;
}
