#include"task_manager.hpp"
#include<iostream>
#include<algorithm>

TaskManager::TaskManager() {
    next_id = 1;
}

void TaskManager::add_task(const std::string& name, const std::string& description, std::chrono::system_clock::time_point deadline, Priority level){
    Task current;
    
    current.id = next_id;
    current.name = name;
    current.description = description;
    current.status = false;
    current.deadline = deadline;
    current.level = level;

    tasks.push_back(current);
    next_id++;
}

void TaskManager::print_all_tasks(){
    if(tasks.empty()) {
        std::cout << "У вас нет созданных задач!\n";
        return;
    }
    
    for(const auto& task : tasks){
        std::cout << "================================================\n";
        std::cout << "Номер задачи: " << task.id << "\n";
        std::cout << "Название: " << task.name << "\n";
        std::cout << "Описание: \n\"" << task.description << "\"\n";
        switch(task.level) {
            case Priority::low:
                std::cout << "Приоритет: Низкий\n";
                break;
            case Priority::medium:
                std::cout << "Приоритет: Средний\n";
                break;
            case Priority::high:
                std::cout << "Приоритет: Высокий\n";
                break;
        }
        std::cout << std::chrono::format("%Y-%m-%d %H:%M", task.deadline); 
        std::cout << "================================================\n\n";
    }
}

void TaskManager::complete_task(int id){
    auto it = std::find_if(tasks.begin(), tasks.end(), [id](const Task& t) {return t.id == id;});

    if(it != tasks.end()) it->status = true;
    else std::cout << "Невозможно завершить задачу. Задача с таким ID не найдена. \n";
}

void TaskManager::delete_task(int id){
    auto it = std::find_if(tasks.begin(), tasks.end(), [id](const Task& t) {return t.id == id;});

    if(it != tasks.end()) tasks.erase(it);
    else std::cout << "Невозможно удалить задачу. задача с таким ID не найдена. \n";
}
