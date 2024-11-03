#ifndef CONFIGURATION_LIST_HEADER
#define CONFIGURATION_LIST_HEADER

//=======NAME OF GRAPH FILE=====
const char output_image_name[] = "KrutoyGraph2007.png";
const char output_graph_name[] = "MyGraph.dot";
//===============================

#define DEBUG
// #define RELIZ

#ifdef DEBUG
    #ifdef RELIZ
        #undef DEBUG
        #undef RELIZ
    #endif
#endif

#ifdef DEBUG
    #undef RELIZ
#endif

#ifdef RELIZ
    #undef DEBUG
#endif


// TODO: всеееееееееееее инклюды подряд


#endif
