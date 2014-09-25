#ifndef COMMON_HPP
#define COMMON_HPP

#define EXIT_PROGRAM 	 1
#define EXIT_SUCCESS 	 0
#define ERROR_PROCESS 	-1
#define MAGICNUM 	"P2"
#define ANCHO_IMAGEN 	20
#define ALTO_IMAGEN 	40


using namespace std;

typedef enum {
                OK,
                ERROR,
                ERROR_NULL_POINTER,
                ERROR_MEMORY_NO_AVAILABLE,
                ERROR_TEXT_LINE_INVALID
                }status_t;

#endif
