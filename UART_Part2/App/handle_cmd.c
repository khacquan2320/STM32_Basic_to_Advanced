#include "handle_cmd.h"
#include "led_driver.h"
#include <string.h>

void handle_cmd(char *buff_cmd , char *cmd , int on_off)
{
    char *pCMDOn = strstr(buff_cmd,cmd);
    if(pCMDOn != NULL )
    {
        pCMDOn += strlen(cmd);
        if(*pCMDOn == ':')
        {
            pCMDOn ++; // tro den so
        }
        int number = 0;
        while(1)
        {
        if(*pCMDOn >= '0' && *pCMDOn <= '9')
        {
            number *= 10;
            number += (*pCMDOn - '0');
        }
        else if (*pCMDOn == ',')
        {
            control_led(number,on_off);
            number = 0;
        }
        else if(*pCMDOn == ';')
        {
           control_led(number,on_off);
            break;
        }
        pCMDOn ++;
        }
    }
}