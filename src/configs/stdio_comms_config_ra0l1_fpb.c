#include <stddef.h>
#include <string.h>

#include "hal_data.h"
#include "rs_stdio_comms.h"

#if defined(BOARD_RA0L1_FPB)

#if !defined(R_UARTA_H)
#error "Please enable using the Smart Configurator configuration.xml > Components > Renesas > HAL Drivers > all > r_uarta."
#endif

static uarta_instance_ctrl_t g_uart_jlob_vcom_ref_ctrl;

static const uarta_baud_setting_t g_uart_jlob_vcom_ref_baud_setting =
{
#if (BSP_CFG_UARTA1_CLOCK_SOURCE == BSP_CLOCKS_SOURCE_CLOCK_MAIN_OSC)

    /* Baud rate calculated with Actual_Error0.22%. */
    /* The permissible baud rate error range during reception: -5.15% ~ 5.14% */
    .utanck_clock_b.utasel = UARTA_CLOCK_SOURCE_MOSC,
    .utanck_clock_b.utanck = UARTA_CLOCK_DIV_1,
    .brgca = 87,
    .delay_time = 1,

#elif (BSP_CFG_UARTA1_CLOCK_SOURCE == BSP_CLOCKS_SOURCE_CLOCK_HOCO)

    /* Baud rate calculated with Actual_Error0.08%. */
    /* The permissible baud rate error range during reception: -5.19% ~ 5.18% */
    .utanck_clock_b.utasel = UARTA_CLOCK_SOURCE_HOCO,
    .utanck_clock_b.utanck = UARTA_CLOCK_DIV_1,
    .brgca = 139,
    .delay_time = 1,

#elif (BSP_CFG_UARTA1_CLOCK_SOURCE == BSP_CLOCKS_SOURCE_CLOCK_MOCO)

    /* Baud rate calculated with Actual_Error2.12%. */
    /* The permissible baud rate error range during reception: -4.67% ~ 4.62% */
    .utanck_clock_b.utasel = UARTA_CLOCK_SOURCE_MOCO,
    .utanck_clock_b.utanck = UARTA_CLOCK_DIV_1,
    .brgca = 17,
    .delay_time = 1,

#elif ((BSP_CFG_UARTA1_CLOCK_SOURCE == BSP_CFG_FSXP_SOURCE) || \
       (BSP_CFG_UARTA1_CLOCK_SOURCE == BSP_CLOCKS_SOURCE_CLOCK_LOCO))

    /* Baud rate calculated with Actual_Error100%. */
    /* The permissible baud rate error range during reception: Invalid Range Error */
    .utanck_clock_b.utasel = 0,
    .utanck_clock_b.utanck = 0,
    .brgca = 0,
    .delay_time = 31,

#elif (BSP_CFG_UARTA1_CLOCK_SOURCE == BSP_CLOCKS_SOURCE_CLOCK_SUBCLOCK)

    /* Baud rate calculated with Actual_Error100%. */
    /* The permissible baud rate error range during reception: Invalid Range Error */
    .utanck_clock_b.utasel = 0,
    .utanck_clock_b.utanck = 0,
    .brgca = 0,
    .delay_time = 31,

#endif
};

/** UART extended configuration for UART on UARTA HAL driver */
static const uarta_extended_cfg_t g_uart_jlob_vcom_ref_cfg_extend =
{
    .transfer_dir = UARTA_DIR_BIT_LSB_FIRST,
    .transfer_level = UARTA_ALV_BIT_POSITIVE_LOGIC,
    .clock_output = UARTA_CLOCK_OUTPUT_DISABLED,
    .p_baud_setting = (uarta_baud_setting_t *)&g_uart_jlob_vcom_ref_baud_setting,
};

