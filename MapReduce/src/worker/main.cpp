#include "worker.h"
#include<string>
#include<iostream>

int main(int argc, char* argv[]){
    Worker* worker = new Worker();
    int master_port = stoi((std::string)argv[1]);
    rpc::client client("localhost", 8080);
    client.call("hello");



    // if(worker->Initialize(master_port) == 0){
    //   worker->Poll();
      
    // }

    return 0;
}