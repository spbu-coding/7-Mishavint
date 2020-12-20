#pragma once

#define MAX_SIZE_OF_LINE 1000


int comp ( const void* first_line , const void* second_line );

void free_array( char **array , int i );

void deleting_symbols( char **array , int const* number_of_lines );

void adding_slash_n_symbol( char* line );
