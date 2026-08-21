#include <stdio.h>
#include "rs_stdio_comms.h"

void syscalls_picolib_stdio_to_comms_demo(void)
{
    extern fsp_err_t RS_STDIO_COMMS_CheckApplicationConfiguration(void);

    fsp_err_t err = FSP_SUCCESS;
    err = RS_STDIO_COMMS_CheckApplicationConfiguration();

    while(FSP_SUCCESS != err);

    printf("\rSystem Init\r\n");

    while (1)
    {
        int c = getchar();
        printf("You typed: %c\r\n", c);
    }
    
}
