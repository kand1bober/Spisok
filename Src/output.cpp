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
    fprintf(file->stream, "digraph G\n{\nrankdir=LR;size=\"200,200\";bgcolor=\"#FFB6C1\";\n"
    "node[color=\"#6666FF\",fontsize=14,shape=\"rectangle\",style=\"rounded,filled\",fillcolor=\"#FFFACD\"];\n"
    "edge[color=\"#000080\",fontcolor=\"#000080\",fontsize=20];\n");
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


enum Errors WriteBonds( const char* line_a, const char* line_b, struct File_graph* file )
{   
    BufferResize( &file->output_buffer ); //resize if needed
    //TODO: maybe parser of commands

    size_t line_length = strlen( line_a );
    snprintf(file->output_buffer.buffer + file->output_buffer.ip, line_length, "%s", line_a);
    file->output_buffer.ip += line_length;

    line_length = strlen( line_b );
    snprintf(file->output_buffer.buffer + file->output_buffer.ip, line_length, "%s", line_b);
    file->output_buffer.ip += line_length;

    if( file->output_buffer.buffer )
        return good_write_bonds;
    else
        return bad_write_bonds;
}


enum Errors WriteAllBonds( struct List* list, struct File_graph* file )
{
    int target = 1, prev_target = 1;
    for(size_t i = 0; i < list->next_size - 1; i++)
    {
        prev_target = target;
        target = *(list->next + target);
        printf(GREEN "success prev_target = %d, target = %d\n" DELETE_COLOR, prev_target, target);

        if(*(list->next + target) == -1)
            fprintf(file->stream, "next_%d -> next_empty [color = \"#800080\", arrowsize = 1];\n", prev_target );
        else
            fprintf(file->stream, "next_%d -> next_%d [color = \"#800080\", arrowsize = 1];\n", prev_target,  target );
    }

    return good_write_bonds;
}
