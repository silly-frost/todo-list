#pragma once

#include<vector>
#include<string>
#include<chrono>

enum class Priority{
    low = 1,
    medium = 2,
    high = 3
};

struct Task {
    int id;

    std::string name;
    std::string description;
    
    bool status;                                        // true - выполнено | false - не выполнено
    std::vector<std::string> tags;                      // теги для поиска
    std::chrono::system_clock::time_point deadline;     // срок, до которого задачу нужно выполнить

    Priority level;
};
