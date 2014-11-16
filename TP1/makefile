#compilacion y ejecucion de los archivos
CC       =  g++
CFLAGS   = -g -Wall  -pedantic -O2
OBJS	 = main.o   dictionary.o  cmdline.o options.o process.o printers.o complejo.o planoC.o  expression.o shuntingYard.o operation.o


muestras.exe:$(OBJS)
	$(CC)  $(OBJS) -o main.exe

main.o:main.cpp dictionary.hpp common.hpp cmdline.h options.hpp process.hpp printers.hpp complejo.hpp planoC.hpp
	$(CC) main.cpp -c -o main.o $(CFLAGS)

dictionary.o:dictionary.cpp dictionary.hpp cmdline.h  options.hpp
	$(CC) dictionary.cpp -c -o dictionary.o $(CFLAGS)

cmdline.o: cmdline.cc cmdline.h
	$(CC)  cmdline.cc -c -o cmdline.o $(CFLAGS)

options.o: options.cpp options.hpp dictionary.hpp
	$(CC)  options.cpp -c -o options.o $(CFLAGS)

process.o:process.cpp process.hpp dictionary.hpp common.hpp planoC.hpp
	$(CC) process.cpp -c -o process.o $(CFLAGS)

printers.o:printers.cpp printers.hpp common.hpp
	$(CC) printers.cpp -c -o printers.o $(CFLAGS)

complejo.o:complejo.cpp complejo.hpp
	$(CC) complejo.cpp -c -o complejo.o $(CFLAGS)

planoC.o:planoC.cpp planoC.hpp
	$(CC) planoC.cpp -c -o planoC.o $(CFLAGS)

expression.o:expression.cpp expression.hpp common.hpp
	$(CC) expression.cpp -c -o expression.o $(CFLAGS)

shuntingYard.o:shuntingYard.cpp shuntingYard.hpp operation.hpp common.hpp
	$(CC) shuntingYard.cpp -c -o shuntingYard.o $(CFLAGS)

operation.o:operation.cpp operation.hpp common.hpp binTree.hpp complejo.hpp
	$(CC) operation.cpp -c -o operation.o $(CFLAGS)

clean:
	rm *.o
