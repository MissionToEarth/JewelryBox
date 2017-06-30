USER_FLAG = 0
TARGET := ResolveLoclizedPlist
INCLUDE := -I./Main/ -I./Main/Class/ -I../../libs/C++
CXX := g++
CFLAGS := $(INCLUDE)
ifeq ($(USER_FLAG), debug)
CFLAGS += -g
endif
CXXFLAGS := $(CFLAGS) -std=c++11
LDFLAGS := -lc
# #除外するファイルを指定
# EXCLUDES = ./Main/Class/C_mix.cpp
SRCS := $(wildcard ./Main/*.cpp) $(wildcard Main/Class/*.cpp)
# SRCS := $(filter-out $(wildcard $(EXCLUDES), $(SRCS)))
OBJS := $(SRCS:%.cpp=%.o)

all: clean $(OBJS) $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) -o $@ $^ $(LDFLAGS)

clean:
	-rm $(OBJS)
	-rm $(TARGET)