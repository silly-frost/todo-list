#pragma once 

#include<cstdlib>

inline void clear_screen() {
#ifdef _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif
}
