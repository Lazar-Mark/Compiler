#include "error.h"
void load_file_error(char* file,const char* function,int line){
    printf("ERROR: File opening failed in function %s,%s, %d\n",function,file,line);
    exit(1);
}
void memory_allocation_error(char* file,const char* function,int line){
    printf("ERROR: Memory allocation failed in function %s,%s:%d",function,file,line);
    exit(1);
}

