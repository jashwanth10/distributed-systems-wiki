#include <iostream>
#include <vector>

#include <rpc/client.h>
#include "master.h"

int main(int argc, char* argv[]){


    std::vector<std::string> files;
    std::vector<std::string> workers;

    for(int i=0;i<argc;i++){
        if(i < argc && strcmp(argv[i], "--files") == 0){
            i++;
            while(i < argc && argv[i][0] != '-'){
                files.push_back((std::string)argv[i]);
                i++;
            }
        }
        if(i<argc && strcmp(argv[i], "--workers") == 0){
            i++;
            while(i < argc && argv[i][0] != '-'){
                workers.push_back(argv[i]);
                i++;
            }
        }
    }
    // Master
    Master* master_node = new Master();
    if(master_node->Initialize(workers) != -1)
    {
        master_node->Run(files);
        std::cout<<"Operation complete"<<std::endl;
    }
    else
    {
        std::cout<<"Error with connecting Worker Nodes"<<std::endl;
    }
    
    return 0;
}