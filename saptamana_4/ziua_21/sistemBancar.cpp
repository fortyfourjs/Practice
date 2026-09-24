#include <iostream>

double retrageBani(double soldCurent, double sumaDorita){
    if(sumaDorita <= 0){
        throw std::invalid_argument("Introdu o suma valida!");}
    if(sumaDorita > soldCurent){
        throw std::runtime_error("Fonduri insuficiente!");
    }
    return soldCurent-sumaDorita;
}

int main(){

    double sold = 500;
    double sumaRetrasa;
    while(true){
        try{
            std::cout << "Ce suma doresti sa retragi?" << '\n';
            std::cin >> sumaRetrasa;
            sold = retrageBani(sold, sumaRetrasa);
            std::cout << sold << '\n';
            if(sold == 0){
                std::cout << "Ai retras toti banii!" << '\n';
                break;
            }
    
        }catch(const std::exception& err){
            std::cout << err.what() << '\n';
        }
    }

    return 0;
}