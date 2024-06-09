#include "worker.h"
#include <rpc/server.h>
#include <fstream>
#include <map>


Worker::Worker(int port): port(port), running(false)
{   
    master_instance = new rpc::client("localhost", 8080);
    
    server_instance = new rpc::server(port);
    server_instance->bind("assign_map", Worker::RunMap);
    server_instance->bind("assign_reduce", Worker::RunReduce);
    server_instance->async_run();
}

void Worker::Poll()
{   
    while(true){
        if(!Worker::running)
        {
            std::pair<int, std::string> task = master_instance->call("assign_task").as<std::pair<int, std::string>>();
            if(task.first == 0)
            {
                RunMap(task.second);
            }
            else if (task.first == 1)
            {
                RunReduce();
            }
            else
            {
                continue;
            }
        }
    };
}

int Worker::Initialize(int port)
{
    Worker::port = 8080;
    return 1;
}

std::string Worker::RunMap(std::string chunk_name)
{
    std::ifstream inputFile(chunk_name, std::ios::binary);
    const std::size_t buffer_size = 64 * 1024 * 1024;
    std::vector<char> buffer(buffer_size);
    std::size_t bytes_read;
    inputFile.read(buffer.data(), buffer_size);

    std::map<std::string, int> inter_map = parse_document(buffer);

    std::string intermediary_file = write_intermediary(inter_map);

    return intermediary_file;

}

void Worker::RunReduce()
{
    return;
}

std::map<std::string, int> Worker::parse_document(std::vector<char> data)
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
    return mp;
}

std::string Worker::write_intermediary(std::map<std::string, int> mp)
{
    for(auto it: mp){}
    return std::string();
}
