# normally, I use cmake, but trying to keep example simple.

# if eigen3 is not in system search path
EIGENDIR =/usr/include/eigen3
EIGENOPT = 
# possible options
#EIGENOPT += -DEIGEN_NO_DEBUG 
EIGENOPT += -fopenmp  # let eigen use multiple cores for matrix multiplication
#EIGENOPT += -DNDEBUG t

CCX = g++
CXXFlags +=  --std=c++11 -I$(EIGENDIR)
LDFlags += -lm

# On linux, we need to add -lrt library for the BenchTimer code 
LDFlags += -lrt
SOURCE_DIR = source/
BIN_DIR = bin/

all : fann

fann: $(BIN_DIR)fann.o
	$(CCX) $(CXXFlags) -o fann.exe $(BIN_DIR)fann.o $(BIN_DIR)fann_structs.o $(BIN_DIR)pa_util.o

$(BIN_DIR)fann.o: $(SOURCE_DIR)fann_test.cpp $(BIN_DIR)fann_structs.o $(BIN_DIR)pa_util.o
	$(CCX) $(CXXFlags) -c $(SOURCE_DIR)fann_test.cpp $(BIN_DIR)fann_structs.o $(BIN_DIR)pa_util.o -o $(BIN_DIR)fann.o

$(BIN_DIR)fann_structs.o: $(SOURCE_DIR)fann_structs.cpp $(BIN_DIR)pa_util.o
	$(CCX) $(CXXFlags) -c $(SOURCE_DIR)fann_structs.cpp $(BIN_DIR)pa_util.o -o $(BIN_DIR)fann_structs.o

test: $(BIN_DIR)test.o 
	$(CCX) $(CXXFlags) -o test.exe $(BIN_DIR)test.o $(BIN_DIR)noise.o $(BIN_DIR)net_layer_manager.o $(BIN_DIR)net_structs.o $(BIN_DIR)pa_util.o

$(BIN_DIR)test.o: $(SOURCE_DIR)test.cpp $(BIN_DIR)noise.o $(BIN_DIR)net_layer_manager.o $(BIN_DIR)net_structs.o $(BIN_DIR)pa_util.o
	$(CCX) $(CXXFlags) -c $(SOURCE_DIR)test.cpp $(BIN_DIR)noise.o $(BIN_DIR)net_layer_manager.o $(BIN_DIR)net_structs.o $(BIN_DIR)pa_util.o -o$(BIN_DIR)test.o

$(BIN_DIR)noise.o: $(SOURCE_DIR)noise.cpp $(SOURCE_DIR)noise.h
	$(CCX) $(CXXFlags) -c $(SOURCE_DIR)noise.cpp -o$(BIN_DIR)noise.o

eigentest: $(BIN_DIR)eigen_test.o
	$(CCX) $(CXXFlags) -o eigen_test.exe $(BIN_DIR)eigen_test.o

$(BIN_DIR)eigen_test.o: $(SOURCE_DIR)eigen_test.cpp $(SOURCE_DIR)eigen_test.h
	$(CCX) $(CXXFlags) -c $(SOURCE_DIR)eigen_test.cpp -o$(BIN_DIR)eigen_test.o

$(BIN_DIR)net_layer_manager.o: $(SOURCE_DIR)net_layer_manager.cpp $(SOURCE_DIR)net_layer_manager.h $(BIN_DIR)net_structs.o $(BIN_DIR)pa_util.o
	$(CCX) $(CXXFlags) -c $(SOURCE_DIR)net_layer_manager.cpp $(BIN_DIR)net_structs.o $(BIN_DIR)pa_util.o -o$(BIN_DIR)net_layer_manager.o

$(BIN_DIR)net_structs.o: $(SOURCE_DIR)net_structs.cpp $(SOURCE_DIR)net_structs.h
	$(CCX) $(CXXFlags) -c $(SOURCE_DIR)net_structs.cpp -o$(BIN_DIR)net_structs.o

$(BIN_DIR)pa_util.o: $(SOURCE_DIR)pa_util.cc $(SOURCE_DIR)pa_util.h
	$(CCX) $(CXXFlags) -c $(SOURCE_DIR)pa_util.cc -o$(BIN_DIR)pa_util.o

clean:
	rm $(BIN_DIR)* 
