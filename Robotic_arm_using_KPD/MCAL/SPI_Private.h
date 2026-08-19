#ifndef SPI_PRIVATE_H_
#define SPI_PRIVATE_H_

#define SPCR         *((volatile u8*)0x2D)
#define SPCR_SPIE    7
#define SPCR_SPE     6
#define SPCR_DORD    5
#define SPCR_MSTR    4
#define SPCR_CPOL    3
#define SPCR_CPHA    2
#define SPCR_SPR1    1
#define SPCR_SPR0    0

#define SPSR         *((volatile u8*)0x2E)
#define SPSR_SPIF    7
#define SPSR_WCOL    6
#define SPSR_SPI2X   0

#define SPDR         *((volatile u8*)0x2F)

#define SPI_MASTER               0
#define SPI_SLAVE                1

#define SPI_DATA_MSB_FIRST       0
#define SPI_DATA_LSB_FIRST       1

#define SPI_CLOCK_IDLE_LOW       0
#define SPI_CLOCK_IDLE_HIGH      1

#define SPI_PHASE_SAMPLE_FIRST   0
#define SPI_PHASE_SETUP_FIRST    1

#define SPI_PRESCALER_4          1
#define SPI_PRESCALER_16         2
#define SPI_PRESCALER_64         3
#define SPI_PRESCALER_128        4
#define SPI_PRESCALER_2_DOUBLE   5
#define SPI_PRESCALER_8_DOUBLE   6
#define SPI_PRESCALER_32_DOUBLE  7
#define SPI_PRESCALER_64_DOUBLE  8

#endif
