CXX = clang++
TARGET1 = csv2key_store
CXXFLAGS = -Wall -O2 -pipe -std=c++11 -stdlib=libc++
SRCS1 = main.cpp
OBJS1 := $(SRCS1:.cpp=.o) #SRCSの各ファイルのサフィックスの.cppを.oに変換

all: $(TARGET1) 
$(TARGET1): $(OBJS1)
	$(CXX) -o $@ $(OBJS1)
