#ifndef BIT_MATH_H_
#define BIT_MATH_H_

/* Basic Bit Operations */
#define SET_BIT(REG, BIT_NUM)       ((REG) |=  (1UL << (BIT_NUM)))
#define CLR_BIT(REG, BIT_NUM)       ((REG) &= ~(1UL << (BIT_NUM)))
#define TOG_BIT(REG, BIT_NUM)       ((REG) ^=  (1UL << (BIT_NUM)))
#define GET_BIT(REG, BIT_NUM)       (((REG) >> (BIT_NUM)) & 1UL)

/* Advanced Bit Operations */
#define ASSIGN_BIT(REG, BIT_NUM, VAL) ((VAL) ? SET_BIT(REG, BIT_NUM) : CLR_BIT(REG, BIT_NUM))
#define WRITE_BIT(REG, BIT_NUM, VAL)  ((REG) = (((REG) & ~(1UL << (BIT_NUM))) | ((VAL) << (BIT_NUM))))
#define ROTATE_RIGHT(REG, BIT_NUM)    ((REG) = ((REG) >> (BIT_NUM)) | ((REG) << (32 - (BIT_NUM))))
#define ROTATE_LEFT(REG, BIT_NUM)     ((REG) = ((REG) << (BIT_NUM)) | ((REG) >> (32 - (BIT_NUM))))

/* Multi-Bit Masking Operations */
#define SET_REG(REG)                ((REG) = 0xFF)
#define CLR_REG(REG)                ((REG) = 0x00)
#define TOG_REG(REG)                ((REG) ^= 0xFF)
#define WRITE_REG(REG, VAL)         ((REG) = (VAL))

#endif