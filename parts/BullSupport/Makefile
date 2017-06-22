APPLICATION := myapp
INCLUDE := -I/Main/Class/ -I.
SRCS := Main/main.cpp
SRCS += Main/Class/LocalizedPlist.cpp
OBJS := $(SRCS:%.c=%.o)

CFLAGS = -I./ -M -rdynamic # コンパイルのオプションだと思うぜ。
APP_LDFLAGS = -latomic

CXX := gcc

ifeq (ad,ad)
CFLAGS += -g -Isub_dir
endif


main: $(APPLICATION)
	ls $(CFLAGS)
	ls $(SRCS)

.c.o:
	gcc -c $<

$(APPLICATION): $(OBJS)
	$(CXX) $(CFLAGS) $(INCLUDE) -o $@ $^



clean:
	-rm ./libs/main.o
	-rmdir libs/
	
	-rmdir bin/ # ファイルがあったら消さないようにする。
