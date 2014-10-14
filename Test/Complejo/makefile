#compilacion y ejecucion de los archivos
CC       =  g++
CFLAGS   = -g -Wall  -pedantic
OBJS	 = main.o complejo.o


muestras.exe:$(OBJS)
	$(CC)  $(OBJS) -o main.exe

main.o:main.cpp complejo.hpp
	$(CC) main.cpp -c -o main.o $(CFLAGS)

complejo.o:complejo.cpp complejo.hpp
	$(CC) complejo.cpp -c -o complejo.o $(CFLAGS)


clean:
	rm *.o
