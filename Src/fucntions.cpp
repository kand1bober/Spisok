#include "../Headers/functions.h"
#include "../Headers/decoration.h"
#include <mutex>

enum Errors ListCtor( struct List* list )
{
    list->array = (ListElem*)calloc( START_LIST_SIZE, sizeof(ListElem) );
    list->array_capacity = START_LIST_SIZE - 1;
    ListElem buffer[] = { 12, 65, 32, 17, 25, 1, 2, 3 };

    list->next = (int*)calloc(START_LIST_SIZE, sizeof(int) );

    list->prev = (int*)calloc(START_LIST_SIZE, sizeof(int) );


    //=========заполнение списка=======Тестовое==================
    for(size_t i = 0; i < list->array_capacity + 1; i++)
    {
        *(uint64_t*)(list->array + i) = POISON_VALUE;
    }
    for(size_t i = 0; i < sizeof(buffer) / sizeof(ListElem); i++)
    {
        list->array[i + 1] = buffer[i];
        list->array_size++;
    }
    //===========================================================


    for(size_t i = 1; i < list->array_size + 1; i++)
    {
        list->next[i] = -1;
        list->prev[i] = -1;
    }

    //===========заполнение массива индексов=================

    ON_DEBUG( printf(YELLOW "Size of array: %lu\n\n" DELETE_COLOR, list->array_size); )

    //=============NEXTS=======================
    for(size_t i = 0; i < list->array_size; i++)
    {
        list->next[i] = i + 1;
        list->next_size++;
        ON_DEBUG( printf(RED "next[%lu]: %d\n" DELETE_COLOR, i, list->next[i]); )
    }
    *(list->next + list->array_size) = 0;
    ON_DEBUG( printf(RED "next[%lu]: %d\n\n" DELETE_COLOR, list->array_size, list->next[list->array_size]); )

    //===============PREVS=====================
    *(list->prev) = list->array_size;
    ON_DEBUG( printf(GREEN "prev[0]: %d\n" DELETE_COLOR, *(list->prev) ); )

    for(size_t g = 1; g < list->array_size + 1; g++ )
    {
        *(list->prev + g) = g - 1;
        ON_DEBUG( printf(GREEN "prev[%lu]: %d\n" DELETE_COLOR, g, *(list->prev + g) ); )
    }
    ON_DEBUG( printf("size of filed part of array of indexes: %lu\n", list->next_size); )
    //=========================================




    // printf("size of filled part: %lu\n", list->array_size);
    //size->array_size -- size of only filled part, without first null





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
    printf(GREEN "[i]  Array Dump      Next    Prev     [i]\n" DELETE_COLOR);
    for(size_t i = 0 ; i < START_LIST_SIZE; i++)
    {
        if( *(uint64_t*)(list->array + i) == POISON_VALUE )
        {
            printf(ORANGE "[%02lu]" DELETE_COLOR "  " PURPLE "%7.2lf" DELETE_COLOR "   ---  %3d    %3d      " ORANGE "[%02lu]" DELETE_COLOR "\n", i, list->array[i], list->next[i], list->prev[i], i );
        }
        else
        {
            printf(ORANGE "[%02lu]" DELETE_COLOR "  %7.2lf   ---  %3d    %3d      " ORANGE "[%02lu]" DELETE_COLOR "\n", i, list->array[i], list->next[i], list->prev[i], i );
        }
    }
    printf("\n\n");
}   


//=====первая версия Insert=======
enum Errors ListInsert( struct List* list, size_t pivot, ListElem* elem) // pivot -- номер элемента в который хочу вставить, то есть: вставляем в 3ий -- 2ой ссылается на номер после последнего он ссылаяется на , а 
{
    list->array_size++;                                     //--|
    *(ListElem*)(list->array + list->array_size ) = *elem;  //--|-- вставка реального числа в конец массива чисел

    size_t target = 1;

    size_t i = 1; //номер ячейки в next; target -- то, что лежит в ячейке, то есть номер "следующей" ячейки
    for(i = 1; i < pivot - 1; i++)
    {
        target = *(list->next + target);
        // printf(ORANGE "target: %lu\n" DELETE_COLOR, target);
    }

    //=============меняем значение next предыдущего перед вставляемым и последнего 
    size_t pivot_target = *(list->next + target);

    //размер только рабочей области, поэтому везде вылазит (+1), а (++) это увеличение реального размера
    list->next_size++;                            
    *(list->next + target) = list->next_size + 1;
    *(list->next + list->next_size + 1) = pivot_target;

    return good_insert;
}


enum Errors ListDelete( struct List* list, size_t pivot )
{
    size_t target = 1;

    size_t i = 1;
    for(i = 1; i < pivot - 1; i++)
    {
        target = *(list->next + target);
        ON_DEBUG( printf(ORANGE "target: %lu\n" DELETE_COLOR, target); )
    }

    size_t pivot_target = *(list->next + target);
    ON_DEBUG( printf(ORANGE "pivot_target: %lu\n" DELETE_COLOR, pivot_target); )
    //============CHANGING some IP'S and one value==========
    *(list->next + target) = *(list->next + pivot_target); // предыдущий указывает на следующий от меняемого
    *(list->next + pivot_target) = -1;
    ON_DEBUG( *(list->array + pivot_target) = -*(list->array + pivot_target); ) //для заметности меняю значение на минус
    ON_RELIZ( *(uint64_t*)(list->array + pivot_target) = POISON_VALUE; ) 

    return good_delete;                            
}


enum Errors ListTake( struct List* list, size_t number, ListElem* elem )
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

        size_t target = 1; 
        for(size_t i = 1; (i < number) && (i < list->next_size + 1); i++) //смещение на 1 из-за фантомного элемента
        {
            target = list->next[target];      
            printf("target in taking: %lu\n", target); 
        }

        *elem = *(list->array + target);

        return good_take;
    }
}


// enum Errors()
// {

// }

