#include <iostream>
#include <vector>
using namespace std;

void printStack(const vector<int>& stack){
    if(stack.size() == 0){
        cout << "Stack is empty ";
    }
    for(auto i : stack){
        cout << "(" << i << ")" << ' ';
    }
    cout << "Capacity: " << stack.capacity() << " " << "Length: " << stack.size() << '\n';
}

int main(){
    vector<int> stack{};
    stack.push_back(1);
    printStack(stack);
    stack.push_back(2);
    printStack(stack);
    stack.push_back(3);
    printStack(stack);
    stack.pop_back();
    printStack(stack);
    stack.push_back(4);
    stack.pop_back();
    printStack(stack);
    stack.pop_back();
    printStack(stack);
    stack.pop_back();
    printStack(stack);
    
}