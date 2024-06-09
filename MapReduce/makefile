CXX = g++
CXXFLAGS = -std=c++17 -Wall -Iinclude -pthread
LDFLAGS = -L/usr/local/lib -lrpc -lpthread

# Directories
OBJ_DIR = obj
BIN_DIR = bin
MASTER_SRC_DIR = src/master
WORKER_SRC_DIR = src/worker

# Recursively find all .cpp files in src/ directory
MASTER_SRCS = $(wildcard $(MASTER_SRC_DIR)/*.cpp)
WORKER_SRCS = $(wildcard $(WORKER_SRC_DIR)/*.cpp)

# Create object files for each .cpp file
MASTER_OBJS = $(patsubst $(MASTER_SRC_DIR)/%.cpp,$(OBJ_DIR)/master/%.o,$(MASTER_SRCS))
WORKER_OBJS = $(patsubst $(WORKER_SRC_DIR)/%.cpp,$(OBJ_DIR)/worker/%.o,$(WORKER_SRCS))

# Executables
MASTER_BIN = $(BIN_DIR)/master
WORKER_BIN = $(BIN_DIR)/worker

all: directories $(MASTER_BIN) $(WORKER_BIN)

directories:
	mkdir -p $(OBJ_DIR)/master $(OBJ_DIR)/worker $(BIN_DIR)

$(MASTER_BIN): $(MASTER_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

$(WORKER_BIN): $(WORKER_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

$(OBJ_DIR)/master/%.o: $(MASTER_SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/worker/%.o: $(WORKER_SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
