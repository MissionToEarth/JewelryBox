APPLICATION := myapp
SRCS := main.c
SRCS += 
OBJS := $(SRCS:%.c=%.o)

CFLAGS = -I./ -M -rdynamic # コンパイルのオプションだと思うぜ。
APP_LDFLAGS = -latomic

CC := gcc

ifeq (ad,ad)
CFLAGS += -g
endif


aaaa: $(APPLICATION)
	ls $(CFLAGS)
	ls $(SRCS)

.c.o:
	gcc -c $<

$(APPLICATION): $(OBJS)
	$(CC) -o $@ $^



clean:
	-rm ./libs/main.o
	-rmdir libs/
	
	-rmdir bin/ # ファイルがあったら消さないようにする。
