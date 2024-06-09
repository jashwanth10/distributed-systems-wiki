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
        std::pair<int, std::string> assign_task();

    
    private:
        std::unique_ptr<rpc::server> server;
        std::vector<std::unique_ptr<rpc::client>> workers;
        std::vector<std::unique_ptr<rpc::client>> idle_workers;
        std::queue<std::string> intermediary_locations;

        std::vector<int> is_idle;
        std::unordered_set<std::string> processed_chunks;
        std::unordered_set<std::string> processed_intermediaries;

        int phase = 0;
        int total_chunks;

};

#endif