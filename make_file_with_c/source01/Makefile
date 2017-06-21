CFLAGS=-I./
main: date_time.o main.o
	-mkdir build
	-mkdir build/libs/
	-mv date_time.o ./build/libs/date_time.o
	-mv main.o ./build/libs/main.o
clean:
	-rmdir build/
	-rm main main.o date_time.o
