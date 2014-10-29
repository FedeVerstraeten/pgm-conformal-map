#compilacion y ejecucion de los archivos
CC       =  g++
CFLAGS   = -g -Wall  -pedantic
OBJS	 = main.o  


muestras.exe:$(OBJS)
	$(CC)  $(OBJS) -o main.exe

main.o:main.cpp binTree.hpp common.hpp
	$(CC) main.cpp -c -o main.o $(CFLAGS)

#binTree.o: binTree.hpp common.hpp
#	$(CC) binTree.hpp -c -o binTree.o $(CFLAGS)


clean:
	rm *.o
