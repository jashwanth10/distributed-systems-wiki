#ifndef WORKER_H
#define WORKER_H

#include <vector>
#include <map>
#include <queue>
#include <rpc/client.h>
#include <rpc/server.h>
#include "ReduceResponse.h"
#include "MapResponse.h"

class Worker{
    public:
        Worker(int port);
        static std::string RunMap(std::string);
        static void RunReduce();

        int Initialize(int port);
        void Poll();
    
    private:
        int port;
        bool running;
        rpc::server* server_instance;
        rpc::client* master_instance;

        // Util functions
        static std::map<std::string, int> parse_document(std::vector<char> data);
        static std::string write_intermediary(std::map<std::string, int>);


};

#endif