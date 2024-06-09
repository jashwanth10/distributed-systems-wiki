#ifndef MASTER_H
#define MASTER_H

#include <vector>
#include <map>
#include <queue>
#include <rpc/client.h>
#include <rpc/server.h>
#include "ReduceResponse.h"
#include "MapResponse.h"

class Master{
    public:
        Master();
        int Initialize(std::vector<std::string> workers);
        void Run(std::vector<std::string> files);
        static void hello_world();

    
    private:
        std::unique_ptr<rpc::server> server;
        std::vector<std::unique_ptr<rpc::client>> workers;
        std::queue<std::unique_ptr<rpc::client>> idle_workers;
        std::queue<std::string> intermediary_locations;

        static void* threadFunctionWrapper(void* arg) 
        {
            Master* instance = static_cast<Master*>(arg);
            instance->RunServer();
            return nullptr;
        }

        void RunServer();
};

#endif