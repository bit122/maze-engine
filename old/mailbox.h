#ifndef MAILBOX_H
#define MAILBOX_H

#include <stdint.h>

#define MBOX_RESPONSE 0x80000000
#define MBOX_REQUEST  0x00000000

#define MBOX_CH_PROP 8

int mailbox_call(uint8_t ch, volatile uint32_t *mbox);
int fb_mailbox_init(uint32_t width, uint32_t height, uint32_t depth,
                    uint32_t *fb_base, uint32_t *fb_size, uint32_t *fb_pitch);

#endif