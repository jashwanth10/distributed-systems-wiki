#ifndef WORKER_H
#define WORKER_H

#include <vector>
#include <map>
#include <queue>
#include <rpc/client.h>
#include "ReduceResponse.h"
#include "MapResponse.h"

class Worker{
    public:
        Worker();
        int Initialize(int port);
        void Poll();
    
    private:
        int master_port; 
        void RunMap(std::string chunk_name);
        void RunReduce();
};

#endif