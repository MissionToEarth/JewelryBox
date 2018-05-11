CXX = clang++
TARGET1 = mix_string
TARGET2 = make_cpp
CXXFLAGS = -Wall -O2 -pipe -std=c++11 -stdlib=libc++
SRCS1 = key_string_maker.cpp
SRCS2 = key_store_template.cpp
OBJS1 := $(SRCS1:.cpp=.o) #SRCSの各ファイルのサフィックスの.cppを.oに変換
OBJS2 := $(SRCS2:.cpp=.o) #SRCSの各ファイルのサフィックスの.cppを.oに変換

all: $(TARGET1) $(TARGET2)
$(TARGET1): $(OBJS1)
	$(CXX) -o $@ $(OBJS1)
$(TARGET2): $(OBJS2)
	$(CXX) -o $@ $(OBJS2)

