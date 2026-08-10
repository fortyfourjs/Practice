#include <iostream>
using namespace std;

class customBuffer{
    private:
        int* data;
        int size;
    public:
        customBuffer(int s){
            size = s;
            data = new int[size];
            for(int i=0;i<size;i++){
                data[i] = i*10;
            }
        }
        ~customBuffer(){
            cout << "s-a eliberat memoria " << data << '\n';
            delete[] data;
            
        }
        customBuffer(const customBuffer& other){
            size = other.size;
            data = new int[size];
            for(int i=0;i<size;i++){
                data[i] = other.data[i];
            }
        }
        customBuffer& operator=(const customBuffer& other){
            if(this == &other){
                return *this;
            }
            delete[] data;
            size = other.size;
            data = new int[size];
            for(int i=0;i<size;i++){
                data[i] = other.data[i];
            }
            return *this;
        }
        void set(int index, int value){
            data[index] = value;
        }
        void print() const{
            for(int i=0;i<size;i++){
                cout << "valoarea " << data[i] << " la adresa: " << &data[i] << '\n';
            }
        }
};

int main(){
    customBuffer b1(5);
    customBuffer b2 = b1;
    b1.set(2, 99);
    b1.print();
    b2.print();
    return 0;
}