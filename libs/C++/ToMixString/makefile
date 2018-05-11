CXX = g++
TARGET = mixstring
CXXFLAGS = -Wall -O2 -pipe
SRCS = key_string_maker.cpp
OBJS := $(SRCS:.cpp=.o) #SRCSの各ファイルのサフィックスの.cppを.oに変換

$(TARGET): $(OBJS)
	$(CXX) -std=c++11 -stdlib=libc++ -o $@ $(OBJS)

