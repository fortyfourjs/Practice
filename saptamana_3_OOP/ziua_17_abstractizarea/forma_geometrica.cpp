#include <iostream>
#include <memory>
#include <vector>
using namespace std;


class FormaGeometrica{
    public:
        virtual ~FormaGeometrica() = default;
        virtual double calculeazaAria() const = 0;
        virtual void afiseaza() const = 0;
};
class Patrat : public FormaGeometrica{
    private:
        double latura;
    public:
        Patrat(double l) : latura(l){};
        double calculeazaAria() const override{
            return latura*latura;
}
        void afiseaza() const override {
            cout << "Latura:" << latura << " Aria:" << calculeazaAria() << '\n';
        }
};
class Cerc : public FormaGeometrica{
    private:
        double raza;
    public:
        Cerc(double r) : raza(r){};
        double calculeazaAria() const override{
            return 3.14*raza*raza;
}
        void afiseaza() const override{
            cout << "Raza:" << raza << " Aria:" << calculeazaAria() << '\n';
        }
};
int main(){
    vector<unique_ptr<FormaGeometrica>> forme;
    forme.push_back(make_unique<Patrat>(4));
    forme.push_back(make_unique<Cerc>(7));
    for(const auto& f : forme){
        f->afiseaza();
    }
    return 0;
}