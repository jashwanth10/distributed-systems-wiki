#include "worker.h"
#include<string>
#include<iostream>

int main(int argc, char* argv[]){
    int my_port = stoi((std::string)argv[1]);
    Worker* worker = new Worker(my_port);

    if(worker->Initialize(my_port) == 0){
      worker->Poll(); 
    }

    return 0;
}