#include "../Headers/functions.h"
#include "../Headers/decoration.h"

enum Errors ListCtor( struct List* list )
{
    list->array = (ListElem*)calloc( START_LIST_SIZE, sizeof(ListElem) );
    list->next = (int*)calloc(START_LIST_SIZE, sizeof(int) );
    list->prev = (int*)calloc(START_LIST_SIZE, sizeof(int) );

    list->array_capacity = START_LIST_SIZE;
    list->next_capacity = START_LIST_SIZE;
    list->prev_capacity = START_LIST_SIZE;

    list->array_size = 0;
    list->next_size = list->array_size;
    list->prev_size = list->array_size;
    list->working_size = list->array_size;

    //===========заполнение массива индексов=================

    ON_DEBUG( printf(YELLOW "Size of:\narray: %lu\nofnext: %lu\nof prev: %lu\n\n" DELETE_COLOR, list->array_size, list->next_size, list->prev_size); )

    //=============NEXTS=======================
    for(size_t i = 0; i < list->array_capacity; i++)
    {
        list->next[i] = i + 1;
        ON_DEBUG( printf(RED "next[%lu]: %d\n" DELETE_COLOR, i, list->next[i]); )
    }
    ON_DEBUG( printf(SINIY "next_capacity = %lu\n\n" DELETE_COLOR, list->next_capacity); )

    //===============PREVS=====================
    *(list->prev) = list->array_capacity - 1;
    ON_DEBUG( printf(GREEN "prev[0]: %d\n" DELETE_COLOR, *(list->prev) ); )

    for(size_t g = 1; g < list->array_capacity; g++ )
    {
        *(list->prev + g) = g - 1;
        ON_DEBUG( printf(GREEN "prev[%lu]: %d\n" DELETE_COLOR, g, *(list->prev + g) ); )
    }
    ON_DEBUG( printf(SINIY "prev_capacity: %lu\n\n" DELETE_COLOR, list->prev_capacity); )
    //=========================================

    if( (list->next) && (list->array) )
        return good_ctor;
    else
        return bad_ctor;
}


enum Errors ListDtor( struct List* list )
{
    free( list->next );
    free( list->array );
    free( list->prev );

    if( (!list->next) && (!list->array) )
        return good_dtor;
    else
        return bad_dtor;
}


void ListDump( struct List* list )
{   
    printf(GREEN "\n[i]  Array Dump      Next    Prev     [i]\n" DELETE_COLOR);
    for(size_t i = 0 ; i < list->array_capacity; i++)
    {
        printf(ORANGE "[%02lu]" DELETE_COLOR "  %7.2lf   ---  %3d    %3d      " ORANGE "[%02lu]" DELETE_COLOR "\n", i, list->array[i], list->next[i], list->prev[i], i );
    }
    printf("\n\n");
}   

// enum Errors ListPush( struct List* list )

//=====первая версия Insert=======
enum Errors ListInsert( struct List* list, size_t pivot, ListElem* elem) 
{
    assert( list );

    ON_DEBUG( printf(GREEN "\n=== START OF INSERT ===\n" DELETE_COLOR); )

    if( pivot > list->array_capacity )
        return bad_insert;

    if( pivot < list->array_size )
    {
        *(ListElem*)(list->array + pivot ) = *elem; 
        list->working_size++;
        list->next_size++;  
        list->prev_size++;
        list->array_size++;   
        return good_insert;
    }
    else 
    {
        *(ListElem*)(list->array + list->array_size ) = *elem;  
        *(ListElem*)(list->array + pivot ) = *elem; 
        list->working_size++;
        list->next_size++;  
        list->prev_size++;
        list->array_size++;
    }

    size_t next_target = 0, prev_target = 0;

    //===================NEXTS===================================
    for(size_t i = 0; i < pivot - 1; i++)
    {
        next_target = *(list->next + next_target);
        ON_DEBUG( printf(SINIY "next_target: %lu\n" DELETE_COLOR, next_target); )
    }
    //=============меняем значение next предыдущего перед вставляемым и последнего  
    size_t pivot_next_target = *(list->next + next_target);
    ON_DEBUG( printf(RED "pivot_next_target: %lu\n" DELETE_COLOR, pivot_next_target); )

    //размер только рабочей области, поэтому везде вылазит (+1), а (++) это увеличение реального размера
    *(list->next + next_target) = list->next_size;
    *(list->next + list->next_size) = pivot_next_target;
    //============================================================

