CFLAGS=-I./ -rdynamic //コンパイルのオプションだと思うぜ。
APP_LDFLAGS=-latomic

main: main.o 
	gcc -o myapp main.o
	-mkdir build/
	-mkdir build/libs build/bin
	-mv main.o ./build/libs
	mv myapp ./build/bin

clean:
	rm ./build/libs/main.o
	-rmdir build/libs/
	-rmdir build/bin/ # ファイルがあったら消さないようにする。
