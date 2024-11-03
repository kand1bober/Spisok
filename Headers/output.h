#include "../Headers/functions.h"

#ifndef LIST_OUTPUT_HEADER
#define LIST_OUTPUT_HEADER


const size_t START_OUTPUT_FILE_SIZE = 10;

struct Writing_buffer
{
    size_t ip;
    char* buffer;
    size_t size;
    size_t capacity;
};

struct File_graph
{
    FILE* stream;
    size_t stream_size;

    Writing_buffer output_buffer;
};

void StartOutput( struct File_graph* file );
void FinishOutput( struct File_graph* file );
enum Errors WriteAllBonds( struct List* list, struct File_graph* file );

#endif
