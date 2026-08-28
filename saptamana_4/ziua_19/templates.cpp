#include <iostream>
#include <typeinfo>
#include <string>


template<typename T> T aduna(T a, T b){
    return a+b;
}
template<typename T> T maxim(T a, T b){
    return a>b?a:b;
}
template<typename T>
class Cutie{
    private:
        T continut;
    public:
        Cutie() = default;
        void setContinut(T v){
            continut = v;
        }
        T getContinut() const{
            return continut;
        }
        void afiseazaTip() const{
            std::cout << "Tip: " << typeid(T).name() << " | valoare: " << continut << "\n";
        }   

};
template<typename T>
class Pereche{
    private:
        T primul;
        T alDoilea;
    public:
        Pereche(T a, T b) : primul(a), alDoilea(b){}
        T getMaxim() const{
            return (primul > alDoilea) ? primul:alDoilea;
        }
        void afiseaza() const{
            std::cout << "[" << primul << ", " << alDoilea << "]" << '\n';
        }
};
int main(){
    int x = aduna(3,5);
    std::cout << x << '\n';
    maxim(6,8);
    Cutie<int> cutieInt;
    cutieInt.setContinut(33);
    cutieInt.afiseazaTip();
    Cutie<std::string> cutieText;
    cutieText.setContinut("abcdefg");
    cutieText.afiseazaTip();
    Pereche<int> pInt(31, 7);
    pInt.afiseaza();
    std::cout << "maxim int: " << pInt.getMaxim() << '\n';
    Pereche<double> pDouble(23.60, 21.21);
    pDouble.afiseaza();
    std::cout << "maxim double: " << pDouble.getMaxim() << '\n';
    
    return 0;

}