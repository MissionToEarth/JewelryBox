APPLICATION := myapp
INCLUDE := -I./Main/ -I./Main/Class/ -I../../libs/C++
SRCS := Main/main.cpp
SRCS += Main/Class/LocalizedPlist.cpp
OBJS := $(SRCS:%.cpp=%.o)

# コンパイルのオプションだと思うぜ。
CFLAGS = -M -rdynamic 
APP_LDFLAGS = -latomic

CXX := gcc

ifeq (ad,ad)
CFLAGS += -g -Isub_dir
endif


test3: main.o LocalizedPlist.o
	g++ -std=c++11 -lc $(INCLUDE) -o $@ $^
main.o: Main/main.cpp
	g++ -std=c++11 -lc $(INCLUDE) -o $@ -c $^
LocalizedPlist.o: Main/Class/LocalizedPlist.cpp
	g++ -std=c++11 -lc $(INCLUDE) -o $@ -c $^
