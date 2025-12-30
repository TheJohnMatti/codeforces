#include <iostream>
#include <string>

int main(int argc, char* argv[]){

    int k;

    std::cin >> k; 


    for (int i = 0; i < k; i++){
        std::string s;
        std::cin >> s;

        if (s.size() > 10) {
            std::cout << s[0] << s.size()-2 << s[s.size()-1] << std::endl;
        } else {
            std::cout << s << std::endl;   
        }
    }

    return 0;
}