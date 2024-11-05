#include "../Headers/functions.h"
#include "../Headers/output.h"


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
    fprintf(file->stream, "digraph G\n{\nrankdir=LR;size=\"200,300\";bgcolor=\"#FF69B4\";\n"
    "edge[color=\"#000000\",fontcolor=\"#000000\",fontsize=10];\n");
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
    int target1 = 0, target2 = *(list->next + target1);
    printf(GREEN "next_size: %lu\n" DELETE_COLOR, list->next_size );
    for(size_t i = 0; i < list->next_size - 1; i++)
    {
        printf(GREEN "i=%lu success target1 = %d, target2 = %d\n" DELETE_COLOR, i, target1, target2 );

        
        fprintf(file->stream, " node_%d [shape=record,style=\"rounded,filled\",fillcolor=\"#FFFACD\",color=\"#6666FF\",label=\" { <ip%lu> ip: %d } | { <data%d> data: %0.2lf} | { <next%d> next: %d } | { <prev> prev: } \" ]; "
                              " node_%d [shape=record,style=\"rounded,filled\",fillcolor=\"#FFFACD\",color=\"#6666FF\",label=\" { <ip%lu> ip: %d } | { <data%d> data: %0.2lf} | { <next%d> next: %d } | { <prev> prev: } \" ];  ",
                              target1, i, target1, target1, *(list->array + target1), target1, target2, 
                              target2, i + 1, target2, target2, *(list->array + target2), target2, *(list->next + target2) );
        
        if( (target1 == -1) || (target2 == -1) )
            fprintf(file->stream, "node_%d: <next%d> -> next_empty [color = \"%s\", arrowsize = 1] ;\n", target1, target2, output_color_1 );
        else
            fprintf(file->stream, "node_%d: <next%d> -> node_%d: <ip%lu> [color = \"%s\", arrowsize = 1] ;\n", target1, target2,
                                                                                                       target2, i + 1, output_color_1 );
        target1 = *(list->next + target1);
        target2 = *(list->next + target1);
    }

    return good_write_bonds;
}
