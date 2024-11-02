#include "../Headers/functions.h"
#include "../Headers/decoration.h"


int CheckSize_t( size_t number )
{
    if( number < 1000000 )
        return 1;
    else
        return -1;
}

char* GetFilePath( char* filepath )
{
    const char* directory = "/home/vyacheslav/Spisok/";
    const char* filename = "graph.dot";
    filepath = {};
    sprintf(filepath, "%s%s", directory, filename);

    return filepath;
}