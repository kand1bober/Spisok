#include <stdlib.h>
#include <stdio.h>

#include "library.h"

#ifndef LIST_FUNCTIONS_HEADER
#define LIST_FUNCTIONS_HEADER

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
};

const int START_LIST_SIZE = 50;
enum Errors ListCtor( struct List* list );
enum Errors ListDtor( struct List* list );

enum Errors ListTake( struct List* list, int number, ListElem* elem );


void ListDump( struct List* list );



#endif