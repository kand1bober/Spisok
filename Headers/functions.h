#include <iterator>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <assert.h>

#include "macros.h"

#ifndef LIST_FUNCTIONS_HEADER
#define LIST_FUNCTIONS_HEADER

typedef double ListElem;

const int START_LIST_SIZE = 10;

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

    good_free_insert,
    bad_free_insert,
    good_free_delete,
    bad_free_delete,
};

struct Free
{
    size_t spisok_size;
    size_t spisok_capacity;


    int* array;
    size_t array_size; 
    size_t array_capacity;

    int* next;
    size_t next_size;
    size_t next_capacity;

    int* prev;
    size_t prev_size;
    size_t prev_capacity;
};

struct List
{
    size_t spisok_size; //размер списка ( эмулированный тип хранения )
    size_t spisok_capacity;


    ListElem* array;
    size_t array_size;  //количество заполненных ячеек реального массива
    size_t array_capacity;

    int* next;
    size_t next_size;
    size_t next_capacity;

    int* prev;
    size_t prev_size;
    size_t prev_capacity;
};

struct Data
{
    List spisok;
    Free free;
};

//========================================
enum Errors ListCtor( struct Data* list );
enum Errors ListDtor( struct Data* data );
void ListDump( struct List* list, struct Free* free );
enum Errors ListInsert( struct List* list, struct Free* free, size_t pivot, ListElem* elem) ;
enum Errors ListDelete( struct List* list, struct Free* free, size_t pivot );
enum Errors ListTakeHead( struct List* list, size_t number, ListElem* elem );
enum Errors ListTakeTale( struct List* list, size_t number, ListElem* elem );
//=======================================

//=======================================
enum Errors FreeInsert( struct List* list, struct Free* free, int ip );
enum Errors FreeDelete( struct List* list, struct Free* free, int* ip );
//=======================================

//============ UTILITIES ===========
char* GetFilePath( char* filepath, const char* filename );
int CheckSize_t( size_t number );
void BufferResize( struct Writing_buffer* buffer );
//==================================


#endif