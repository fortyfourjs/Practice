#include <iostream>
#include <vector>
#include <memory>
using namespace std;


class Notificare{
    protected:
        string mesaj;
    public:
        Notificare(string msg) : mesaj(msg){}
        virtual ~Notificare() = default;
        virtual void trimite() const{
            cout << "Trimite notificare genereica" << mesaj << '\n';
        }
};
class NotificareSMS : public Notificare{
    private:
        int nrtelefon;
    public:
        NotificareSMS(string msg, int nr) : Notificare(msg), nrtelefon(nr){}
        void trimite() const override{
            cout << "Trimite SMS catre " << nrtelefon << ": " << mesaj << '\n';
        }

};
class NotificareEmail : public Notificare{
    private:
        string email;
    public:
        NotificareEmail(string msg, string mail) : Notificare(msg), email(mail){}
        void trimite() const override{
            cout << "Trimite Email catre " << email << ": " << mesaj << '\n';
        }
};
int main(){
    vector<unique_ptr<Notificare>> notificari;
    notificari.push_back(make_unique<NotificareSMS>("comanda expediata", 0724404543));
    notificari.push_back(make_unique<NotificareEmail>("mail confirmare", "client@yahoo.com"));
    for(const auto& a : notificari){
        a->trimite();
    }
    return 0;
}