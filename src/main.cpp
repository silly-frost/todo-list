#include"task_cli.hpp"

int main(){
    TaskManager manager;
    
    manager.load_tasks();
    TaskCLI::main_menu(manager);
    manager.save_tasks();
    return 0;
}:
