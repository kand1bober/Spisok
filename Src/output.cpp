// #include "../Headers/functions.h"
#include "../Headers/output.h"
#include "../Headers/decoration.h"


void StartOutput( struct File_graph* file )
{
    char code_filepath[200] = {};
    char html_filepath[200] = {};
    char image_filepath[200] = {};
    GetFilePath( image_filepath, output_image_name );
    GetFilePath( code_filepath, output_graph_name );
    GetFilePath( html_filepath, output_html_name );

    printf("Name of output file with code: %s\n", code_filepath); 

    //============================== GRAPH FILE ====================================
    file->stream = fopen(code_filepath, "w");
    file->output_buffer.buffer = (char*)calloc( START_OUTPUT_FILE_SIZE, sizeof(char) );
    fprintf(file->stream, "digraph G\n{\nlabel=\"Real array elements\";\nlabelloc=\"t\";\nfontsize=30\nfontname=\"Verdana\"\nrankdir=LR;size=\"200,300\";bgcolor=\"%s\";\n"
    "edge[color=\"#000000\",fontcolor=\"#000000\",fontsize=10];\n", bgcolor);
    //==============================================================================

    
    //============================== HTML FIlE =====================================
    FILE* html_stream = fopen( html_filepath, "w" );
    fprintf(html_stream, "<img src=\"%s\"  alt=\"MyGraph\" width=\"1300px\" height=\"900px\">", image_filepath);
    fclose( html_stream );
    //==============================================================================
}


void FinishOutput( struct File_graph* file )
{
    fprintf(file->stream, "\n}\n");
    char cmd[256] = {};
    snprintf(cmd, sizeof(cmd), "dot -Tsvg %s > %s", output_graph_name, output_image_name);
    ON_DEBUG( printf(SINIY "command for graphviz: " YELLOW "%s\n" DELETE_COLOR, cmd); )

    fclose(file->stream);
    free(file->output_buffer.buffer);

    system( cmd );
}


enum Errors WriteAllBonds( struct List* list, struct File_graph* file )
{
    // if( list->next_size < 2 )
    //     return bad_write_bonds;

    //=== следущий от первого, следующий от второго===============входной расчёт=======+
    int target_next_1 = 0, target_next_2 = 0;
    int target_prev_1 = 0, target_prev_2 = 0;
    ListElem elem1 = 0, elem2 = 0;
    //=======================================

    ON_DEBUG( printf(GREEN "next_size: %lu\n\n" DELETE_COLOR, list->next_size ); )
    for(size_t i = 0; i < list->array_capacity - 1; i++)
    {
        elem1 = *(list->array + i);
        elem2 = *(list->array + i + 1);

        target_next_1 = *(list->next + i);
        target_next_2 = *(list->next + i + 1);

        target_prev_1 = *(list->prev + i);
        target_prev_2 = *(list->prev + i + 1);


        // printf(YELLOW "%4.0lf %4.0lf  i=%lu\n\n", elem1, elem2, i);

        // printf(YELLOW "%4d%4d\n%4d%4d\n\n\n" DELETE_COLOR, target_next_1, target_prev_1, target_next_2, target_prev_2);


        fprintf(file->stream, " node_%lu [shape=record,style=\"rounded,filled\",fillcolor=\"%s\",color=\"%s\",label=\" { <ip%lu> i: %lu } | { <data%lu> data: %0.2lf} | { <next%d> next: %d } | { <prev%lu> prev: %d } \" ]; "
                              " node_%lu [shape=record,style=\"rounded,filled\",fillcolor=\"%s\",color=\"%s\",label=\" { <ip%lu> i: %lu } | { <data%lu> data: %0.2lf} | { <next%d> next: %d } | { <prev%lu> prev: %d } \" ];  ",
                                i, fillcolor, default_pointer_color, i, i, i, elem1, target_next_1, target_next_1, i, target_prev_1,
                                i+1, fillcolor, default_pointer_color, i+1, i+1, i+1, elem2, target_next_2, target_next_2, i+1, target_prev_2 );
        

        fprintf(file->stream, "node_%lu -> node_%lu [color = \"%s\", arrowsize = 1] ;\n", i, i+1, default_pointer_color );
    }
    // fprintf(file->stream, "node_5: <next9> -> node_9: <ip9> [color = \"%s\", arrowsize = 1] ;\n", next_pointer_color);

    return good_write_bonds;
}

