/* generated vector source file - do not edit */
        #include "bsp_api.h"
        /* Do not build these data structures if no interrupts are currently allocated because IAR will have build errors. */
        #if VECTOR_DATA_IRQ_COUNT > 0
        BSP_DONT_REMOVE const fsp_vector_t g_vector_table[BSP_ICU_VECTOR_NUM_ENTRIES] BSP_PLACE_IN_SECTION(BSP_SECTION_APPLICATION_VECTORS) =
        {
                        [44] = uarta_txi_isr, /* UARTA1 TXI (UARTA1 transmission transfer end or buffer empty interrupt) */
            [45] = uarta_rxi_isr, /* UARTA1 RXI (UARTA1 reception transfer end) */
        };
        #if BSP_FEATURE_ICU_HAS_IELSR
        const bsp_interrupt_event_t g_interrupt_event_link_select[BSP_ICU_VECTOR_NUM_ENTRIES] =
        {
            [44] = BSP_PRV_VECT_ENUM(EVENT_UARTA1_TXI,FIXED), /* UARTA1 TXI (UARTA1 transmission transfer end or buffer empty interrupt) */
            [45] = BSP_PRV_VECT_ENUM(EVENT_UARTA1_RXI,FIXED), /* UARTA1 RXI (UARTA1 reception transfer end) */
        };
        #endif
        #endif