/** UART interface configuration */
static const uart_cfg_t g_uart_jlob_vcom_ref_cfg =
{
    .channel = 1,
    .data_bits = UART_DATA_BITS_8,
    .parity = UART_PARITY_OFF,
    .stop_bits = UART_STOP_BITS_1,
    .p_callback = NULL,
    .p_context = NULL,
    .p_extend = &g_uart_jlob_vcom_ref_cfg_extend,

#define RA_NOT_DEFINED (1)
#if (RA_NOT_DEFINED == RA_NOT_DEFINED)
    .p_transfer_tx = NULL,
#else
    .p_transfer_tx = &RA_NOT_DEFINED,
#endif

#if (RA_NOT_DEFINED == RA_NOT_DEFINED)
    .p_transfer_rx = NULL,
#else
    .p_transfer_rx = &RA_NOT_DEFINED,
#endif
#undef RA_NOT_DEFINED

    .rxi_ipl = (2),
    .txi_ipl = (2),

#if defined(VECTOR_NUMBER_UARTA1_RXI)
    .rxi_irq = VECTOR_NUMBER_UARTA1_RXI,
#else
    .rxi_irq = FSP_INVALID_VECTOR,
#endif

#if defined(VECTOR_NUMBER_UARTA1_TXI)
    .txi_irq = VECTOR_NUMBER_UARTA1_TXI,
#else
    .txi_irq = FSP_INVALID_VECTOR,
#endif

#if defined(VECTOR_NUMBER_UARTA1_ERRI)
    .eri_irq = VECTOR_NUMBER_UARTA1_ERRI,
#else
    .eri_irq = FSP_INVALID_VECTOR,
#endif
};

/* Instance structure to use this module. */
static const uart_instance_t g_uart_jlob_vcom_ref =
{
    .p_ctrl = &g_uart_jlob_vcom_ref_ctrl,
    .p_cfg = &g_uart_jlob_vcom_ref_cfg,
    .p_api = &g_uart_on_uarta,
};

static rs_stdio_uart_cfg_t const rs_stdio_uart_ref =
{
    .rxd = IOPORT_PORT_01_PIN_05,
    .txd = IOPORT_PORT_01_PIN_06,

    .uart_instance = g_uart_jlob_vcom_ref,
    .uart_cfg = g_uart_jlob_vcom_ref_cfg,

    .uarta_baud_setting = g_uart_jlob_vcom_ref_baud_setting,
    .uarta_extended_cfg = g_uart_jlob_vcom_ref_cfg_extend,
    .uarta_instance_ctrl = {0},
};

rm_comms_uart_instance_ctrl_t g_comms_jlob_vcom_ref_ctrl;

#if BSP_CFG_RTOS == 1 // ThreadX

 #if !defined(g_comms_jlob_vcom_ref_tx_mutex)
 rm_comms_mutex_t g_comms_jlob_vcom_ref_tx_mutex =
 {
     .p_name = "g_comms_jlob_vcom_ref tx mutex",
 };
 #endif

 #if !defined(g_comms_jlob_vcom_ref_rx_mutex)
 rm_comms_mutex_t g_comms_jlob_vcom_ref_rx_mutex =
 {
     .p_name = "g_comms_jlob_vcom_ref rx mutex",
 };
 #endif

 #if !defined(g_comms_jlob_vcom_ref_tx_semaphore)
 rm_comms_semaphore_t g_comms_jlob_vcom_ref_tx_semaphore =
 {
     .p_name = "g_comms_jlob_vcom_ref tx semaphore",
 };
 #endif

  #if !defined(g_comms_jlob_vcom_ref_rx_semaphore)
 rm_comms_semaphore_t g_comms_jlob_vcom_ref_rx_semaphore =
 {
     .p_name = "g_comms_jlob_vcom_ref rx semaphore",
 };
 #endif

#elif BSP_CFG_RTOS == 2 // FreeRTOS

#if !defined(g_comms_jlob_vcom_ref_tx_mutex)
rm_comms_mutex_t g_comms_jlob_vcom_ref_tx_mutex;
#endif

#if !defined(g_comms_jlob_vcom_ref_rx_mutex)
rm_comms_mutex_t g_comms_jlob_vcom_ref_rx_mutex;
#endif
#if !defined(g_comms_jlob_vcom_ref_tx_semaphore)
rm_comms_semaphore_t g_comms_jlob_vcom_ref_tx_semaphore;
#endif

#if !defined(g_comms_jlob_vcom_ref_rx_semaphore)
rm_comms_semaphore_t g_comms_jlob_vcom_ref_rx_semaphore;
#endif

#else

#endif

