#include "master.h"
#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <rpc/client.h>
#include <rpc/server.h>
#include <rpc/rpc_error.h> 
#include <thread>
#include "ReduceResponse.h"
#include "MapResponse.h"

namespace fs = std::filesystem;

Master::Master() : server(std::make_unique<rpc::server>(8080))
{
    Master::server->bind("hello", Master::hello_world);
    Master::server->async_run();
}

int Master::Initialize(std::vector<std::string> workers)
{
    for(std::string worker: workers)
    {
        auto client = std::make_unique<rpc::client>("localhost", stoi(worker));
        Master::idle_workers.push(std::move(client));
    }
    return 0;
}

void Master::Run(std::vector<std::string>files)
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
            std::string chunk_file = "./.tmp/.chunks/chunk_" + filename + "_" + std::to_string(chunk_number);
            std::ofstream outputFile(chunk_file);
            if (outputFile.is_open()) 
            {
                outputFile.write(buffer.data(),  bytes_read);   
                std::cout<<"Written into chunk: "<<chunk_file<<std::endl;
            }
            else{
                std::cerr << "Failed to create chunk" << std::endl;
                inputFile.close();
                return;
            }

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
        auto& worker = Master::idle_workers.front();
        int status = -1;
        try {
            worker->call("assign_map_task", status);
        }
        catch(const rpc::system_error& e){
            std::this_thread::sleep_for(std::chrono::seconds(2));
            std::cerr<<"Worker is not up!"<<std::endl;
        }

        // Master::intermediary_locations.push(map_response.chunk_location);
        if(status == 1){
            Master::idle_workers.pop();
        }
    }


}

void Master::RunServer()
{
    
}

void Master::hello_world()
{
    std::cout<<"Hello"<<std::endl;
}