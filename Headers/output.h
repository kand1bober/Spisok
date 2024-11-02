#include "../Headers/functions.h"
#ifndef LIST_OUTPUT_HEADER
#define LIST_OUTPUT_HEADER


struct Output_buffer
{
    size_t buffer_ip;
    char* buffer;
    int size;
    int capacity;
};

struct File_graph
{
    FILE* stream;

    size_t byte_size;
    Output_buffer output_buffer;
};


#endif