#include "rs_stdio_comms.h"

fsp_err_t RS_STDIO_COMMS_GetConfigSize(uint32_t * p_size)
{
    FSP_ERROR_RETURN(NULL != p_size, FSP_ERR_INVALID_POINTER);
    *p_size = sizeof(rs_stdio_comms_cfg_t);
    return FSP_SUCCESS;
}

fsp_err_t RS_STDIO_COMMS_GenConfig(rs_stdio_comms_cfg_t * const p_stdio_comms_cfg, uint32_t const config_size)
{
    FSP_ASSERT(NULL != p_stdio_comms_cfg);

    fsp_err_t err = FSP_SUCCESS;
    uint32_t needed_size = 0;

    extern rs_stdio_comms_cfg_t const rs_stdio_comms_ref;

    err = RS_STDIO_COMMS_GetConfigSize(&needed_size);

    FSP_ERROR_RETURN(config_size == needed_size, FSP_ERR_INVALID_ARGUMENT);

    memcpy(p_stdio_comms_cfg, &rs_stdio_comms_ref, sizeof(rs_stdio_comms_ref));
    p_stdio_comms_cfg->comms_instance.p_cfg = &p_stdio_comms_cfg->comms_cfg; 

#if defined(RM_COMMS_UART_H)
    err = RS_STDIO_UART_GenConfig(&p_stdio_comms_cfg->stdio_uart_cfg, sizeof(p_stdio_comms_cfg->stdio_uart_cfg));
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);    
    rm_comms_uart_extended_cfg_t * p_extended_cfg = (rm_comms_uart_extended_cfg_t * )p_stdio_comms_cfg->comms_instance.p_cfg->p_extend;
    p_extended_cfg->p_uart = &p_stdio_comms_cfg->stdio_uart_cfg.uart_instance; 
#endif    

    err = RS_STDIO_COMMS_CheckConfig(p_stdio_comms_cfg);

    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    return FSP_SUCCESS;
}


#if defined(RM_COMMS_UART_H)
static fsp_err_t check_config_implementation(rs_stdio_comms_cfg_t const * const p_cfg)
{
    rm_comms_uart_instance_ctrl_t comms_uart_instance_ctrl_zeros;

    FSP_ERROR_RETURN((&g_comms_on_comms_uart == p_cfg->comms_instance.p_api), FSP_ERR_INVALID_POINTER);
    memset(&comms_uart_instance_ctrl_zeros, 0, sizeof(comms_uart_instance_ctrl_zeros));

    rm_comms_uart_extended_cfg_t const * const p_extended_cfg = (rm_comms_uart_extended_cfg_t * )p_cfg->comms_instance.p_cfg->p_extend;

    FSP_ERROR_RETURN( (NULL != p_extended_cfg), FSP_ERR_INVALID_POINTER);
    FSP_ERROR_RETURN( (NULL == p_cfg->comms_instance.p_cfg->p_lower_level_cfg), FSP_ERR_INVALID_POINTER);

    FSP_ERROR_RETURN( NULL != p_extended_cfg->p_uart, FSP_ERR_INVALID_POINTER);

    fsp_err_t err = FSP_SUCCESS;
    err = RS_STDIO_UART_CheckConfig(&p_cfg->stdio_uart_cfg);
    FSP_ERROR_RETURN((FSP_SUCCESS == err), err);

    FSP_ERROR_RETURN( NULL != p_extended_cfg->p_uart->p_cfg, FSP_ERR_INVALID_POINTER);
    FSP_ERROR_RETURN( p_extended_cfg->p_uart->p_cfg == p_cfg->stdio_uart_cfg.uart_instance.p_cfg, FSP_ERR_INVALID_POINTER);

    int32_t diff = memcmp(&p_cfg->comms_uart_instance_ctrl, &comms_uart_instance_ctrl_zeros, sizeof(p_cfg->comms_uart_instance_ctrl));

    FSP_ERROR_RETURN(0 == diff, FSP_ERR_INVALID_DATA);

    return err;
}
#endif

static fsp_err_t check_config_generics(rs_stdio_comms_cfg_t const * const p_cfg)
{
    FSP_ERROR_RETURN((NULL != p_cfg->comms_instance.p_api), FSP_ERR_INVALID_POINTER);
    FSP_ERROR_RETURN((NULL != p_cfg->comms_instance.p_cfg), FSP_ERR_INVALID_POINTER);
    FSP_ERROR_RETURN((NULL != p_cfg->comms_instance.p_ctrl), FSP_ERR_INVALID_POINTER);

    FSP_ERROR_RETURN((NULL == p_cfg->comms_instance.p_cfg->p_lower_level_cfg), FSP_ERR_INVALID_POINTER);
    FSP_ERROR_RETURN((NULL != p_cfg->comms_instance.p_cfg->p_extend), FSP_ERR_INVALID_POINTER);

    return FSP_SUCCESS;
}

fsp_err_t RS_STDIO_COMMS_CheckConfig(rs_stdio_comms_cfg_t const * const p_cfg)
{
    fsp_err_t err = FSP_SUCCESS;
    err = check_config_generics(p_cfg);
    FSP_ERROR_RETURN((FSP_SUCCESS == err), err);

    err = check_config_implementation(p_cfg);
    FSP_ERROR_RETURN((FSP_SUCCESS == err), err);

    return err;
}


