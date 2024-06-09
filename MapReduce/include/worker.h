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
        static void RunMap(std::string);
        static void RunReduce();

        int Initialize(int port);
        void Poll();
    
    private:
        int master_port; 
        void WordCountMap(std::vector<char> data);
        void WriteIntermediary(std::map<std::string, int>);
};

#endif