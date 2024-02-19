
#ifndef _D_DEBUG_INCLUDED_
#define _D_DEBUG_INCLUDED_


#include <main.h>
#include <stm32f1xx_hal.h>


#ifdef __cplusplus
extern "C" {
#endif


#if (D_DEBUG)


typedef HAL_StatusTypeDef (*d_debug_cmd_handler_fn_t)(char *args);


extern char *d_debug_status[];


#    define d_debug_status_to_str(status)                                    \
    (status <= HAL_TIMEOUT ? d_debug_status[status] : "UNKNOWN_HAL_STATUS")  \


/* weak assertion marco. The value is not asserted if D_DEBUG is 0. */

#    define d_debug_assertw(value)                                      \
    if (!(value)) {                                                     \
        d_debug_fatal("ASSERTW:%s:%d", __FILE__, __LINE__);             \
    }


#    define d_debug_assert_hal(value, expected)                         \
    d_debug_assert_halv(value, expected, __FILE__, __LINE__);


void d_debug_init(void);
void d_debug_log(const char *format, ...);
void d_debug_uart_rx_process(char c);
void d_debug_cmd_register(char *name, d_debug_cmd_handler_fn_t handler);
void d_debug_cmd_process(void);


#else


#    define d_debug_uart        NULL


#    define d_debug_init()


#    define d_debug_assertw(value)


#    define d_debug_log(...)


#    define d_debug_assert_hal(value, expected)                              \
    d_debug_assert_halv(value, expected, NULL, 0);


#    define d_debug_uart_rx_process(c)


#    define d_debug_cmd_register(name, handler)


#    define d_debug_cmd_process()


#endif


#define d_debug_fatal(...)                                               \
    d_debug_log("A FATAL ERROR HAS OCCURED:");                           \
    d_debug_log(__VA_ARGS__);                                            \
    Error_Handler();


#define d_debug_assert(value)                                            \
    if (!(value)) {                                                      \
        d_debug_fatal("ASSERT:%s:%d", __FILE__, __LINE__);               \
    }


#define d_debug_assert_hok(value)                                        \
    d_debug_assert_hal(value, HAL_OK);


#define d_debug_assertw_tim_ch(ch)                                       \
    d_debug_assertw((ch) == TIM_CHANNEL_1 || (ch) == TIM_CHANNEL_2 ||    \
            (ch) == TIM_CHANNEL_3 || (ch) == TIM_CHANNEL_4);


#define d_debug_assertw_adc_ch(ch)                                       \
    d_debug_assertw((ch) == ADC_CHANNEL_0 || (ch) == ADC_CHANNEL_1 ||    \
            (ch) == ADC_CHANNEL_2 || (ch) == ADC_CHANNEL_3 ||            \
            (ch) == ADC_CHANNEL_4 || (ch) == ADC_CHANNEL_5 ||            \
            (ch) == ADC_CHANNEL_6 || (ch) == ADC_CHANNEL_7 ||            \
            (ch) == ADC_CHANNEL_8 || (ch) == ADC_CHANNEL_9 ||            \
            (ch) == ADC_CHANNEL_10 || (ch) == ADC_CHANNEL_11 ||          \
            (ch) == ADC_CHANNEL_12 || (ch) == ADC_CHANNEL_13 ||          \
            (ch) == ADC_CHANNEL_14 || (ch) == ADC_CHANNEL_15 ||          \
            (ch) == ADC_CHANNEL_16 || (ch) == ADC_CHANNEL_17);


#define d_debug_assertw_adc_irank(rank)                                  \
    d_debug_assertw(                                                     \
            (rank) == ADC_INJECTED_RANK_1 ||                             \
            (rank) == ADC_INJECTED_RANK_2 ||                             \
            (rank) == ADC_INJECTED_RANK_3 ||                             \
            (rank) == ADC_INJECTED_RANK_4);


static inline void
d_debug_assert_halv(HAL_StatusTypeDef value, HAL_StatusTypeDef expected,
        const char *file, int line)
{
    if (value != expected) {


#if (D_DEBUG)


        d_debug_fatal("ASSERTH:%s:%d: %s (%u) != %s (%u)", file, line,
                d_debug_status_to_str(value), value,
                d_debug_status_to_str(expected), expected);


#else


        UNUSED(file);
        UNUSED(line);
        d_debug_fatal("ASSERTH: %u != %u", value, expected);


#endif


    }
}


#ifdef __cplusplus
}
#endif


#endif /* _D_DEBUG_INCLUDED_ */
