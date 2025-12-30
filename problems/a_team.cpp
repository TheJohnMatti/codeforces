#include <iostream>


int main(int argc, char* argv[]) {


    int k, res;
    res = 0;
    std::cin >> k;

    for (int i = 0; i < k; i++) {

        int i1, i2, i3;

        std::cin >> i1 >> i2 >> i3;

        if (i1 + i2 + i3 >= 2)
            res += 1;

    }

    std::cout << res;

    return 0;
}