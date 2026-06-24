#pragma once

#include"task_manager.hpp"
#include"utils.hpp"

namespace TaskCLI {
    void main_menu(TaskManager& manager);
    void handle_add_task(TaskManager& manager);
    void handle_delete_task(TaskManager& manager);
    void handle_complete_task(TaskManager& manager);
    void find_task_by_tag(TaskManager& manager);
    int get_id();
}
