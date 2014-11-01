#compilacion y ejecucion de los archivos
CC       =  g++
CFLAGS   = -g -Wall  -pedantic
OBJS	 = main.o expression.o shuntingYard.o operation.o complejo.o


muestras.exe:$(OBJS)
	$(CC)  $(OBJS) -o main.exe

main.o:main.cpp expression.hpp shuntingYard.hpp operation.hpp common.hpp binTree.hpp complejo.hpp
	$(CC) main.cpp -c -o main.o $(CFLAGS)

expression.o:expression.cpp expression.hpp common.hpp
	$(CC) expression.cpp -c -o expression.o $(CFLAGS)

shuntingYard.o:shuntingYard.cpp shuntingYard.hpp operation.hpp common.hpp
	$(CC) shuntingYard.cpp -c -o shuntingYard.o $(CFLAGS)

operation.o:operation.cpp operation.hpp common.hpp binTree.hpp
	$(CC) operation.cpp -c -o operation.o $(CFLAGS)

complejo.o:complejo.cpp complejo.hpp
	$(CC) complejo.cpp -c -o complejo.o $(CFLAGS)


clean:
	rm *.o
