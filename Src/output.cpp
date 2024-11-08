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
    fprintf(file->stream, "digraph G\n{\nsplines=polyline\nlabel=\"Real array elements\";\nlabelloc=\"t\";\nfontsize=30\nfontname=\"Verdana\"\n"
    "rankdir=LR;size=\"200,300\";bgcolor=\"%s\";\n"
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


enum Errors WritePrimaryNodes( struct List* list, struct File_graph* file )
{
    // if( list->next_size < 2 )
    //     return bad_write_bonds;

    //=== следущий от первого, следующий от второго===============входной расчёт=======+
    int target_next_1 = 0, target_next_2 = 0;
    int target_prev_1 = 0, target_prev_2 = 0;
    ListElem elem1 = 0, elem2 = 0;
    //=======================================

    ON_DEBUG( printf(GREEN "next_size: %lu\n\n" DELETE_COLOR, list->next_size ); )
    /*
    fprintf(file->stream, "rank=same; ");
    for(size_t i = 0; i < list->array_capacity; i++)
    {
        fprintf(file->stream, "node_%lu; ", i);
    }
    fprintf(file->stream, "rank=same; ");
    */
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
        

        fprintf(file->stream, "node_%lu -> node_%lu [color = \"%s\", arrowsize = 1] ;\n", i, i+1, default_pointer_color);
    }

    return good_write_nodes;
}


enum Errors WriteSecondaryNodes( struct List* list, struct File_graph* file )
{

    if( list->next_size < 2 )
        return bad_write_nodes;

    //=== следущий от первого, следующий от второго===============входной расчёт=======+
    int target_next_1 = 0, target_next_2 = 0;
    int target_prev_1 = 0, target_prev_2 = 0;
    ListElem elem1 = 0, elem2 = 0;
    //=======================================

    ON_DEBUG( printf(GREEN "next_size: %lu\n\n" DELETE_COLOR, list->next_size ); )
    for(size_t i = 0; i < list->array_size + 1; i++)
    {
        elem1 = *(list->array + i);
        target_next_1 = *(list->next + i);
        target_prev_1 = *(list->prev + i);

        for(size_t g = 0; g < list->array_size + 1; g++ )
        {
            if( g != i)
                ;
            else 
                continue;

            elem2 = *(list->array + g);
            target_next_2 = *(list->next + g);
            target_prev_2 = *(list->prev + g);


            ON_DEBUG( printf(YELLOW "%4.2lf %4.2lf  i=%lu g=%lu\n\n", elem1, elem2, i, g); )
            ON_DEBUG( printf(YELLOW "%4d%4d\n%4d%4d\n\n\n" DELETE_COLOR, target_next_1, target_prev_1, target_next_2, target_prev_2); )
            
            fprintf(file->stream, " node_%lu [shape=record,style=\"rounded,filled\",fillcolor=\"%s\",color=\"%s\",label=\" { <ip%lu> i: %lu } | { <data%lu> data: %0.2lf} | { <next%d> next: %d } | { <prev%lu> prev: %d } \" ]; "
                                " node_%lu [shape=record,style=\"rounded,filled\",fillcolor=\"%s\",color=\"%s\",label=\" { <ip%lu> i: %lu } | { <data%lu> data: %0.2lf} | { <next%d> next: %d } | { <prev%lu> prev: %d } \" ];  ",
                                    i, fillcolor, default_pointer_color, i, i, i, elem1, target_next_1, target_next_1, i, target_prev_1,
                                    g, fillcolor, default_pointer_color, g, g, g, elem2, target_next_2, target_next_2, g, target_prev_2 );
            
            

            if( ( (size_t)target_next_1 == g ) && ( !( (i == 0) && (g == 0) ) ) )
            {
                ON_DEBUG( printf(YELLOW "printfng: ip:%lu <%d> -> ip:%lu <%lu>\n" DELETE_COLOR, i, target_next_1, g, g ); )
                fprintf(file->stream, "node_%lu: <next%d> -> node_%lu: <ip%lu> [color = \"%s\", arrowsize = 1] ;\n", i, target_next_1, g, g, next_pointer_color);
            }
            else 
            {
                ON_DEBUG( printf(PURPLE"not printfng: ip:%lu <%d> -> ip:%lu <%lu>\n" DELETE_COLOR, i, target_next_1, g, g ); )
                continue;
            }
            
        }
    }

    return good_write_nodes;
}

