#include <iostream>

int main(int argc, char * argv[]) {
    int v;
    std::cin >> v;

    if (v <= 2) {
        std::cout << "NO";
        return 0;
    }

    if (v % 2 == 0) std::cout << "YES";
    else std::cout << "NO";
    return 0;
}