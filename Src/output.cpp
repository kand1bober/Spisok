#include "../Headers/functions.h"
#include "../Headers/output.h"


void StartOutput( struct File_graph* file )
{
    char filepath[200] = {};
    GetFilePath( filepath );
    printf("Name of output file with code: %s\n", filepath); 

    file->stream = fopen(filepath, "w");
    file->output_buffer.buffer = (char*)calloc( START_OUTPUT_FILE_SIZE, sizeof(char) );
    fprintf(file->stream, "digraph G\n{\nrankdir=LR;\n"
    "node[color=\"red\",fontsize=14];\n"
    "edge[color=\"darkgreen\",fontcolor=\"blue\",fontsize=12];\n");
}


void FinishOutput( struct File_graph* file )
{
    fprintf(file->stream, "\n}\n");
    char cmd[256] = {};
    snprintf(cmd, sizeof(cmd), "dot %s -Tpng -o %s", output_graph_name, output_image_name);
    ON_DEBUG( printf(SINIY "command for graphviz: " YELLOW "%s\n" DELETE_COLOR, cmd); )

    system( cmd );
    // system( "dot MyGraph.dot -Tpng  -o KrutoyGraph2007.png" );

    fclose(file->stream);
    free(file->output_buffer.buffer);
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
            fprintf(file->stream, "next_%d -> next_empty;\n", prev_target );
        else
            fprintf(file->stream, "next_%d -> next_%d;\n", prev_target,  target );
    }

    return good_write_bonds;
}
