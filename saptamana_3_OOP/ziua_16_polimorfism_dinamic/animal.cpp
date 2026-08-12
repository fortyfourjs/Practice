#include <iostream>
#include <memory>
#include <vector>

using namespace std;

class Animal{
    public:
        virtual ~Animal(){
            cout << "memorie stearsa" << '\n';
        }
        virtual void scoateSunet() const{
            cout << "sunet generic animal" << '\n';
        }
};
class Caine : public Animal{
    public:
        void scoateSunet() const override{
            cout << "ham" << '\n';
        }
};
class Pisica : public Animal{
        public:
            void scoateSunet() const override{
                cout << "miau" << '\n';
            }
};

int main(){
    vector<unique_ptr<Animal>> animale;
    animale.push_back(make_unique<Caine>());
    animale.push_back(make_unique<Pisica>());
    animale.push_back(make_unique<Animal>());
    for(const auto& a : animale){
        a->scoateSunet();
    }
    return 0;
}