#include <iostream>
#include <fstream>
#include <string>

void scrieLog(const std::string& text){
    std::ofstream scrieFisier("log.txt", std::ios::app);

    if(scrieFisier.is_open()){
        scrieFisier << text << '\n';
    }
}
void citesteLog(){
    std::ifstream citesteFisier("log.txt");
    if(!citesteFisier.is_open()){
        throw std::invalid_argument("Fisierul nu e deschis.");
    }
    std::string linie;
    while(std::getline(citesteFisier, linie)){
        std::cout << linie << '\n';
    }
}
int main(){

    scrieLog("Text1");
    scrieLog("Text2");
    scrieLog("Text3");
    citesteLog();


    return 0;
}