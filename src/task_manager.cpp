#include"task_manager.hpp"
#include<iostream>
#include<algorithm>

TaskManager::TaskManager() {
    next_id = 1;
}

void TaskManager::add_task(const std::string& name, const std::string& description, std::chrono::system_clock::time_point deadline, Priority level, const std::vector<std::string> tags){
    Task current;
    
    current.id = next_id;
    current.name = name;
    current.description = description;
    current.status = false;
    current.deadline = deadline;
    current.level = level;
    current.tags = tags;

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
        std::cout << "Выполнить до: " << std::chrono::format("%Y-%m-%d", task.deadline) << "\n";
        std::cout << "\nТеги: ";
        if(task.tags.empty()) std::cout << "У этой задачи нет тегов";
        else{
            for(const auto& tag : task.tags){
                std::cout << "#" << tag << " ";
            }
        }
        std::cout << "\n";
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

void TaskManager::find_by_tag(const std::string& tag){
    bool found = false;

    for(const auto& task : tasks){
        auto it = std::find(task.tags.begin(), task.tags.end(), tag); 
        if(it != task.tags.end()) {
            std::cout << "================================================\n";
            std::cout << "ID задачи: " << task.id << "\n";
            std::cout << "Название задачи: " << task.name << "\n";
            std::cout << "Описание задачи: " << task.description << "\n";
            std::cout << "Выполнить до: " << std::chrono::format("%Y-%m-%d", task.deadline) << "\n";
            std::cout << "================================================\n\n";
            found = true;
        }
     
    }
    if(found == false) std::cout << "Задач с таким тегом не найдено. \n";
}

void TaskManager::save_tasks(){
    std::ofstream file("tasks.txt");

    if(file.is_open()){
        for(const auto& task : tasks){
            file << task.id << " "
                 << task.status << " " 
                 << task.deadline.time_since_epoch().count() << " " 
                 << static_cast<int>(task.level) << " " 
                 << task.tags.size() << " ";

            for(auto tag : task.tags){
                file << tag << " ";
            }
            file << "\n";
            file << task.name << "\n" << task.description << "\n";
        }
    }
}

void TaskManager::load_tasks(){
    std::ifstream file("tasks.txt");

    int id;
    while(file >> id){
        Task loaded_task;
        loaded_task.id = id;

        bool status;
        file >> status;
        loaded_task.status = status;

        long long deadline;
        file >> deadline;
        std::chrono::system_clock::time_point deadline_time{std::chrono::system_clock::duration{deadline}};
        loaded_task.deadline = deadline_time;

        int priority;
        file >> priority;
        loaded_task.level = static_cast<Priority>(priority);

        size_t tags_count;
        file >> tags_count;
        
        std::vector<std::string> local_tags;
        for(size_t i = 0; i < tags_count; i++){
            std::string tag;
            file >> tag;
            local_tags.push_back(tag);
        }
        loaded_task.tags = local_tags;

        file >> std::ws;

        std::getline(file, loaded_task.name);

        std::getline(file, loaded_task.description);
        
        tasks.push_back(loaded_task);
    }

    if(!tasks.empty()) next_id = tasks.back().id + 1;
    else next_id = 1;
}
