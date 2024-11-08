#include "../Headers/functions.h"
#include "../Headers/decoration.h"

enum Errors ListCtor( struct Data* data )
{
    //================ INITIALIZATION =========================
    //-------------------list of numbers-----------------------
    data->spisok.array = (ListElem*)calloc( START_LIST_SIZE, sizeof(ListElem) );
    data->spisok.next = (int*)calloc(START_LIST_SIZE, sizeof(int) );
    data->spisok.prev = (int*)calloc(START_LIST_SIZE, sizeof(int) );

    data->spisok.array_capacity = START_LIST_SIZE;
    data->spisok.next_capacity = data->spisok.array_capacity;
    data->spisok.prev_capacity = data->spisok.array_capacity;
    data->spisok.spisok_capacity = data->spisok.array_capacity - 1;

    data->spisok.array_size = 0;
    data->spisok.next_size = data->spisok.array_size;
    data->spisok.prev_size = data->spisok.array_size;
    data->spisok.spisok_size = data->spisok.array_size;

    *(data->spisok.next) = 1;
    *(data->spisok.prev) = 0;

    // //=============NEXTS=======================
    // for(size_t i = 0; i < data->spisok.next_capacity - 1; i++)
    // {
    //     data->spisok.next[i] = i + 1;
    //     ON_DEBUG( printf(RED "next[%lu]: %d\n" DELETE_COLOR, i, data->spisok.next[i]); )
    // }
    //     ON_DEBUG( printf(SINIY "next_capacity = %lu\n\n" DELETE_COLOR, data->spisok.next_capacity); )

    // //===============PREVS=====================
    // *(data->spisok.prev) = data->spisok.prev_capacity - 1;
    //     ON_DEBUG( printf(GREEN "prev[0]: %d\n" DELETE_COLOR, *(data->spisok.prev) ); )

    // for(size_t g = 1; g < data->spisok.prev_capacity; g++ )
    // {
    //     *(data->spisok.prev + g) = g - 1;
    //     ON_DEBUG( printf(GREEN "prev[%lu]: %d\n" DELETE_COLOR, g, *(data->spisok.prev + g) ); )
    // }
    //     ON_DEBUG( printf(SINIY "prev_capacity: %lu\n\n" DELETE_COLOR, data->spisok.prev_capacity); )
    // //=========================================



    //----------------list of free places-------------------------
    data->free.array = (int*)calloc( START_LIST_SIZE, sizeof(int) );
    data->free.next = (int*)calloc( START_LIST_SIZE, sizeof(int) );
    data->free.prev = (int*)calloc( START_LIST_SIZE, sizeof(int) );

    data->free.array_capacity = START_LIST_SIZE;
    data->free.next_capacity = data->free.array_capacity;
    data->free.prev_capacity = data->free.array_capacity;
    data->free.spisok_capacity = data->free.array_capacity - 1;

    data->free.array_size = 0;
    data->free.next_size = data->free.array_size;
    data->free.prev_size = data->free.array_size;
    data->free.spisok_size = data->free.array_size;
    //----------------------------------------------------------------
    *(data->free.array + 1) = 1;
    data->free.array_size++;
    data->free.spisok_size++;
    printf(YELLOW "free->spisok_size: %lu\n" DELETE_COLOR, data->free.spisok_size);

    //----------------------------------------------------------------
    for(size_t i = 0; i < data->free.next_capacity - 1; i++)
    {
        data->free.next[i] = i + 1;
    }
    *(data->free.next + data->free.next_capacity - 1) = 0; 

    //-----------------------------------------------------------------
    *(data->free.prev) = data->free.prev_capacity - 1;
    data->free.prev_size++;
    for(size_t g = 1; g < data->free.prev_capacity; g++ )
    {
        *(data->free.prev + g) = g - 1;
    }
    //=========================================================

    if( (data->spisok.next) && (data->spisok.array) && (data->spisok.prev) &&
        ( data->free.next ) && ( data->free.array ) && ( data->free.prev ) )
        return good_ctor;
    else
        return bad_ctor;
}


enum Errors ListDtor( struct Data* data )
{
    free( data->spisok.next );
    free( data->spisok.array );
    free( data->spisok.prev );

    free( data->free.next );
    free( data->free.array );
    free( data->free.prev );

    if( (!data->spisok.next) && (!data->spisok.array) && (!data->spisok.prev) &&
        ( !data->free.next ) && ( !data->free.array ) && ( !data->free.prev ) )
        return good_dtor;
    else
        return bad_dtor;
}


