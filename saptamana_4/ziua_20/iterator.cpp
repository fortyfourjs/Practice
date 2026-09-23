#include <iostream>
#include <vector>
#include <map>

int main(){
    std::vector<int> v = {10, 20, 30, 40};
    for(std::vector<int>::iterator it = v.begin(); it != v.end(); it++){
        std::cout << *it << '\n';
    }
    std::map<std::string, int> map = {{"Produs1", 30}, {"Produs2", 10}, {"Produs3", 34}};
    for(std::map<std::string, int>::const_iterator it = map.begin(); it != map.end(); it++){
        std::cout << it.first << it.second << '\n';
    }
    return 0;
}