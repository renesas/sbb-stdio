/* generated HAL source file - do not edit */
#include "hal_data.h"
uarta_instance_ctrl_t     g_uart_jlob_vcom_ctrl;

            uarta_baud_setting_t      g_uart_jlob_vcom_baud_setting =
            {
                 #if (BSP_CFG_UARTA1_CLOCK_SOURCE == BSP_CLOCKS_SOURCE_CLOCK_MAIN_OSC)

/* Baud rate calculated with Actual_Error0.22%. */
/* The permissible baud rate error range during reception: -5.15% ~ 5.14% */
  .utanck_clock_b.utasel = UARTA_CLOCK_SOURCE_MOSC
, .utanck_clock_b.utanck = UARTA_CLOCK_DIV_1
, .brgca = 87
, .delay_time = 1
 #elif (BSP_CFG_UARTA1_CLOCK_SOURCE == BSP_CLOCKS_SOURCE_CLOCK_HOCO)

/* Baud rate calculated with Actual_Error0.08%. */
/* The permissible baud rate error range during reception: -5.19% ~ 5.18% */
  .utanck_clock_b.utasel = UARTA_CLOCK_SOURCE_HOCO
, .utanck_clock_b.utanck = UARTA_CLOCK_DIV_1
, .brgca = 139
, .delay_time = 1
 #elif (BSP_CFG_UARTA1_CLOCK_SOURCE == BSP_CLOCKS_SOURCE_CLOCK_MOCO)

/* Baud rate calculated with Actual_Error2.12%. */ 
/* The permissible baud rate error range during reception: -4.67% ~ 4.62% */
  .utanck_clock_b.utasel = UARTA_CLOCK_SOURCE_MOCO
, .utanck_clock_b.utanck = UARTA_CLOCK_DIV_1
, .brgca = 17
, .delay_time = 1
 #elif ((BSP_CFG_UARTA1_CLOCK_SOURCE == BSP_CFG_FSXP_SOURCE) || (BSP_CFG_UARTA1_CLOCK_SOURCE == BSP_CLOCKS_SOURCE_CLOCK_LOCO))

/* Baud rate calculated with Actual_Error100%. */
/* The permissible baud rate error range during reception: Invalid Range Error */
  .utanck_clock_b.utasel = 0
, .utanck_clock_b.utanck = 0
, .brgca = 0
, .delay_time = 31
 #elif (BSP_CFG_UARTA1_CLOCK_SOURCE == BSP_CLOCKS_SOURCE_CLOCK_SUBCLOCK)

/* Baud rate calculated with Actual_Error100%. */
/* The permissible baud rate error range during reception: Invalid Range Error */
  .utanck_clock_b.utasel = 0
, .utanck_clock_b.utanck = 0
, .brgca = 0
, .delay_time = 31
 #endif
            };

            /** UART extended configuration for UART on UARTA HAL driver */
            const uarta_extended_cfg_t g_uart_jlob_vcom_cfg_extend =
            {
                .transfer_dir            = UARTA_DIR_BIT_LSB_FIRST,
                .transfer_level          = UARTA_ALV_BIT_POSITIVE_LOGIC,
                .clock_output            = UARTA_CLOCK_OUTPUT_DISABLED,
                .p_baud_setting          = &g_uart_jlob_vcom_baud_setting,
            };

            /** UART interface configuration */
            const uart_cfg_t g_uart_jlob_vcom_cfg =
            {
                .channel             = 1,
                .data_bits           = UART_DATA_BITS_8,
                .parity              = UART_PARITY_OFF,
                .stop_bits           = UART_STOP_BITS_1,
                .p_callback          = uart_jlob_vcom_callback,
                .p_context           = NULL,
                .p_extend            = &g_uart_jlob_vcom_cfg_extend,
#define RA_NOT_DEFINED (1)
#if (RA_NOT_DEFINED == RA_NOT_DEFINED)
                .p_transfer_tx       = NULL,
#else
                .p_transfer_tx       = &RA_NOT_DEFINED,
#endif
#if (RA_NOT_DEFINED == RA_NOT_DEFINED)
                .p_transfer_rx       = NULL,
#else
                .p_transfer_rx       = &RA_NOT_DEFINED,
#endif
#undef RA_NOT_DEFINED
                .rxi_ipl             = (2),
                .txi_ipl             = (2),
                .eri_ipl             = (BSP_IRQ_DISABLED),
#if defined(VECTOR_NUMBER_UARTA1_RXI)
                .rxi_irq             = VECTOR_NUMBER_UARTA1_RXI,
#else
                .rxi_irq             = FSP_INVALID_VECTOR,
#endif
#if defined(VECTOR_NUMBER_UARTA1_TXI)
                .txi_irq             = VECTOR_NUMBER_UARTA1_TXI,
#else
                .txi_irq             = FSP_INVALID_VECTOR,
#endif
#if defined(VECTOR_NUMBER_UARTA1_ERRI)
                .eri_irq             = VECTOR_NUMBER_UARTA1_ERRI,
#else
                .eri_irq             = FSP_INVALID_VECTOR,
#endif
            };

/* Instance structure to use this module. */
const uart_instance_t g_uart_jlob_vcom =
{
    .p_ctrl        = &g_uart_jlob_vcom_ctrl,
    .p_cfg         = &g_uart_jlob_vcom_cfg,
    .p_api         = &g_uart_on_uarta
};
void g_hal_init(void) {
g_common_init();
}