rm_comms_uart_extended_cfg_t g_comms_jlob_vcom_ref_extended_cfg =
{
#if BSP_CFG_RTOS

#if !defined(g_comms_jlob_vcom_ref_tx_mutex)
    .p_tx_mutex = &g_comms_jlob_vcom_ref_tx_mutex,
#else
    .p_tx_mutex = NULL,
#endif

#if !defined(g_comms_jlob_vcom_ref_rx_mutex)
    .p_rx_mutex = &g_comms_jlob_vcom_ref_rx_mutex,
#else
    .p_rx_mutex = NULL,
#endif

#if !defined(g_comms_jlob_vcom_ref_tx_semaphore)
    .p_tx_semaphore = &g_comms_jlob_vcom_ref_tx_semaphore,
#else
    .p_tx_semaphore = NULL,
#endif

#if !defined(g_comms_jlob_vcom_ref_rx_semaphore)
    .p_rx_semaphore = &g_comms_jlob_vcom_ref_rx_semaphore,
#else
    .p_rx_semaphore = NULL,
#endif
    .mutex_timeout  = 0xFFFFFFFF,
#endif
  .p_uart = &g_uart0, };

const rm_comms_cfg_t g_comms_jlob_vcom_ref_cfg =
{ .semaphore_timeout = 0xFFFFFFFF,
  .p_lower_level_cfg = NULL,
  .p_extend = (void*) &g_comms_jlob_vcom_ref_extended_cfg,
  .p_callback = comms_jlob_vcom_callback, };

const rm_comms_instance_t g_comms_jlob_vcom_ref =
{ .p_ctrl = &g_comms_jlob_vcom_ref_ctrl, .p_cfg = &g_comms_jlob_vcom_ref_cfg, .p_api = &g_comms_on_comms_uart, };

rs_stdio_comms_cfg_t rs_stdio_comms_ref =
{
    .comms_instance = g_comms_jlob_vcom_ref,
    .comms_cfg = g_comms_jlob_vcom_ref_cfg,
    .stdio_uart_cfg = rs_stdio_uart_ref,
    .comms_uart_instance_ctrl = {0},
};

fsp_err_t RS_STDIO_COMMS_CheckApplicationConfiguration(void)
{
    extern uarta_baud_setting_t g_uart0_baud_setting;
    extern rm_comms_uart_extended_cfg_t g_comms_jlob_vcom_extended_cfg;
    
    rs_stdio_uart_cfg_t const rs_stdio_uart_check =
    {
        .rxd = IOPORT_PORT_01_PIN_05,
        .txd = IOPORT_PORT_01_PIN_06,
         .uart_instance = g_uart0,
         .uart_cfg = g_uart0_cfg,
         .uarta_baud_setting = g_uart0_baud_setting,
         .uarta_extended_cfg = g_uart0_cfg_extend,
         .uarta_instance_ctrl = {0},
    };
    rs_stdio_comms_cfg_t check =
    {
         .comms_instance = g_comms_jlob_vcom,
         .comms_cfg = g_comms_jlob_vcom_cfg,
#if defined(RM_COMMS_UART_H)
         .stdio_uart_cfg = rs_stdio_uart_check,
         .comms_uart_extended_cfg = g_comms_jlob_vcom_extended_cfg,
         .comms_uart_instance_ctrl = g_comms_jlob_vcom_ctrl,
    };
#endif

    check.stdio_uart_cfg.uart_instance.p_cfg = &check.stdio_uart_cfg.uart_cfg;
    check.stdio_uart_cfg.uart_instance.p_ctrl = &check.stdio_uart_cfg.uarta_instance_ctrl;

    check.comms_instance.p_cfg = &check.comms_cfg;
    check.comms_instance.p_ctrl = &check.comms_uart_instance_ctrl;
    check.comms_cfg.p_extend = &check.comms_uart_extended_cfg;
    rm_comms_uart_extended_cfg_t * p_extend = (rm_comms_uart_extended_cfg_t *)check.comms_instance.p_cfg->p_extend;
    p_extend->p_uart = &check.stdio_uart_cfg.uart_instance;

    fsp_err_t err = RS_STDIO_COMMS_CheckConfig(&check);

    return err;
}

#endif /* defined(BOARD_RA0L1_FPB) */
