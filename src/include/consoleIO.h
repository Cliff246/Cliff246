#ifndef _CONSOLEIO_H
#define _CONSOLEIO_H

#include <tice.h>
#include <stdint.h>
#include <stdlib.h>

#include "filemanger.h"
#include "tistring.h"


void ti_get_input_d(char* data)
{
    uint16_t i = 0;
    if(data == NULL)
        return;
    for(char get_csc = os_GetCSC();get_csc != sk_Enter;i++)
       data[i] = get_csc;
    return;
}

char* ti_get_input_s()
{
    char* buffer = (char*)malloc(1);
    if(buffer != NULL)
    {
        for(uint16_t i = 0;i < UINT16_MAX;i++)
        {
            char get_char = os_GetCSC();
            char* temp = (char*)realloc(buffer,i+1);
            if(temp != NULL)
            {
                if(get_char == sk_Enter)
                {
                    buffer[i] = 0;
                    return buffer;
                }
                else
                {
                    buffer = temp;
                    buffer[i] = get_char;
                }
            }
            else
                os_ThrowError(-1);
        }
    }
    else
        os_ThrowError(-1);
    return buffer;
}



#endif