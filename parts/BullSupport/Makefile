USER_FLAG = 0
TARGET := ResolveLoclizedPlist
INCLUDE := -I./Main/ -I./Main/Class/
CXX := g++
CFLAGS := $(INCLUDE)
ifeq ($(USER_FLAG), debug)
CFLAGS += -g
endif
CXXFLAGS := $(CFLAGS) -std=c++11
LDFLAGS := -lc
SRCS := $(wildcard ./Main/*.cpp) $(wildcard Main/Class/*.cpp)
OBJS := $(SRCS:%.cpp=%.o)

all: clean $(OBJS) $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) -o $@ $^ $(LDFLAGS)

clean:
	-rm $(OBJS)
	-rm $(TARGET)