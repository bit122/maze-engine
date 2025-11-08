#include "mailbox.h"

#define MBOX_BASE      (0x3F00B880)
#define MBOX_READ      ((volatile uint32_t *)(MBOX_BASE + 0x00))
#define MBOX_STATUS    ((volatile uint32_t *)(MBOX_BASE + 0x18))
#define MBOX_WRITE     ((volatile uint32_t *)(MBOX_BASE + 0x20))
#define MBOX_FULL      0x80000000
#define MBOX_EMPTY     0x40000000

// --- mailbox_call ---
// mbox: must be 16-aligned (in .bss or static)
// ch: mailbox property (usually 8 for property tags)
int mailbox_call(uint8_t ch, volatile uint32_t *mbox) {
    uint32_t addr = ((uint32_t)(uintptr_t)mbox) & ~0xF; // 16-byte aligned
    while (*MBOX_STATUS & MBOX_FULL);
    *MBOX_WRITE = (addr) | (ch & 0xF);
    while (1) {
        while (*MBOX_STATUS & MBOX_EMPTY);
        if ((*MBOX_READ & 0xF) == ch)
            return mbox[1] == MBOX_RESPONSE;
    }
}

// --- fb_mailbox_init ---
// Fills out fb_base, fb_size, fb_pitch with real framebuffer data
int fb_mailbox_init(uint32_t width, uint32_t height, uint32_t depth,
                    uint32_t *fb_base, uint32_t *fb_size, uint32_t *fb_pitch) {
    static volatile uint32_t __attribute__((aligned(16))) mbox[35];

    mbox[0] = 35 * 4;      // buffer size in bytes
    mbox[1] = MBOX_REQUEST;

    mbox[2] = 0x48003;     // Tag: set phy wh
    mbox[3] = 8;
    mbox[4] = 8;
    mbox[5] = width;
    mbox[6] = height;

    mbox[7] = 0x48004;     // Tag: set virt wh
    mbox[8] = 8;
    mbox[9] = 8;
    mbox[10] = width;
    mbox[11] = height;

    mbox[12] = 0x48005;    // Tag: set depth
    mbox[13] = 4;
    mbox[14] = 4;
    mbox[15] = depth;

    mbox[16] = 0x48009;    // Tag: set pixel order (RGB)
    mbox[17] = 4;
    mbox[18] = 4;
    mbox[19] = 0;

    mbox[20] = 0x40001;    // Tag: alloc fb
    mbox[21] = 8;
    mbox[22] = 4;
    mbox[23] = 16;         // alignment: 16
    mbox[24] = 0;

    mbox[25] = 0x40008;    // Tag: get pitch
    mbox[26] = 4;
    mbox[27] = 4;
    mbox[28] = 0;

    mbox[29] = 0;          // End tag

    if(mailbox_call(MBOX_CH_PROP, (uint32_t*)mbox) && mbox[20+1] == 8 && mbox[20+2]) {
        *fb_base = mbox[23];
        *fb_size = mbox[24];
        *fb_pitch = mbox[28];
        return 1;
    }
    return 0;
}