#include "worker.h"
#include <rpc/server.h>
#include <fstream>
#include <map>


Worker::Worker()
{
}

void Worker::Poll()
{   
    rpc::client client("localhost", Worker::master_port);
    while(true){
        client.call("assign_task");
    };
}

int Worker::Initialize(int port)
{
    Worker::master_port = port;
    rpc::server srv(8081);
    srv.bind("assign_map", Worker::RunMap);
    srv.bind("assign_reduce", Worker::RunReduce);
    srv.async_run();
    return 0;
}

void Worker::RunMap(std::string chunk_name)
{
    std::ifstream inputFile(chunk_name, std::ios::binary);
    const std::size_t buffer_size = 64 * 1024 * 1024;
    std::vector<char> buffer(buffer_size);
    std::size_t bytes_read;
    inputFile.read(buffer.data(), buffer_size);

}

void Worker::RunReduce()
{
    return;
}


void Worker::WordCountMap(std::vector<char> data)
{
    std::map<std::string, int> mp;
    std::string word = "";
    for(int i=0;i<data.size();i++){
        if(data[i] == ' ' || data[i] == '\n'){
            mp[word]++;
        }else{
            word += data[i];
        }
    }
    Worker::WriteIntermediary(mp);
}

void Worker::WriteIntermediary(std::map<std::string, int>)
{
}
