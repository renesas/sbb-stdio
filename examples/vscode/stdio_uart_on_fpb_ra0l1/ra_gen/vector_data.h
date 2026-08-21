/* generated vector header file - do not edit */
        #ifndef VECTOR_DATA_H
        #define VECTOR_DATA_H
        #ifdef __cplusplus
        extern "C" {
        #endif
                /* Number of interrupts allocated */
        #ifndef VECTOR_DATA_IRQ_COUNT
        #define VECTOR_DATA_IRQ_COUNT    (2)
        #endif
        /* ISR prototypes */
        void uarta_txi_isr(void);
        void uarta_rxi_isr(void);

        /* Vector table allocations */
        #define VECTOR_NUMBER_UARTA1_TXI ((IRQn_Type) 44) /* UARTA1 TXI (UARTA1 transmission transfer end or buffer empty interrupt) */
        #define UARTA1_TXI_IRQn          ((IRQn_Type) 44) /* UARTA1 TXI (UARTA1 transmission transfer end or buffer empty interrupt) */
        #define VECTOR_NUMBER_UARTA1_RXI ((IRQn_Type) 45) /* UARTA1 RXI (UARTA1 reception transfer end) */
        #define UARTA1_RXI_IRQn          ((IRQn_Type) 45) /* UARTA1 RXI (UARTA1 reception transfer end) */
        /* The number of entries required for the ICU vector table. */
        #define BSP_ICU_VECTOR_NUM_ENTRIES (46)

        #ifdef __cplusplus
        }
        #endif
        #endif /* VECTOR_DATA_H */
