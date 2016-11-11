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


all : encoder

encoder: encoder.o
	$(CCX) $(CXXFlags) $(LDFlags) -o encoder.exe  nn_auto_encoder.o encoder.o noise.o nn_util.o pa_util.o

encoder.o: encoder.cpp noise.o nn_util.o pa_util.o nn_auto_encoder.o
	$(CCX) $(CXXFlags) -c encoder.cpp nn_auto_encoder.o nn_util.o pa_util.o -o encoder.o

nn_auto_encoder.o: nn_auto_encoder.cpp noise.o nn_util.o pa_util.o
	$(CCX) $(CXXFlags) -c nn_auto_encoder.cpp nn_util.o pa_util.o -o nn_auto_encoder.o

noise.o: noise.cpp noise.h
	$(CCX) $(CXXFlags) -c noise.cpp -o noise.o

nn_util.o: nn_util.cpp nn_util.h pa_util.o
	$(CCX) $(CXXFlags) -c nn_util.cpp pa_util.o -o nn_util.o

pa_util.o: pa_util.cc pa_util.h
	$(CCX) $(CXXFlags) -c pa_util.cc -o pa_util.o

clean:
	rm *.o