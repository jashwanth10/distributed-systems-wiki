CXX = g++
CXXFLAGS = -std=c++17 -Wall -I/usr/local/include -I/usr/local/include/absl -Ibuild -Isrc -pthread
LDFLAGS = -L/usr/local/lib -lgrpc++ -lgrpc -lprotobuf -labsl_base -labsl_log_severity -labsl_strings -lpthread

PROTOC = protoc
GRPC_CPP_PLUGIN = /usr/bin/grpc_cpp_plugin
PROTO_SRC = proto/mapreduce.proto
PROTO_GEN_CC = build/mapreduce.pb.cc build/mapreduce.grpc.pb.cc
PROTO_GEN_HDR = build/mapreduce.pb.h build/mapreduce.grpc.pb.h

# Recursively find all .cpp files in src/ directory
MASTER_SRCS = $(shell find src/master -name '*.cpp')
MASTER_OBJS = $(MASTER_SRCS:.cpp=.o)

WORKER_SRCS = $(shell find src/worker -name '*.cpp')
WORKER_OBJS = $(WORKER_SRCS:.cpp=.o)

all: master worker

build/%.grpc.pb.cc build/%.grpc.pb.h: proto/%.proto
	$(PROTOC) --grpc_out=build --plugin=protoc-gen-grpc=$(GRPC_CPP_PLUGIN)	$<

build/%.pb.cc build/%.pb.h: proto/%.proto
	$(PROTOC) --cpp_out=build	$<

master: $(MASTER_OBJS) $(PROTO_GEN_CC)
	$(CXX) $(CXXFLAGS) -o $@ $(MASTER_OBJS) $(PROTO_GEN_CC) $(LDFLAGS)

worker: $(WORKER_OBJS) $(PROTO_GEN_CC)
	$(CXX) $(CXXFLAGS) -o $@ $(WORKER_OBJS) $(PROTO_GEN_CC) $(LDFLAGS)

clean:
	rm -f src/**/*.o master worker $(PROTO_GEN_CC) $(PROTO_GEN_HDR)

src/master/%.o: src/master/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

src/worker/%.o: src/worker/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
