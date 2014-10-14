#compilacion y ejecucion de los archivos
CC       =  g++
CFLAGS   = -g -Wall  -pedantic
OBJS	 = main.o expression.o


muestras.exe:$(OBJS)
	$(CC)  $(OBJS) -o main.exe

main.o:main.cpp expression.hpp
	$(CC) main.cpp -c -o main.o $(CFLAGS)

expression.o:expression.cpp expression.hpp
	$(CC) expression.cpp -c -o expression.o $(CFLAGS)


clean:
	rm *.o
