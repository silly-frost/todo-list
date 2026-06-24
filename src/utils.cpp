#include"utils.hpp"
#include<iostream>

void clear_screen(){
    #ifdef _WIN32
        std::system("cls");
    #else
        std::system("clear");
    #endif
}

void wait_for_user(){
    std::cin.clear();

    std::cout << "Нажмите Enter, чтобы продолжить...";
    std::cin.get();
}
