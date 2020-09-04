CC = gcc
CXX = g++
AR = ar

OPT = -O2
DEBUG = -g

CFLAGS = -Wall -pipe $(DEBUG) $(OPT) -fno-strict-aliasing -std=c++11 -Wl,-rpath,./

LIB_VERSION = 0.2.22
INCS = -I ../include
LIBS = ../lib/x64/libhftx64.so.${LIB_VERSION} \
	   ../lib/x64/libprotobuf.so.12 ../lib/x64/libbiz_messagex64.so -ldl

TARGET1 = simple
TARGET2 = chase_limitup

CPP_SOURCE_FILES1 = simple_strategy.cc
CPP_SOURCE_FILES2 = chase_limitup_strategy.cc

OBJS1 += $(patsubst %.cpp,%.o, $(CPP_SOURCE_FILES1))
OBJS2 += $(patsubst %.cpp,%.o, $(CPP_SOURCE_FILES2))

%.o:%.cc Makefile
	$(CXX) $(CFLAGS) -c -o $@ $< $(INCS)

%.o:%.cpp Makefile
	$(CXX) $(CFLAGS) -c -o $@ $< $(INCS)
	
%.o:%.c Makefile
	$(CC) $(CFLAGS) -c -o $@ $< $(INCS)

$(TARGET1): $(OBJS1)
	$(CXX) $(CFLAGS) $(INCS) -o $@ $^ $(LIBS)

$(TARGET2): $(OBJS2)
	$(CXX) $(CFLAGS) $(INCS) -o $@ $^ $(LIBS)

.PHONY: clean

all: $(TARGET1) ${TARGET2}

clean: 
	rm -rf $(TARGET1) ${TARGET2} *.o
