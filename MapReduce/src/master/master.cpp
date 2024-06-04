#include "master.h"
#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <rpc/client.h>
#include <rpc/server.h>
#include "ReduceResponse.h"
#include "MapResponse.h"

namespace fs = std::filesystem;

Master::Master() {}

int Master::Initialize(std::vector<char*> workers)
{
    for(auto worker: workers)
    {
        rpc::client client("localhost", stoi((std::string)worker));
        Master::workers.push_back(client);
        Master::idle_workers.push(client);
    }
    return 0;
}

void Master::Run(std::vector<char *> files)
{   
    // tmp diectory
    fs::path chunk_directory = "./.tmp/.chunks";
    if(!fs::exists(chunk_directory))
    {
        fs::create_directory(chunk_directory);
    }

    // chunk the input files into 64 MB sized files   
    for(auto filename: files)
    {

        // Open the file
        std::string file = "./files/" + (std::string)filename;
        std::ifstream inputFile(file, std::ios::binary);
        if (!inputFile.is_open())
        {
            std::cerr << "Failed to open the file: " << filename << std::endl;
            return;
        }
        
        // Define buffer constraints
        const std::size_t buffer_size = 64 * 1024 * 1024;
        std::vector<char> buffer(buffer_size);
        std::size_t bytes_read;

        // Read the file & write into chunk files
        int chunk_number = 0;
        do{
            inputFile.read(buffer.data(), buffer_size);
            bytes_read = inputFile.gcount();
            if(bytes_read == 0)
            {
                break;
            }

            // write into chunk file
            std::string chunk_file = "./tmp/.chunks/chunk_" + std::to_string(chunk_number);
            std::ofstream outputFile(chunk_file);
            if (!outputFile.is_open()) 
            {
                std::cerr << "Failed to create chunk" << std::endl;
                inputFile.close();
                return;
            }

            outputFile.write(buffer.data(),  bytes_read);

            if(!outputFile)
            {
                std::cerr << "Failed to write into the chunk." << std::endl;
                inputFile.close();
                outputFile.close();
                return;
            }

            chunk_number++;


        }while(bytes_read == buffer_size);

    }

    Master::RunServer();
    
    // Assign Map tasks
    while(!Master::idle_workers.empty())
    {
        int status = Master::idle_workers.front().call("assign_map_task").as<int>();
        // Master::intermediary_locations.push(map_response.chunk_location);
        if(status == 1){
            Master::idle_workers.pop();
        }
    }


}

void Master::RunServer()
{
    rpc::server srv(8080);
    srv.bind("write_intermediate_location", Master::WriteIntermediate);
    srv.bind("request_reduce", Master::AssignReduce);
    srv.async_run();
    return;
}

void Master::WriteIntermediate()
{
    return;
}

MapResponse Master::assignMap()
{   
    return;
}

ReduceResponse Master::AssignReduce()
{   

    return;
}