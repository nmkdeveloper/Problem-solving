#include <iostream>

using namespace std;

int main() {
    int *ptr = nullptr;
    
    *ptr = 42; 
    
    cout << *ptr << endl;
    return 0;
}