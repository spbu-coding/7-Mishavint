#include <stdio.h>
#include <stdlib.h>
#include "main_work.h"

#define error(...) (fprintf(stderr, __VA_ARGS__))
#define NUMBER_OF_PARAMS 2


int main( int argc , char **argv )
{

    if( argc != NUMBER_OF_PARAMS )
    {
        error( "You have entered %d number of arguments. Please enter %d argument\n" , argc - 1 , NUMBER_OF_PARAMS - 1 );
        return -1;
    }

    FILE *input_file;
    input_file = fopen( argv[1] , "rb" );
    if( input_file == NULL )
    {
        error( "Can not find file %s\n" , argv[1] );
        return -1;
    }

    char **array_of_lines = ( char**)malloc( sizeof(char*) * 5 );
    if( array_of_lines == NULL )
    {
        error( "Can not take memory\n" );
        return -1;
    }
    int number_of_lines = 0;

    for( ; ; )
    {
        if( number_of_lines != 0 )
        {
            array_of_lines = (char**)realloc( array_of_lines , sizeof (char*) * ( number_of_lines+1 ) );
            if ( array_of_lines == NULL )
            {
                fclose( input_file );
                free_array( array_of_lines , number_of_lines );
                error( "Can not take memory\n" );
                return -1;
            }
        }

        array_of_lines[ number_of_lines ] = (char*)malloc( sizeof( char ) * MAX_SIZE_OF_LINE );
        if( array_of_lines[ number_of_lines ] == NULL )
        {
            fclose( input_file );
            free_array( array_of_lines , number_of_lines );
            error("Can not take memory\n");
            return -1;
        }

        if( fgets( array_of_lines[ number_of_lines ] , MAX_SIZE_OF_LINE , input_file ) == NULL )
        {
            break;
        }

        number_of_lines++;
    }


//     If last line hasn't got \n, this function will add it
    adding_slash_n_symbol( array_of_lines[ number_of_lines - 1 ] );

    deleting_symbols( array_of_lines , &number_of_lines );

    qsort( array_of_lines , number_of_lines * sizeof(char) , sizeof(char *) , comp );


    int temp_for_print = 0;
    while( temp_for_print < 100 && temp_for_print < number_of_lines )
    {
        printf("%s" , array_of_lines[ temp_for_print ]);
        temp_for_print++;
    }

    free_array( array_of_lines , number_of_lines );
    fclose( input_file );
}
