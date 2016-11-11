# normally, I use cmake, but trying to keep example simple.

# if eigen3 is not in system search path
EIGENDIR =/usr/include/eigen3
EIGENOPT = 
# possible options
#EIGENOPT += -DEIGEN_NO_DEBUG 
EIGENOPT += -fopenmp  # let eigen use multiple cores for matrix multiplication
EIGENOPT += -DNDEBUG

CCX = g++
CXXFlags +=  --std=c++11 -I$(EIGENDIR) $(EIGENOPT)
LDFlags += -lm

# On linux, we need to add -lrt library for the BenchTimer code 
LDFlags += -lrt
SOURCE = source/
BIN = bin/

all : encoder

encoder: $(BIN)encoder.o
	$(CCX) $(CXXFlags) $(LDFlags) -o encoder.exe  $(BIN)encoder.o $(BIN)nn_auto_encoder.o $(BIN)nn_training_policy.o $(BIN)nn_encoding_layer.o $(BIN)nn_structs.o $(BIN)noise.o $(BIN)nn_util.o $(BIN)pa_util.o

$(BIN)encoder.o: $(SOURCE)encoder.cpp $(BIN)nn_auto_encoder.o $(BIN)nn_training_policy.o
	$(CCX) $(CXXFlags) -c $(SOURCE)encoder.cpp $(BIN)nn_auto_encoder.o $(BIN)nn_training_policy.o -o $(BIN)encoder.o

$(BIN)nn_auto_encoder.o: $(SOURCE)nn_auto_encoder.cpp $(SOURCE)nn_auto_encoder.h $(BIN)nn_encoding_layer.o
	$(CCX) $(CXXFlags) -c $(SOURCE)nn_auto_encoder.cpp $(BIN)nn_encoding_layer.o -o $(BIN)nn_auto_encoder.o

$(BIN)nn_encoding_layer.o: $(SOURCE)nn_encoding_layer.cpp $(SOURCE)nn_encoding_layer.h $(BIN)nn_structs.o $(BIN)nn_training_policy.o $(BIN)noise.o
	$(CCX) $(CXXFlags) -c $(SOURCE)nn_encoding_layer.cpp $(BIN)nn_structs.o $(BIN)nn_training_policy.o $(BIN)noise.o -o $(BIN)nn_encoding_layer.o

$(BIN)nn_structs.o: $(SOURCE)nn_structs.cpp $(SOURCE)nn_structs.h $(BIN)nn_util.o
	$(CCX) $(CXXFlags) -c $(SOURCE)nn_structs.cpp $(BIN)nn_util.o -o $(BIN)nn_structs.o

$(BIN)nn_training_policy.o: $(SOURCE)nn_training_policy.cpp $(SOURCE)nn_training_policy.h $(BIN)nn_util.o
	$(CCX) $(CXXFlags) -c $(SOURCE)nn_training_policy.cpp $(BIN)nn_util.o -o $(BIN)nn_training_policy.o

$(BIN)noise.o: $(SOURCE)noise.cpp $(SOURCE)noise.h
	$(CCX) $(CXXFlags) -c $(SOURCE)noise.cpp -o $(BIN)noise.o

$(BIN)nn_util.o: $(SOURCE)nn_util.cpp $(SOURCE)nn_util.h $(BIN)pa_util.o
	$(CCX) $(CXXFlags) -c $(SOURCE)nn_util.cpp $(BIN)pa_util.o -o $(BIN)nn_util.o

$(BIN)pa_util.o: $(SOURCE)pa_util.cc $(SOURCE)pa_util.h
	$(CCX) $(CXXFlags) -c $(SOURCE)pa_util.cc -o $(BIN)pa_util.o

clean:
	rm $(BIN)*.o