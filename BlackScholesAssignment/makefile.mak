PATH_TO_BUILD = /home/build

# Use Intel CPP compiler 
CC = icpc

# Compile-time flags 
CFLAGS = -std=c++11 -mmic -O3 
CFLAGS += -DEIGEN_FAST_MATH -DEIGEN_INITIALIZE_MATRICES_BY_ZERO -DEIGEN_NO_DEBUG -DBOOST_THREAD_PROVIDES_SHARED_MUTEX_UPWARDS_CONVERSIONS -DBOOST_ASIO_HAS_MOVE -DNDEBUG 
CFLAGS += -I"/usr/local/include/" -I"./BasicBinomialTest" -I"/usr/include/mysql/" -I"/usr/include/eigen3/"  -I"./x_sstool_client"  -I"./x_utils"  -I"./" -I"./x_client-server" 
CFLAGS += -lpthread -ltbb -multiple-processes=10 -align -opt-prefetch -fma -funroll-loops -ipo -ansi-alias -fno-math-errno -fno-alias -fargument-noalias -z defs -daz -ftz -no-prec-div -no-prec-sqrt -fimf-precision=low -fp-model fast=2
LDFLAGS = -mmic -L/usr/lib_our/mic_old/lib/6.1.6/ -L/var/shared/phi-libs/  /home/src_our/protobuf/protobuf-2.6.1-mic-aldr/src/.libs/libprotobuf.a  /usr/lib_our/icc-16.0.4/mic/release/tbb/libtbb.so -lmysqlclient -lpthread -Wl,-Bstatic -lboost_serialization -lboost_program_options -lboost_thread  -lboost_system -lboost_filesystem -lboost_log -lboost_atomic -lboost_log_setup -Wl,-Bdynamic
#LDFLAGS =  -L/usr/local/icc-16.0.4/mic/release/boost_1_55_0/ -L/usr/lib_our/mic_old/lib/6.1.6/ /usr/src_our/protobuf/protobuf-2.6.1-mic-aldr/src/.libs/libprotobuf.a
#LDFLAGS = -L/var/shared/phi-libs/ - old phi libs
#-L/usr/lib_our/mic_old/lib/6.1.6/ -L/home/src_our/boost_1_55_0/stage/lib/

###LDFLAGS = -mmic -L/var/shared/phi-libs/ /home/src_our/protobuf/protobuf-2.6.1-mic-aldr/src/.libs/libprotobuf.a  /usr/lib_our/icc-16.0.4/mic/release/tbb/libtbb.so -lmysqlclient -lpthread -Wl,-Bstatic -lboost_serialization -lboost_program_options -lboost_thread  -lboost_system -lboost_filesystem -lboost_log -lboost_atomic -lboost_log_setup -Wl,-Bdynamic 
###LDFLAGS =  -L/usr/local/icc-16.0.4/mic/release/boost_1_55_0/ -L/usr/lib_our/mic_old/lib/6.1.6/ /usr/src_our/protobuf/protobuf-2.6.1-mic-aldr/src/.libs/libprotobuf.a

#include $(PATH_TO_BUILD)/LibDynamic.tbb



# explicit subfolders
#CPP_FILES = $(wildcard ServerExample/*.cpp) $(wildcard libSRDF/*.cpp)

# all recursive subfolders
CPP_FILES_ALL = $(wildcard **/*.cpp)
CPP_FILES_ALL += Unittest/PricerTest/PricerBare.cpp

CC_FILES_ALL = $(wildcard **/*.cc)

CPP_FILES = $(filter-out Unittest/PricerTest/stdafx.cpp Unittest/PricerTest/PricerTest.cpp BasicBinomialTest/main.cpp x_utils/tz.cpp x_client-server/Connection.cpp x_client-server/ProtoBufClient.cpp, $(CPP_FILES_ALL))


OBJ_FILES = $(addprefix obj/,$(notdir $(CPP_FILES:.cpp=.o)))
OBJ_FILES += $(addprefix obj/,$(notdir $(CC_FILES_ALL:.cc=.o)))

#all: sr-test

fitter-phi: $(OBJ_FILES)
	$(CC) -o $@ $^ $(LDFLAGS)


# explicit folders
#obj/%.o: ServerExample/%.cpp libSRDF/%.cpp

obj/%.o: BasicBinomialTest/%.cpp
	$(CC) -c $(CFLAGS) -o $@ $^

obj/%.o: Unittest/%.cpp
	$(CC) -c $(CFLAGS) -o $@ $^

obj/PricerBare.o: Unittest/PricerTest/PricerBare.cpp
	$(CC) -c $(CFLAGS) -o $@ $^

obj/%.o: x_client-server/%.cpp
	$(CC) -c $(CFLAGS) -o $@ $^

obj/%.o: x_sstool_client/%.cpp
	$(CC) -c $(CFLAGS) -o $@ $^
	
obj/%.o: x_utils/%.cpp
	$(CC) -c $(CFLAGS) -o $@ $^

obj/%.o: x_client-server/%.cc
	$(CC) -c $(CFLAGS) -o $@ $^

obj/%.o: x_sstool_client/%.cc
	$(CC) -c $(CFLAGS) -o $@ $^

obj/%.o: ./%.cc
	$(CC) -c $(CFLAGS) -o $@ $^


clean: 
	rm -rf obj/*.o fitter-phi

