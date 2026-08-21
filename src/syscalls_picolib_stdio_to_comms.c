/*
 * Blocking COMMS-backed stdio implementation.
 *
 * Each getc() and putc() waits for the underlying
 * COMMS transfer to complete before returning.
 */


#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#if !defined (__PICOLIBC__) && !defined(UNIT_TEST_COMMS)
#error "Use this file only with picolibc. Typically packaged with LLVM ARM Embedded Toolchain."
#endif /* defined (__PICOLIBC__) */

#include "rm_comms_api.h"

static volatile bool tx_busy = false;
static volatile bool rx_busy = false;

static rm_comms_instance_t * p_comms_jlob_vcom = NULL;

static int comms_putc(char c, FILE *f);
static int comms_getc(FILE *f);

#if defined(__PICOLIBC__) && !defined (UNIT_TEST_COMMS)
static FILE g_stdin_file  = FDEV_SETUP_STREAM(NULL,
                                              comms_getc,
                                              NULL,
                                              _FDEV_SETUP_READ);

static FILE g_stdout_file = FDEV_SETUP_STREAM(comms_putc,
                                              NULL,
                                              NULL,
                                              _FDEV_SETUP_WRITE);

FILE *const stdin  = &g_stdin_file;
FILE *const stdout = &g_stdout_file;
FILE *const stderr = &g_stdout_file;
#endif 

static fsp_err_t jlob_comms_init_once(void);

static bool g_stdio_comms_initialized = false;

static void comms_wait_tx_complete(void)
{
    while (tx_busy)
    {
        __NOP();
    }
    return;
}


static void comms_wait_rx_complete(void)
{
    while (rx_busy)
    {
        __NOP();
    }
    return;
}


#ifdef UNIT_TEST_COMMS
void picolibc_stdio_to_comms_test_reset(void)
{
    tx_busy = false;
    rx_busy = false;
    g_stdio_comms_initialized = false;
    p_comms_jlob_vcom = NULL;
}
#endif


#if defined(BSP_CFG_RTOS) && (BSP_CFG_RTOS == 0)
void comms_jlob_vcom_callback(rm_comms_callback_args_t *p_args)
{
    if(NULL == p_args)
    {
        return;
    }

    rm_comms_event_t event = p_args->event;

    switch(event)
    {
        case RM_COMMS_EVENT_TX_OPERATION_COMPLETE:
        {
            tx_busy = false;
        }
        break;

        case RM_COMMS_EVENT_RX_OPERATION_COMPLETE:
        {
            rx_busy = false;
        }
        break;

        default:
        {
            ;
        }
        break;
    }
}
#endif

static int comms_getc(FILE *f)
{
    if (stdin != f)
    {
        return EOF;
    }

    unsigned char c = 0xFF;

    fsp_err_t err = FSP_SUCCESS;

    err = jlob_comms_init_once ();
    if (FSP_SUCCESS != err)
    {
        return EOF;
    }

#if defined(BSP_CFG_RTOS) && (BSP_CFG_RTOS == 0)
    comms_wait_rx_complete();
    rx_busy = true;
#endif

    err = p_comms_jlob_vcom->p_api->read(p_comms_jlob_vcom->p_ctrl, (uint8_t * const)&c, 1);

    if(FSP_SUCCESS != err)
    {
        rx_busy = false;
        return EOF;
    }

#if defined(BSP_CFG_RTOS) && (BSP_CFG_RTOS == 0)
    /* Wait for completion */
    comms_wait_rx_complete();
#endif

    int ret = c;

    /* Return failure */
    return ret;
}

static int comms_putc(char c, FILE *f)
{
    if ((stdout != f) && (stderr != f))
    {
        return EOF;
    }

    fsp_err_t err = FSP_SUCCESS;

    err = jlob_comms_init_once();

    if(FSP_SUCCESS != err)
    {
        return EOF;
    }
    
#if defined(BSP_CFG_RTOS) && (BSP_CFG_RTOS == 0)
    comms_wait_tx_complete();
    tx_busy = true;
#endif

    err = p_comms_jlob_vcom->p_api->write(p_comms_jlob_vcom->p_ctrl, (uint8_t * const)&c, 1);

    if(FSP_SUCCESS != err)
    {
        tx_busy = false;
        return EOF;
    }

#if defined(BSP_CFG_RTOS) && (BSP_CFG_RTOS == 0)
    comms_wait_tx_complete();
#endif

    return c;
}

static fsp_err_t jlob_comms_init_once(void)
{   
    fsp_err_t retval = FSP_SUCCESS; 
    FSP_CRITICAL_SECTION_DEFINE;
    FSP_CRITICAL_SECTION_ENTER;

    if (g_stdio_comms_initialized)
    {
        retval = FSP_SUCCESS;
        goto jlob_comms_init_once_exit;
    }
    
    fsp_err_t err = FSP_SUCCESS;    
    
#if defined(UNIT_TEST_COMMS)
    p_comms_jlob_vcom = &g_comms_jlob_vcom_fake;
#else
    extern rm_comms_instance_t g_comms_jlob_vcom;
    p_comms_jlob_vcom = &g_comms_jlob_vcom;
#endif

    FSP_ASSERT(NULL != p_comms_jlob_vcom->p_api);
    FSP_ASSERT(NULL != p_comms_jlob_vcom->p_ctrl);
    FSP_ASSERT(NULL != p_comms_jlob_vcom->p_cfg);
    
    if ((NULL == p_comms_jlob_vcom) ||
        (NULL == p_comms_jlob_vcom->p_api) ||
        (NULL == p_comms_jlob_vcom->p_ctrl) ||
        (NULL == p_comms_jlob_vcom->p_cfg))
    {
        retval = FSP_ERR_ASSERTION;
        goto jlob_comms_init_once_exit;
    }


    err = p_comms_jlob_vcom->p_api->open(p_comms_jlob_vcom->p_ctrl, p_comms_jlob_vcom->p_cfg);

    if (FSP_SUCCESS != err)
    {
        retval = err;
        goto jlob_comms_init_once_exit;
    }

#if defined(BSP_CFG_RTOS) && (BSP_CFG_RTOS == 0)
    if(comms_jlob_vcom_callback != p_comms_jlob_vcom->p_cfg->p_callback)
    {
        err = p_comms_jlob_vcom->p_api->callbackSet(p_comms_jlob_vcom->p_ctrl, comms_jlob_vcom_callback, NULL);

        if (FSP_SUCCESS != err)
        {
            retval = err;
            goto jlob_comms_init_once_exit;
        }

    }
#endif
    g_stdio_comms_initialized = true;

jlob_comms_init_once_exit:
    FSP_CRITICAL_SECTION_EXIT;
    return retval;
}