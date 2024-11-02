#include "configuration.h"

#ifndef MACROS_LIST_HEADER
#define MACROS_LIST_HEADER


#ifdef DEBUG
    #define ON_DEBUG( expr ) expr
#else
    #define ON_DEBUG( expr )
#endif

#ifdef RELIZ
    #define ON_RELIZ( expr ) expr
#else
    #define ON_RELIZ( expr )
#endif


#endif
