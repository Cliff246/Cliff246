#ifndef _FILEMANGER_H
#define _FILEMANGER_H

#include <tice.h>
#include <fileioc.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "include/tistring.h"

#define CHUNKSIZE 8


typedef struct ti_file ti_file_t;


struct ti_file
{
    ti_var_t ti_var_file;
    char ti_mode[3];
    char ti_file_name[];
};

ti_file_t* ti_open_file(char* file_name,char* file_mode) 
{

    //custom wrapper for open file 
    if(file_name == NULL || file_mode == NULL)
        return 0;
    uint16_t size_name = strlen(file_name);
    ti_file_t *file_object = (ti_file_t*)calloc(1,sizeof(ti_file_t) + size_name);
    if(file_object != NULL)
    {
        ti_var_t temp = ti_Open(file_name,file_mode);

        if(temp == 0)
            os_ThrowError(-1);

        file_object->ti_var_file = temp; 
        
        void* fmode_cpy = memcpy(file_object->ti_mode,file_mode,3);
        void* fname_cpy = memcpy(file_object->ti_file_name,file_name,size_name);
        
        if(fmode_cpy == NULL || fname_cpy == NULL)
            os_ThrowError(-1);
        return file_object;
    }
    else
        os_ThrowError(-1);
}

char* pull_file(ti_file_t* file)
{
    if(file != NULL)
    {   
        if(file->ti_var_file != 0)
        {
            file_reset:
            if(file->ti_mode == "r" || file->ti_mode == "r+" || file->ti_mode == "w+" || file->ti_mode == "a+")
            {
                uint16_t isize = ti_GetSize(file->ti_var_file);

                char* data = (char*)malloc(isize);
                if(data == NULL)
                    os_ThrowError(-1);
                else
                {
                    size_t rsize = ti_Read(data,CHUNKSIZE,isize,file->ti_var_file);
                    if(rsize == isize)
                    {
                        return data;
                    }
                    else
                        os_ThrowError(-1);
                }
            }
            else
            {
                ti_var_t reset = ti_Open(file->ti_file_name,"r+");
                if(reset == 0)
                    os_ThrowError(-1);
                else
                {
                    void* copy = memcpy(file->ti_mode,"r+",3);
                    if(copy == NULL)
                        os_ThrowError(-1);
                    else
                    {
                        file->ti_var_file = reset;
                        goto file_reset;
                    }
                }
            }
        }
    }
    os_ThrowError(-1);
    return NULL;
}

void close_file(ti_file_t* file)
{
    if(file != NULL)
    {
        ti_Close(file->ti_var_file);
        free(file);
        file = NULL;
    }
    else
        os_ThrowError(-1);
}




#endif