#ifndef SSD_PRIVATE_H
#define SSD_PRIVATE_H

#define SSD_COMMON_CATHODE    0
#define SSD_COMMON_ANODE      1

/* 
 * Hex values for numbers 0 to 9 on a Common Cathode 7-Segment
 * (For Common Anode, we will just invert these values in the .c file)
 */
static const u8 SSD_u8Numbers[10] = {
    0x3F, /* 0 */
    0x06, /* 1 */
    0x5B, /* 2 */
    0x4F, /* 3 */
    0x66, /* 4 */
    0x6D, /* 5 */
    0x7D, /* 6 */
    0x07, /* 7 */
    0x7F, /* 8 */
    0x6F  /* 9 */
};

#endif