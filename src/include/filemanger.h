#ifndef _FILEMANGER_H
#define _FILEMANGER_H

#include <tice.h>
#include <fileioc.h>
#include <stdlib.h>
#include <stdint.h>

struct file_io
{
    ti_var_t file;

}
typedef struct file_io file_io_t;

file_io_t* open_file_read(char* _name)
{
    ti_var_t file = ti_Open(_name,'r');
    
    file_io_t *file_object = (file_io_t*)malloc(sizeof(file_io_t)) 
}





#endif