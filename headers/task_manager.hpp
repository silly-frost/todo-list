#pragma once

#include"task.hpp"
#include<fstream>

class TaskManager {
    private:
        std::vector<Task> tasks;
        int next_id;

    public:
        void add_task(const std::string& name, const std::string& description, std::chrono::system_clock::time_point deadline, Priority level);
        void print_all_tasks();
        void complete_task(int id);
        void delete_task(int id);
        void find_by_tag(const std::string& tag);
        void save_tasks();
        void load_tasks();
};