    //==================PREVS=====================================
    for(size_t i = 0; i < (list->working_size - pivot ); i++)
    {
        prev_target = *(list->prev + prev_target);
        ON_DEBUG( printf(SINIY "prev_target: %lu\n" DELETE_COLOR, prev_target); )
    }

    size_t pivot_prev_target = prev_target;
    prev_target = *(list->prev + pivot_prev_target);
    ON_DEBUG( printf(RED "pivot_prev_tatrget: %lu\n" DELETE_COLOR, pivot_prev_target); )

    *(list->prev + pivot_prev_target) = list->prev_size;  
    *(list->prev + list->prev_size) = prev_target;
    //============================================================

    ON_DEBUG( printf(GREEN "=== END OF INSERT ===\n" DELETE_COLOR); )

    return good_insert;
}


enum Errors ListDelete( struct List* list, size_t pivot )
{
    ON_DEBUG( printf(GREEN "=== START OF DELETE ===\n" DELETE_COLOR); )
    //TODO: добавить умешьшение размера, free elements, чтобы добавлять не только тупо в конец

    //========================= NEXTS ================================
    size_t next_target = 0;
    for(size_t i = 0; i < pivot - 1; i++)
    {
        next_target = *(list->next + next_target);
        ON_DEBUG( printf(SINIY "next_target: %lu\n" DELETE_COLOR, next_target); )
    }

    size_t pivot_next_target = *(list->next + next_target);
    ON_DEBUG( printf(RED "pivot_next_target: %lu\n" DELETE_COLOR, pivot_next_target); )

    *(list->next + next_target) = *(list->next + pivot_next_target); // предыдущий указывает на следующий от меняемого
    *(list->next + pivot_next_target) = -1;
    ON_DEBUG( *(list->array + pivot_next_target) = -*(list->array + pivot_next_target); ) //для заметности меняю значение на минус
    ON_RELIZ( *(uint64_t*)(list->array + pivot_next_target) = POISON_VALUE; ) 
    //================================================================

    //========================== PREV ================================
    size_t prev_target = 0;
    for(size_t i = 0; i < (list->working_size - pivot ); i++)
    {
        prev_target = *(list->prev + prev_target);
        ON_DEBUG( printf(SINIY "prev_target: %lu\n" DELETE_COLOR, prev_target); )
    }

    size_t pivot_prev_target = *(list->prev + prev_target); 
    ON_DEBUG( printf(RED "pivot_prev_tatrget: %lu\n" DELETE_COLOR, pivot_prev_target); )

    *(list->prev + prev_target) = *(list->prev + pivot_prev_target);  
    *(list->prev + pivot_prev_target) = -1;

    list->working_size--;
    //================================================================

    ON_DEBUG( printf(GREEN "=== END OF DELETE ===\n" DELETE_COLOR); )

    return good_delete;                            
}


enum Errors ListTakeHead( struct List* list, size_t number, ListElem* elem )
{
    if ( !CheckSize_t(number) )
    {
        printf("bad number to take\n");
        return bad_take;
    }
    else if ( number > list->next_size ) 
    {
        printf("Trying to access empty memory part\n");
        return bad_take;
    }
    else 
    {
        // printf("size of working area of array: %lu\n", list->next_size);

        size_t target = 0; 
        for(size_t i = 0; (i < number) && (i < list->next_size ); i++) //смещение на 1 из-за фантомного элемента
        {
            target = list->next[target];      
            printf(SINIY "target in taking: %lu\n" DELETE_COLOR, target); 
        }

        *elem = *(list->array + target);

        return good_take;
    }
}


enum Errors ListTakeTale( struct List* list, size_t number, ListElem* elem )
{
    if ( !CheckSize_t(number) )
    {
        printf("bad number to take\n");
        return bad_take;
    }
    else if ( number > list->next_size ) 
    {
        printf("Trying to access empty memory part\n");
        return bad_take;
    }
    else 
    {
        size_t target = 0; 
        for(size_t i = 0; (i < (list->working_size - number + 1 ) ) && (i < list->prev_size + 1); i++) //смещение на 1 из-за фантомного элемента
        {
            target = list->prev[ target ];      
            printf(SINIY "target in taking: %lu\n" DELETE_COLOR, target); 
        }

        *elem = *(list->array + target);

    }

    return good_take;
}

