#include "../Headers/library.h"
#include "../Headers/functions.h"
#include "../Headers/decoration.h"


enum Errors ListCtor( struct List* list )
{
    list->array = (ListElem*)calloc( START_LIST_SIZE + 1, sizeof(ListElem) );

    ListElem buffer[] = { 12, 78, 5, 32, 87, 19, 64, 4, 93, 25, 56 };

    for(size_t i = 0; i < sizeof(buffer) / sizeof(ListElem); i++)
    {
        list->array[i +1] = buffer[i];
    }

    list->next = (int*)calloc(START_LIST_SIZE + 1, sizeof(int) );

    for(int i = 1; i < START_LIST_SIZE; i++)
    {
        list->next[i] = -1;
    }

    for(int i = 1; i < (int)(sizeof(buffer) / sizeof(ListElem)); i++)
    {
        list->next[i] = i + 1;
        list->next_size++;
    }


    if( (list->next) && (list->array) )
        return good_ctor;
    else
        return bad_ctor;
}


enum Errors ListDtor( struct List* list )
{
    free( list->next );
    free( list->array );

    if( (!list->next) && (!list->array) )
        return good_dtor;
    else
        return bad_dtor;
}


void ListDump( struct List* list )
{
    printf(GREEN "Next Dump:\n" DELETE_COLOR);
    for(int i = 0; i < START_LIST_SIZE + 1; i++)
    {
        printf("%d ", list->next[i] );
    }
    printf("\n\n");

    printf(GREEN "   Array Dump:         Next Dump:\n" DELETE_COLOR);
    for(int i = 0 ; i < START_LIST_SIZE + 1; i++)
    {
        printf(ORANGE "[%2d]" DELETE_COLOR ": %7.2lf     ----     %d\n", i, list->array[i], list->next[i] );
    }
    printf("\n\n");
}   


// enum Errors ListInsert( struct List* list )
// {

// }


// enum Errors ListDelete( struct List* list )
// {

// }

enum Errors ListTake( struct List* list, int number, ListElem* elem )
{
    int target = 1;  //TODO: везде пересмотреть работу с size_t
    for(int i = 0; (i < number - 1) && (i < (int)list->next_size); i++) //смещение на 1 из-за фантомного элемента
    {
        target = list->next[target];       
    }
    // printf("result: targ: %d\n", target);
    // printf("%lf\n", list->array[target] );

    if( list->array[target] != -1 )
    {
        *elem = list->array[target];
        return good_take;
    }
    else 
    {
        *elem = -1;
        printf("Trying to access empty memory part\n");
        return bad_take;
    }

}
