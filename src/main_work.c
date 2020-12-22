#include <string.h>
#include <stdlib.h>
#include "main_work.h"

void adding_slash_n_symbol( char* line )
{
    int count_of_symbols = 0;
    while( line[ count_of_symbols ] != '\n' && line[ count_of_symbols ] !='\0' && count_of_symbols < MAX_SIZE_OF_LINE )
        count_of_symbols++;

    line[ count_of_symbols ] = '\n';

}


int comp ( const void* first_line , const void* second_line )
{
    const char **ia = (const char **)first_line;
    const char **ib = (const char **)second_line;
    return -strcmp(*ia, *ib);
}

void free_array( char **array , int i )
{
    for( int j = 0 ; j <= i ; j++ )
    {
        free( array[j] );
    }
    free( array );
}

_Bool is_symbol_is_punctuation_mark( char symbol )
{
    if( ( symbol == '.' ) || ( symbol == ',' ) || ( symbol == ';' ) || ( symbol == ':' ) || ( symbol == '!' )
                                                                                            || ( symbol == '?' ))
    {
        return 1;
    }
    else
        return 0;
}

void rewriting_symbols( char *line , int number_of_start )
{
    if( number_of_start  > MAX_SIZE_OF_LINE )
        return;
    while( line[ number_of_start  ] != '\n' && line[ number_of_start ] != '\0' )
    {
        line[ number_of_start ] = line[ number_of_start + 1 ];
        number_of_start ++;
    }
    line[ number_of_start ] = '\0';
    line[ number_of_start + 1 ] = '\0';

}

void deleting_symbols_in_line( char *line )
{
    int number_of_symbol = 0;
    while( line[ number_of_symbol ] != '\n' && line[ number_of_symbol ] != '\0' )
    {
        // is_symbol_is_punctuation_mark return TRUTH when symbol is punctuation mark
        if( is_symbol_is_punctuation_mark( line[ number_of_symbol ] ) )
        {
            rewriting_symbols( line , number_of_symbol );
        }
        else
        {
            number_of_symbol++;
        }
    }
}

void deleting_symbols( char **array , int const* number_of_lines )
{
    for( int i = 0 ; i < *number_of_lines ; i++ )
    {
        deleting_symbols_in_line( array[ i ] );
    }
}
