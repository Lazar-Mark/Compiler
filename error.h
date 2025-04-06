#ifndef error_h
#define error_h
#define LOAD_ERR() load_file_error(__FILE__,__func__,__LINE__)
#define MALLOC_ERR() memory_allocation_error(__FILE__,__func__,__LINE__)
#include <stdio.h>
#include <stdlib.h>
void load_file_error(char* file,const char* function,int line);
void memory_allocation_error(char* file,const char* function,int line);
#endif