void ListDump( struct List* list, struct Free* free )
{     
    printf(GREEN "====== Begin of ListDump ======\n" DELETE_COLOR);

    printf("list::\nspisok_size: %lu, array_size: %lu, next_size: %lu, prev_size: %lu\n", list->spisok_size, list->array_size, list->next_size, list->prev_size); 
    printf(SINIY "\n[i]  Number Dump     Next    Prev     [i]\n" DELETE_COLOR);
    for(size_t i = 0 ; i < list->array_capacity; i++)
    {
        printf(ORANGE "[%02lu]" DELETE_COLOR "  %7.2lf   ---  %3d    %3d      " ORANGE "[%02lu]" DELETE_COLOR "\n",
        i, list->array[i], list->next[i], list->prev[i], i );
    }
    printf("\n\n");


    printf("free:\nspisok_size: %lu, array_size: %lu, next_size: %lu, prev_size: %lu\n", free->spisok_size, free->array_size, free->next_size, free->prev_size); 
    printf(SINIY "\n[i]  Free  Dump      Next    Prev     [i]\n" DELETE_COLOR);
    for(size_t i = 0 ; i < free->array_capacity; i++)
    {
        printf(ORANGE "[%02lu]" DELETE_COLOR "  %7d   ---  %3d    %3d      " ORANGE "[%02lu]" DELETE_COLOR "\n", 
        i, free->array[i], free->next[i], free->prev[i], i );
    }
    printf("\n");

    printf(GREEN "====== End of ListDump ======\n\n" DELETE_COLOR);
}   



enum Errors ListInsert( struct List* list, struct Free* free, size_t pivot, ListElem* elem) 
{
    assert( list );

        ON_DEBUG( printf(GREEN "\n=== START OF INSERT ===\n" DELETE_COLOR); )
    if ( !CheckSize_t( pivot ) || ( pivot == 0 ) )
    {
        printf(RED "cannot insert in the null or negative element" DELETE_COLOR);
        return bad_insert;
    }
    if( (pivot >= list->spisok_capacity) || (pivot > list->spisok_size + 1) ) //TODO: добавить realloc, но здесб всё равно слать нахуй
    {
        printf(RED "Cannot insert, place is above max size\n" DELETE_COLOR);
        return bad_insert;
    }
    
    int free_elem = 0;
    FreeDelete( list, free, &free_elem);
        ON_DEBUG( printf(SINIY "Number of element to change with: %d\n" DELETE_COLOR, free_elem); )
    *(ListElem*)(list->array + free_elem) = *elem;
    list->array_size++;   //физический размер
    list->spisok_size++; //логический размер
    list->next_size++;  //логический размер

    size_t next_target = 0;
    //===================NEXTS===================================
    for(size_t i = 0; i < pivot - 1; i++)
    {
        next_target = *(list->next + next_target);
            ON_DEBUG( printf(SINIY "next_target: %lu\n" DELETE_COLOR, next_target); )
    }
    
    size_t pivot_next_target = *(list->next + next_target);
        ON_DEBUG( printf(RED "pivot_next_target: %lu\n" DELETE_COLOR, pivot_next_target); )

    *(list->next + next_target) = free_elem; 
    if( pivot_next_target != (size_t)free_elem )
    {
        *(list->next + free_elem) = pivot_next_target;
    }
        PAUSE
    //============================================================

        ON_DEBUG( ListDump(list, free); )
/*
    //==================PREVS=====================================
    size_t prev_target = 0;
    for(size_t i = 0; i < (list->spisok_size - pivot + 1); i++)
    {
        prev_target = *(list->prev + prev_target);
            ON_DEBUG( printf(SINIY "prev_target: %lu\n" DELETE_COLOR, prev_target); )
            PAUSE
    }

    if( prev_target != pivot )
    {
        size_t pivot_prev_target = *(list->prev + prev_target);

            ON_DEBUG( printf(RED "pivot_prev_tatrget: %lu\n" DELETE_COLOR, pivot_prev_target); )

        *(list->prev + prev_target) = pivot_prev_target;
        *(list->prev + pivot_prev_target) = *(list->prev + *(list->prev + pivot_prev_target) );  
    }
    list->prev_size++;
    //============================================================
*/
        ON_DEBUG( ListDump(list, free); )

        ON_DEBUG( printf(GREEN "=== END OF INSERT ===\n" DELETE_COLOR); )

    return good_insert;
}


