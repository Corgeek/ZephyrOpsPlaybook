/*
 * Copyright (c) 2026 Takayuki Goto <tkg.develop@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#define COM_HOST_RX_TIMEOUT     (0)
#define COM_HOST_RXBUF_SIZE     (sizeof(struct com_host_frame) * 4)
#define COM_HOST_RINGSIZE       (sizeof(struct com_host_frame) * 16)
#define COM_HOST_FRAME_HEAD1    (0xAA)
#define COM_HOST_FRAME_HEAD2    (0x55)
#define COM_HOST_FRAME_TERM1    (0x0D)
#define COM_HOST_FRAME_TERM2    (0x0A)

struct com_host_frame {
    uint8_t head1;
    uint8_t head2;
    uint8_t cmd;
    uint8_t sub1;
    uint8_t sub2;
    uint8_t chksum;
    uint8_t term1;
    uint8_t term2;
};

#define COM_DATA_ARRAY_SIZE (26 + 32)

struct com_data_frame {
    uint8_t head1;
    uint8_t head2;
    uint8_t cmd;
    uint8_t array[COM_DATA_ARRAY_SIZE];
    uint8_t chksum;
    uint8_t term1;
    uint8_t term2;
};
