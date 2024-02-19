
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stm32f1xx_hal.h>

#include <d_debug.h>

#include "d_main.h"


#ifdef __cplusplus
extern "C" {
#endif


#if (D_DEBUG)


/* Message buffer size */

#    define D_DEBUG_MAX_LEN           128

/* Reserved space in message buffer for a null-byte and/or NL */

#    define D_DEBUG_RESERVED          3


/* 
 * Number of `d_debug_write` fails after which the logging will
 * no longer work.
 */

#    define D_DEBUG_MAX_FAILS         128


#    define D_DEBUG_CMD_MAXN          32
#    define D_DEBUG_CMD_MAX_NAME_LEN  32
#    define D_DEBUG_CMD_MAX_MSG_LEN                                \
    (sizeof ("DBG") - 1 + 1 + D_DEBUG_CMD_MAX_NAME_LEN + 1 + 256)


struct d_debug_cmd {
    char                        *name;
    d_debug_cmd_handler_fn_t     handler;
};


#    define d_debug_write_cstr(cstr)                               \
    d_debug_write(cstr "\r\n", sizeof (cstr) - 1 + 2)


static HAL_StatusTypeDef d_debug_write(const char *buffer, size_t length);
static inline void d_debug_uart_process(void);
static struct d_debug_cmd *d_debug_cmd_find(char *name);
static inline void d_debug_cmd_parse(char *p);


char                    *d_debug_status[] = {
    "HAL_OK",
    "HAL_ERROR",
    "HAL_BUSY",
    "HAL_TIMEOUT"
};


static volatile int           d_debug_uart_available = 0;
static char                   d_debug_uart_buf[D_DEBUG_CMD_MAX_MSG_LEN + 1];
static char                  *d_debug_uart_buf_last = d_debug_uart_buf;
static char                  *d_debug_uart_buf_end = 
    d_debug_uart_buf + D_DEBUG_CMD_MAX_MSG_LEN;

static struct d_debug_cmd     d_debug_cmds[D_DEBUG_CMD_MAXN];
static struct d_debug_cmd    *d_debug_cmds_last = d_debug_cmds;
static struct d_debug_cmd    *d_debug_cmds_end =
    &d_debug_cmds[D_DEBUG_CMD_MAXN - 1];


void
d_debug_init(void)
{
    d_debug_assert(HAL_OK == 0);
    d_debug_assert(HAL_ERROR == 1);
    d_debug_assert(HAL_BUSY == 2);
    d_debug_assert(HAL_TIMEOUT == 3);
}


void
d_debug_log(const char *format, ...)
{
    static unsigned int     failsn = 0;
    va_list                 args;
    char                    buffer[D_DEBUG_MAX_LEN];
    int                     n;

    if (failsn >= D_DEBUG_MAX_FAILS) {

        /* XXX: Stop any logging attempts after a series of failures */

        return;
    }

    va_start(args, format);
    n = vsnprintf(buffer, D_DEBUG_MAX_LEN - D_DEBUG_RESERVED, format, args);
    va_end(args);

    if (n < 0) {

        /* XXX: WTF? */

        d_debug_write_cstr("d_debug_log has failed because of vsnprintf");

        return;
    }

    if (n >= D_DEBUG_MAX_LEN - D_DEBUG_RESERVED) {
        d_debug_write_cstr("The following message has been truncated");
    }

    buffer[n++] = '\r';
    buffer[n++] = '\n';
    buffer[n] = 0;

    if (d_debug_write(buffer, n) != HAL_OK) {
        failsn++;

        if (failsn >= D_DEBUG_MAX_FAILS) {
            d_debug_write_cstr("D_DEBUG_MAX_FAILS has been reached");
        }
    }
}


void
d_debug_uart_rx_process(char c)
{
    if (d_debug_uart_available) {

        /* Drop any data until the last message is parsed. */

        return;
    }

    if (c == '\r') {
        
        /* Ignore CRs */

        return;
    }

    if (c == '\n') {
        d_debug_uart_available = 1;
        *d_debug_uart_buf_last++ = 0;

        return;
    }

    if (d_debug_uart_buf_last < d_debug_uart_buf_end) {
        *d_debug_uart_buf_last++ = c;
    } else {

        /* Buffer overflow. Drop the whole buffer. */

        d_debug_uart_buf_last = d_debug_uart_buf;
    }
}


void
d_debug_cmd_register(char *name, d_debug_cmd_handler_fn_t handler)
{
    struct d_debug_cmd    *cmd;

    d_debug_assert(d_debug_cmds_last < d_debug_cmds_end);

    for (cmd = d_debug_cmds; cmd < d_debug_cmds_last; cmd++) {
        d_debug_assert(strcmp(name, cmd->name) != 0);
    }

    cmd = d_debug_cmds_last++;
    cmd->name = name;
    cmd->handler = handler;
}


void
d_debug_cmd_process(void)
{
    d_debug_uart_process();
}


static inline void
d_debug_uart_process(void)
{
    int      available;

    available = d_debug_uart_available;

    if (!available) {
        return;
    }

    d_debug_cmd_parse(d_debug_uart_buf);

    d_debug_uart_buf_last = d_debug_uart_buf;
    d_debug_uart_available = 0;
}


static HAL_StatusTypeDef
d_debug_write(const char *buffer, size_t length)
{
    return d_main_debug_write(buffer, length);
}


static struct d_debug_cmd *
d_debug_cmd_find(char *name)
{
    struct d_debug_cmd    *cmd;

    for (cmd = d_debug_cmds; cmd < d_debug_cmds_last; cmd++) {
        if (strcmp(name, cmd->name) == 0) {
            return cmd;
        }
    }

    return NULL;
}


static inline void
d_debug_cmd_parse(char *p)
{
    enum {
        D_DEBUG_CMD_PARSE_D = 0,
        D_DEBUG_CMD_PARSE_B,
        D_DEBUG_CMD_PARSE_G,
        D_DEBUG_CMD_PARSE_SPACE1,
        D_DEBUG_CMD_PARSE_CMD,
    }                      state = 0;
    char                   cmd_buf[D_DEBUG_CMD_MAX_NAME_LEN + 1];
    char                  *cmd_buf_last = cmd_buf;
    char                  *cmd_buf_end = cmd_buf + D_DEBUG_CMD_MAX_NAME_LEN;
    char                  *args, c;
    struct d_debug_cmd    *cmd;
    HAL_StatusTypeDef      rc;

    for (;; p++) {
        c = *p;

        switch (state) {
        

        case D_DEBUG_CMD_PARSE_D:

            if (c == 'd') {
                state = D_DEBUG_CMD_PARSE_B;
            }

            break;


        case D_DEBUG_CMD_PARSE_B:

            state = c == 'b' ? D_DEBUG_CMD_PARSE_G : D_DEBUG_CMD_PARSE_D;

            break;


        case D_DEBUG_CMD_PARSE_G:

            state = c == 'g' ? D_DEBUG_CMD_PARSE_SPACE1 : D_DEBUG_CMD_PARSE_D;

            break;


        case D_DEBUG_CMD_PARSE_SPACE1:

            if (c == ' ') {
                cmd_buf_last = cmd_buf;
                state = D_DEBUG_CMD_PARSE_CMD;
            } else {
                state = D_DEBUG_CMD_PARSE_D;
            }

            break;


        case D_DEBUG_CMD_PARSE_CMD:

            if (c == ' ' || c == 0) {
                *cmd_buf_last = 0;
                cmd = d_debug_cmd_find(cmd_buf);

                if (cmd == NULL) {
                    d_debug_log("'%s' not found", cmd_buf);
                } else {
                    for (args = p; *args == ' '; args++);

                    rc = cmd->handler(args);

                    d_debug_log("'%s' %s", cmd_buf, d_debug_status_to_str(rc));
                }

                state = D_DEBUG_CMD_PARSE_D;
            } else if (cmd_buf_last < cmd_buf_end) {
                *cmd_buf_last++ = c;
            } else {

                /* Command name buffer overflow. */

                state = D_DEBUG_CMD_PARSE_D;
            }

            break;


        }

        if (*p == 0) {
            break;
        }
    }
}


#ifdef __cplusplus
}
#endif


#endif