enum Errors ListDelete( struct List* list, struct Free* free, size_t pivot )
{   
    assert(free);
    assert(list);

    if ( !CheckSize_t( pivot ) || ( pivot == 0 ) )
    {
        printf(RED "cannot dekete the null or negative element\n" DELETE_COLOR);
        return bad_insert;
    }
    if( pivot > list->spisok_size )
    {
        printf(RED "no such element in the list\n" DELETE_COLOR);
        return bad_delete;
    }

        ON_DEBUG( printf(RED "=== START OF DELETE ===\n" DELETE_COLOR); )
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
    list->next_size--;
    list->spisok_size--;

        ON_DEBUG( ListDump(list, free); )
    //================================================================
/*
    //========================== PREV ================================
    size_t prev_target = 0;
    for(size_t i = 0; i < (list->spisok_size - pivot ); i++)
    {
        prev_target = *(list->prev + prev_target);
            ON_DEBUG( printf(SINIY "prev_target: %lu\n" DELETE_COLOR, prev_target); )
    }

    size_t pivot_prev_target = *(list->prev + prev_target); 
        ON_DEBUG( printf(RED "pivot_prev_tatrget: %lu\n" DELETE_COLOR, pivot_prev_target); )

    *(list->prev + prev_target) = *(list->prev + pivot_prev_target);  
    *(list->prev + pivot_prev_target) = -1;

    list->prev_size--;

    //--------------
    FreeInsert( list, free, pivot);

    ON_DEBUG( ListDump(list, free); )
    //================================================================
*/
        ON_DEBUG( printf(RED "=== END OF DELETE ===\n" DELETE_COLOR); )

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
        for(size_t i = 0; (i < (list->spisok_size - number + 1 ) ) && (i < list->prev_size + 1); i++) //смещение на 1 из-за фантомного элемента
        {
            target = list->prev[ target ];      
            printf(SINIY "target in taking: %lu\n" DELETE_COLOR, target); 
        }

        *elem = *(list->array + target);

    }

    return good_take;
}


enum Errors FreeInsert( struct List* list, struct Free* free, int ip )
{
        PAUSE
        ON_DEBUG( printf(YELLOW "===== Start of FreeInsert =====\n" DELETE_COLOR); )
        // ON_DEBUG( printf("spisok_size: %lu, array_size: %lu, next_size: %lu, prev_size: %lu\n", free->spisok_size, free->array_size, free->next_size, free->prev_size); )

    free->spisok_size++; //логический
    free->array_size++; //хуй знает какой

    int next_target = 0;
    
    for(size_t i = 0; i < free->spisok_size; i++)
    {   
        next_target = free->next[next_target];
    }
    free->array[next_target] = ip;
    free->next_size++; //логический

    //пересчёт prev
    free->prev_size++;//логический

        ON_DEBUG( printf(YELLOW "===== End of FreeInsert =====\n" DELETE_COLOR); )
        ON_DEBUG( ListDump(list, free); )
        PAUSE

    return good_free_insert;
}


//====похер в какой номер вписывает insert, delete тупо даёт разрешение на запись в определённое место в массиве
enum Errors FreeDelete( struct List* list, struct Free* free, int* ip )
{
        PAUSE
        ON_DEBUG( printf(YELLOW "===== Start of FreeDelete =====\n" DELETE_COLOR); )
    // *ip = *(free->array + free->array_size);
    int target_ip = 0;
    for(size_t i = 0; i < free->next_size + 1; i++)
    {
        target_ip = free->next[target_ip];
    }
    *ip = free->array[target_ip];

    if ( free->spisok_size < 2 )
    {
        *(free->array + free->array_size) = *(free->array + free->array_size) + 1;
    }
    else 
    {
        *(free->array + free->array_size) = -1;
        
        *(free->next + free->next_size - 1) = 0;
        *(free->next + free->next_size) = 0;

        *(free->prev + free->prev_size) = 0;
        *(free->prev) = free->prev_size - 1;

        free->spisok_size--;
        free->array_size--;
        free->next_size--;
        free->prev_size--;
    }
    
        ON_DEBUG( printf(SINIY "spisok_size after delete: %lu, returned ip: %d\n" DELETE_COLOR, free->spisok_size, *ip ); )
        ON_DEBUG( ListDump(list, free); )
        ON_DEBUG( printf(YELLOW "===== End of FreeDelete =====\n" DELETE_COLOR); )
        PAUSE

    return good_free_delete;
}
