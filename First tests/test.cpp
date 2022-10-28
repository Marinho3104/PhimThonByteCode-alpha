
#include <iostream>

int main() {

    int ola = 10, ll = 0;

    ll = 11 + (ola += 1) * 10;

    std::cout << ola << std::endl;
    

    return 0;
}