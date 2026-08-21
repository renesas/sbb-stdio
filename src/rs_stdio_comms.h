#ifndef RS_STDIO_COMMS_H
#define RS_STDIO_COMMS_H

#include "rm_comms_api.h"
#include "rs_stdio_uart.h"

#if __has_include("rm_comms_uart.h")
#include "rm_comms_uart.h"
#else
#include "fake_comms.h"
#endif

typedef struct {
    rm_comms_instance_t comms_instance;
    rm_comms_cfg_t comms_cfg;
 #if defined(RM_COMMS_UART_H)   
    rs_stdio_uart_cfg_t stdio_uart_cfg;
    rm_comms_uart_extended_cfg_t comms_uart_extended_cfg;
    rm_comms_uart_instance_ctrl_t comms_uart_instance_ctrl;
 #endif
}rs_stdio_comms_cfg_t;


fsp_err_t RS_STDIO_COMMS_GetConfigSize(uint32_t * p_size);
fsp_err_t RS_STDIO_COMMS_CheckConfig(rs_stdio_comms_cfg_t const * const p_cfg);
fsp_err_t RS_STDIO_COMMS_GenConfig(rs_stdio_comms_cfg_t * const p_cfg, uint32_t const config_size);
fsp_err_t RS_STDIO_COMMS_CheckApplicationConfiguration(void);

#endif
