APPLICATION := myapp
INCLUDE := -I./Main/ -I./Main/Class/ -I../../libs/C++
SRCS := Main/main.cpp
SRCS += Main/Class/LocalizedPlist.cpp
OBJS := $(SRCS:%.cpp=%.o)
OUTDIR := Build

# コンパイルのオプションだと思うぜ。
CFLAGS = -M -rdynamic 
APP_LDFLAGS = -latomic

CXX := gcc

ifeq (ad,ad)
CFLAGS += -g -Isub_dir
endif

.PHONY:app
$(OUTDIR)/app: $(OUTDIR)/main.o $(OUTDIR)/LocalizedPlist.o
	-mkdir $(OUTDIR)/
	g++ -std=c++11 -lc $(INCLUDE) -o $@ $^
$(OUTDIR)/main.o: Main/main.cpp
	g++ -std=c++11 -lc $(INCLUDE) -o $@ -c $^
$(OUTDIR)/LocalizedPlist.o: Main/Class/LocalizedPlist.cpp
	g++ -std=c++11 -lc $(INCLUDE) -o $@ -c $^
