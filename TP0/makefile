#compilacion y ejecucion de los archivos
CC       =  g++
CFLAGS   = -g -Wall  -pedantic
OBJS	 = main.o   dictionary.o  cmdline.o options.o process.o



muestras.exe:$(OBJS)
	$(CC)  $(OBJS) -o main.exe

main.o:main.cpp dictionary.hpp common.hpp cmdline.h options.hpp
	$(CC) main.cpp -c -o main.o $(CFLAGS)

dictionary.o:dictionary.cpp dictionary.hpp cmdline.h  options.hpp
	$(CC) dictionary.cpp -c -o dictionary.o $(CFLAGS)

cmdline.o: cmdline.cc cmdline.h
	$(CC)  cmdline.cc -c -o cmdline.o $(CFLAGS)

options.o: options.cpp options.hpp
	$(CC)  options.cpp -c -o options.o $(CFLAGS)

process.o:process.cpp process.hpp dictionary.hpp common.hpp
	$(CC) process.cpp -c -o process.o $(CFLAGS)


clean:
	rm *.o
