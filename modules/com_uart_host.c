/*
 * Copyright (c) 2026 Takayuki Goto <tkg.develop@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/sys/ring_buffer.h>
#include <zephyr/drivers/uart.h>
#include "boards/unique.h"
#include "drivers/serial/drv_uart_common.h"
#include "modules/com_uart_host.h"
#include "utils/generic.h"

RING_BUF_DECLARE(s_host_ringbuf, COM_HOST_RINGSIZE);

static struct ctx_hostcomm {
    const struct device *port;
    uint8_t rxbuf[COM_HOST_RXBUF_SIZE];
} s_ctx_hostcom;

static struct com_data_frame s_tx_frame;
static volatile bool s_tx_busy = false;

static
void com_host_callback(const struct device *uart_port, struct uart_event *evt, void *user_data)
{
    switch (evt->type) {
        case UART_RX_RDY:
            ring_buf_put(&s_host_ringbuf, evt->data.rx.buf + evt->data.rx.offset, evt->data.rx.len);
            break;

        case UART_RX_DISABLED:
            uart_rx_enable(uart_port, s_ctx_hostcom.rxbuf, sizeof(s_ctx_hostcom.rxbuf), COM_HOST_RX_TIMEOUT);
            break;

        case UART_TX_DONE:
        case UART_TX_ABORTED:
            s_tx_busy = false;
            break;

        default:
            break;
    }
}

bool com_host_init(const struct device *uart_port)
{
    uart_callback_set(uart_port, com_host_callback, NULL);
    uart_rx_enable(uart_port, s_ctx_hostcom.rxbuf, sizeof(s_ctx_hostcom.rxbuf), COM_HOST_RX_TIMEOUT);

    s_ctx_hostcom.port = uart_port;

    return true;
}

void com_host_close(void)
{
}

bool com_host_read(struct com_host_frame *frame)
{
    size_t ring_len = 0;

    ring_len = ring_buf_size_get(&s_host_ringbuf);
    if (ring_len < sizeof(*frame)) {
        return false;
    }

    size_t claimed = 0;
    uint8_t *raw = NULL;
    claimed = ring_buf_get_claim(&s_host_ringbuf, &raw, ring_len);
    if (claimed < sizeof(*frame)) {
        ring_buf_get_finish(&s_host_ringbuf, 0);
        return false;
    }

    const size_t seek_end = claimed - sizeof(*frame);
    for (size_t i = 0; i <= seek_end; ++i) {
        if ((raw[i] != COM_HOST_FRAME_HEAD1) || (raw[i + 1] != COM_HOST_FRAME_HEAD2))
            continue;

        memcpy(frame, &raw[i], sizeof(*frame));
        ring_buf_get_finish(&s_host_ringbuf, i + sizeof(*frame));
        return true;
    }

    ring_buf_get_finish(&s_host_ringbuf, seek_end);
    return false;
}

bool com_host_write(void)
{
    return true;
}

bool com_host_write_data(uint8_t cmd, const uint8_t array[COM_DATA_ARRAY_SIZE])
{
    if (!s_ctx_hostcom.port || s_tx_busy) {
        return false;
    }

    s_tx_frame.head1 = COM_HOST_FRAME_HEAD1;
    s_tx_frame.head2 = COM_HOST_FRAME_HEAD2;
    s_tx_frame.cmd   = cmd;
    memcpy(s_tx_frame.array, array, COM_DATA_ARRAY_SIZE);

    uint8_t crc = utl_crc8_update(0x00, &cmd, 1);
    s_tx_frame.chksum = utl_crc8_update(crc, array, COM_DATA_ARRAY_SIZE);
    s_tx_frame.term1  = COM_HOST_FRAME_TERM1;
    s_tx_frame.term2  = COM_HOST_FRAME_TERM2;

    s_tx_busy = true;
    uart_tx(s_ctx_hostcom.port, (const uint8_t *)&s_tx_frame, sizeof(s_tx_frame), SYS_FOREVER_US);

    return true;
}
