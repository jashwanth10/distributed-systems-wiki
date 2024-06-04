#include "worker.h"
#include<string>

int main(int argc, char* argv[]){
    Worker* worker = new Worker();
    int master_port = stoi((std::string)argv[1]);
    rpc::client client("localhost", master_port);

    if(worker->Initialize(master_port) == 0){
      worker->Poll();
      
    }

    return 0;
}