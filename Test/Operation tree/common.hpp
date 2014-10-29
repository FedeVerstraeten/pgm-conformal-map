#ifndef COMMON_HPP
#define COMMON_HPP

#include <iostream>
#include <stdlib.h>

using namespace std;

typedef enum {
                OK,
                ERROR,
                ERROR_NULL_POINTER,
                ERROR_MEMORY_NO_AVAILABLE,
                ERROR_INVALID_TOKEN,
                ERROR_INSERT_TREE_NODE
                }status_t;

#endif
