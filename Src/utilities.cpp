#include "../Headers/library.h"
#include "../Headers/functions.h"
#include "../Headers/decoration.h"


int CheckSize_t( size_t number )
{
    if( number < 1000000 )
        return 1;
    else
        return -1;
}

