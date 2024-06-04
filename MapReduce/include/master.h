#ifndef MASTER_H
#define MASTER_H

#include <vector>
#include <map>
#include <queue>
#include <rpc/client.h>
#include "ReduceResponse.h"
#include "MapResponse.h"

class Master{
    public:
        Master();
        int Initialize(std::vector<char*> workers);
        void Run(std::vector<char*> files);
    
    private:
        std::vector<rpc::client> workers;
        std::queue<rpc::client> idle_workers;
        std::queue<std::string> intermediary_locations;

        static void* threadFunctionWrapper(void* arg) 
        {
            Master* instance = static_cast<Master*>(arg);
            instance->RunServer();
            return nullptr;
        }

        ReduceResponse AssignReduce();
        MapResponse assignMap();
        void WriteIntermediate();
        void RunServer();
};

#endif