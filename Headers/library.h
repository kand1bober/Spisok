#include <stdio.h>

#ifndef SPISOK_LIBRARY_HEADER
#define SPISOK_LIBRARY_HEADER

typedef double ListElem;

struct List
{
    ListElem* array;
    int* next;
    size_t next_size;

};

#endif
