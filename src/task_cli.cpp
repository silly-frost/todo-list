#include"task_cli.hpp"
#include<iostream>

namespace TaskCLI {

void main_menu(TaskManager& manager){
    while(true){
        clear_screen();
        int choice;
        
        std::cout << "Список действий: \n\n";
        std::cout << "1. Добавить задачу \n2. Удалить задачу \n3. Вывести список активных задач \n4. Пометить задачу выполненной (Это действие удалит задачу автоматически) \n5. Найти задачу по тегу \n0. Выйти\n\n";

        std::cout << "Что вы хотите сделать (1-5)? ";
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch(choice){
            case 0:
                clear_screen();
                std::cout << "Удачного дня! :)\n";
                return;
            case 1:
                clear_screen();
                handle_add_task(manager);
                break;
            case 2:
                clear_screen();
                handle_delete_task(manager);
                break;
            case 3:
                clear_screen();
                manager.print_all_tasks();
                break;
            case 4:
                clear_screen();
                handle_complete_task(manager);
                break;
            case 5:
                clear_screen();
                find_task_by_tag(manager);
                break;
            default:
                clear_screen();
                std::cout << "Вводите числа строго от 1 до 5!\n";
                wait_for_user();
                break;
        }
    }
}

int get_id(){
    std::cout << "Введите ID задачи: ";
    int id;
    std::cin >> id;
    return id;
}

void handle_delete_task(TaskManager& manager){
    manager.delete_task(get_id());
    wait_for_user();
}

void handle_complete_task(TaskManager& manager){
    manager.complete_task(get_id());
    wait_for_user();
}

void handle_add_task(TaskManager& manager){
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    std::cout << "Введите название задачи: ";
    std::string name;
    std::getline(std::cin, name);
    std::cout << "\n\n";

    std::cout << "Введите описание: ";
    std::string description;
    std::getline(std::cin, description);
    std::cout << "\n\n";

    std::cout << "Введите дату, до которой хотите выполнить задачу (ГГГГ-ММ-ДД): ";
    std::string date;
    std::getline(std::cin, date);
    std::stringstream date_stream(date);
    std::chrono::system_clock::time_point deadline; 
    std::chrono::from_stream(date_stream, "%Y-%m-%d", deadline);
    std::cout << "\n\n";

priority_mistake: //переносится сюда из блока default, если юзер ввёл неправильное число
    std::cout << "Список приоритетов: \n\n";
    std::cout << "1. Низкий \n2. Средний \n3. Высокий\n\n";
    std::cout << "Выберите один из вышеуказанных (1-3): ";
    int priority;
    Priority level;
    std::cin >> priority;
    switch(priority){
        case 1: 
            level = Priority::low;
            break;
        case 2:
            level = Priority::medium;
            break;
        case 3: 
            level = Priority::high;
            break;
        default:
            std::cout << "Введено неверное число. Попробуйте ещё раз. \n\n";
            goto priority_mistake;
    }
    std::cout << "\n\n";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');


tags_mistake: //переносится сюда из блока else if, если юзер неправильно написал слова да/нет 
    std::cout << "Вы хотите добавить теги для этой задачи (да/нет)? ";
    std::string tags_choice;
    std::vector<std::string> local_tags;
    std::getline(std::cin, tags_choice);
    if(tags_choice == "да" || tags_choice == "Да"){
        std::cout << "Вводите названия тегов через пробел: ";
        std::string tags;
        std::getline(std::cin, tags);

        std::stringstream tags_stream(tags);
        std::string temp_tag;
        while(tags_stream >> temp_tag) local_tags.push_back(temp_tag);
    }
    else if(tags_choice != "Да" && tags_choice != "да" && tags_choice != "Нет" && tags_choice != "нет"){
        std::cout << "Введён некорекктный ответ. Попробуйте ещё раз. \n\n";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        goto tags_mistake;
    }
    std::cout << "\n\n";

    std::cout << "Новая задача успешно создана! Удачи с выполнением! \n";
    manager.add_task(name, description, deadline, level, local_tags);

    wait_for_user();
}

void find_task_by_tag(TaskManager& manager){
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Введите тег для поиска: ";
    std::string tag;
    std::getline(std::cin, tag);
    manager.find_by_tag(tag);
}

}
