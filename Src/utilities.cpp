#include "../Headers/functions.h"
#include "../Headers/decoration.h"
#include "../Headers/output.h"
#include "../Headers/macros.h"


int CheckSize_t( size_t number )
{
    if( number < 1000000 )
        return 1;
    else
        return -1;
}

char* GetFilePath( char* filepath )
{
    printf("getting filepath\n");
    const char* directory = "/home/vyacheslav/Spisok/";
    const char* filename = output_graph_name;
    sprintf(filepath, "%s%s", directory, filename);

    return filepath;
}


void BufferResize( struct Writing_buffer* buffer )
{
    ON_DEBUG( printf("ip: %lu capacity: %lu\n", buffer->ip, buffer->capacity); )
    if ( buffer->ip + 10 >= buffer->capacity )
    {
        ON_DEBUG( printf(RED "resizing\n" DELETE_COLOR); )
        buffer->buffer = (char*)realloc( buffer->buffer, buffer->capacity * 2 );
        buffer->capacity *= 2;
    }
}
