#ifndef SPI_CONFIG_H_
#define SPI_CONFIG_H_

#define SPI_TIMEOUT              50000

/*
 * Node Mode Options:
 * - SPI_MASTER
 * - SPI_SLAVE
 */
#define SPI_NODE_MODE            SPI_MASTER

/*
 * Data Order Options:
 * - SPI_DATA_MSB_FIRST
 * - SPI_DATA_LSB_FIRST
 */
#define SPI_DATA_ORDER           SPI_DATA_MSB_FIRST

/*
 * Clock Polarity Options:
 * - SPI_CLOCK_IDLE_LOW
 * - SPI_CLOCK_IDLE_HIGH
 */
#define SPI_CLOCK_POLARITY       SPI_CLOCK_IDLE_LOW

/*
 * Clock Phase Options:
 * - SPI_PHASE_SAMPLE_FIRST
 * - SPI_PHASE_SETUP_FIRST
 */
#define SPI_CLOCK_PHASE          SPI_PHASE_SAMPLE_FIRST

/*
 * Prescaler Options (Used only in Master Mode):
 * - SPI_PRESCALER_4
 * - SPI_PRESCALER_16
 * - SPI_PRESCALER_64
 * - SPI_PRESCALER_128
 * - SPI_PRESCALER_2_DOUBLE
 * - SPI_PRESCALER_8_DOUBLE
 * - SPI_PRESCALER_32_DOUBLE
 * - SPI_PRESCALER_64_DOUBLE
 */
#define SPI_PRESCALER_SELECT     SPI_PRESCALER_16

#endif
