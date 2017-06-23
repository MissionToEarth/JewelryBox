APPLICATION := ResolveLoclizedPlist
CXX := clang++
CFLAGS = -M -rdynamic 
CXXFLAGS :=
APP_LDFLAGS = -latomic
INCLUDE := -I./Main/ -I./Main/Class/ -I../../libs/C++
SRCS := Main/main.cpp
SRCS += Main/Class/LocalizedPlist.cpp
OBJS := $(SRCS:%.cpp=%.o)
OUTDIR := Build

ifeq (ad,ad)
CFLAGS += -g -Isub_dir
endif



.PHONY:$(APPLICATION)
$(APPLICATION): $(OUTDIR)/main.o $(OUTDIR)/LocalizedPlist.o
	$(CXX) -std=c++11 -lc $(INCLUDE) -DDEBUG -o $@ $^
$(OUTDIR)/main.o: Main/main.cpp
	-mkdir $(OUTDIR)/
	$(CXX) -std=c++11 -lc $(INCLUDE) -DDEBUG -o $@ -c $^
$(OUTDIR)/LocalizedPlist.o: Main/Class/LocalizedPlist.cpp
	-mkdir $(OUTDIR)/
	$(CXX) -std=c++11 -lc $(INCLUDE) -DDEBUG -o $@ -c $^
