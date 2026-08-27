#include <iostream>

using namespace std;

int main() {
    int a[3] = {1, 2, 3};
    
    a[10] = 99; 
    
    cout << a[10] << endl;
    return 0;
}