#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "macros.h"
#include "decoration.h"

#ifndef LIST_FUNCTIONS_HEADER
#define LIST_FUNCTIONS_HEADER

typedef double ListElem;

const int START_LIST_SIZE = 20;

const uint64_t POISON_VALUE = 0xBA5ED;

enum Errors
{
    good_ctor = 0,
    bad_ctor,
    good_dtor,
    bad_dtor,
    good_insert,
    bad_insert,
    good_delete,
    bad_delete,
    good_take,
    bad_take,

    good_write_bonds,
    bad_write_bonds,

    good_
};

struct List
{
    ListElem* array;
    size_t array_size;
    size_t array_capacity;

    int* next;
    size_t next_size;
    size_t next_capacity;

    int* prev;
    size_t prev_size;
    size_t prev_capacity;
};


enum Errors ListCtor( struct List* list );
enum Errors ListDtor( struct List* list );
enum Errors ListTakeHead( struct List* list, size_t number, ListElem* elem );
enum Errors ListTakeTale( struct List* list, size_t number, ListElem* elem );
enum Errors ListInsert( struct List* list, size_t pivot, ListElem* elem );
enum Errors ListDelete( struct List* list, size_t pivot );
void ListDump( struct List* list );

//============ UTILITIES ===========
char* GetFilePath( char* filepath, const char* filename );
int CheckSize_t( size_t number );
void BufferResize( struct Writing_buffer* buffer );
//==================================


#endif