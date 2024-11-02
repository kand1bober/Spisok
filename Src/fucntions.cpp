#include "../Headers/functions.h"
#include "../Headers/decoration.h"

enum Errors ListCtor( struct List* list )
{
    list->array = (ListElem*)calloc( START_LIST_SIZE + 1, sizeof(ListElem) );

    ListElem buffer[] = { 12, 78, 5, 32, 87, 19, 64, 4, 93, 25, 56 };

//=========заполнение списка=======Тестовое========
    for(size_t i = 0; i < sizeof(buffer) / sizeof(ListElem); i++)
    {
        list->array[i + 1] = buffer[i];
        list->array_size++;
    }
// printf("size of filled part: %lu\n", list->array_size);
//size->array_size -- size of only filled part, without first null

    list->next = (int*)calloc(START_LIST_SIZE + 1, sizeof(int) );

    for(size_t i = 1; i < START_LIST_SIZE; i++)
    {
        list->next[i] = -1;
    }
//===================================================

//===========заполнение массива индексов=================
    for(size_t i = 1; i < list->array_size; i++)
    {
        list->next[i] = i + 1;
        list->next_size++;

    }
    printf("size of filed part of array of indexes: %lu\n", list->next_size);
//================================

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
    printf(GREEN "    Next Dump\n    " DELETE_COLOR);
    for(int i = 0; i < START_LIST_SIZE + 1; i++)
    {
        for(int g = 0; g < 10; g++, i++)
        {
            printf("%d ", list->next[i] );
        }
        printf("\n\n    ");
    }
    printf("\n");

    printf(GREEN "     Array Dump       Next Dump    real numers\n" DELETE_COLOR);
    for(int i = 0 ; i < START_LIST_SIZE + 1; i++)
    {
        printf(ORANGE "[%02d]" DELETE_COLOR "  %7.2lf     ----     %3d       " ORANGE "[%02d]" DELETE_COLOR "\n", i, list->array[i], list->next[i], i );
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
        printf(ORANGE "target: %lu\n" DELETE_COLOR, target);
    }

    //=============меняем значение next предыдущего перед вставляемым и последнего 
    size_t pivot_target = *(list->next + target);
    //размер только рабочей области, поэтому везде вылазит (+1), а (++) это увеличение реального размера
    list->next_size++;                            
    *(list->next + target) = list->next_size + 1;
    *(list->next + list->next_size + 1) = pivot_target;
    //===========================================

    return good_insert;
}


enum Errors ListDelete( struct List* list, int pivot )
{
    ON_DEBUG( *(list->array + pivot) = -*(list->array + pivot); ) //для заметности меняю на минус
    ON_RELIZ( *(uint64_t*)(list->array + pivot) = POISON_VALUE; )

    *(list->next + pivot) = -1;
    *(list->next + pivot - 1) = (pivot + 1); //предыдущий перед удаляемым указывает на следующий после удаллённого 


    return good_delete;
}


enum Errors ListTake( struct List* list, int number, ListElem* elem )
{
    int target = 1;  //TODO: везде пересмотреть работу с size_t
    for(int i = 1; (i < number) && (i < (int)list->next_size); i++) //смещение на 1 из-за фантомного элемента
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
