CXX = g++
CXXFLAGS = -std=c++17 -Wall -Iinclude -pthread
LDFLAGS = -L/usr/local/lib -lrpc -lpthread

# Recursively find all .cpp files in src/ directory
MASTER_SRCS = $(shell find src/master -name '*.cpp')
WORKER_SRCS = $(shell find src/worker -name '*.cpp')
SRCS = $(MASTER_SRCS) $(WORKER_SRCS) $(COMMON_SRCS)

# Create object files for each .cpp file
MASTER_OBJS = $(MASTER_SRCS:.cpp=.o)
WORKER_OBJS = $(WORKER_SRCS:.cpp=.o)
COMMON_OBJS = $(COMMON_SRCS:.cpp=.o)

all: master worker

master: $(MASTER_OBJS) $(COMMON_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(MASTER_OBJS) $(COMMON_OBJS) $(LDFLAGS)

worker: $(WORKER_OBJS) $(COMMON_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(WORKER_OBJS) $(COMMON_OBJS) $(LDFLAGS)

clean:
	rm -f src/master/*.o src/worker/*.o master worker

src/master/%.o: src/master/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

src/worker/%.o: src/worker/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

