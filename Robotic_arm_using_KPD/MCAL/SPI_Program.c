#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MATH.h"

#include "../MCAL/DIO_interface.h"

#include "SPI_interface.h"
#include "SPI_private.h"
#include "SPI_config.h"

void SPI_voidInit(void)
{
	u8 Local_u8SPCRValue = 0;

#if SPI_DATA_ORDER == SPI_DATA_LSB_FIRST
	SET_BIT(Local_u8SPCRValue, SPCR_DORD);
#elif SPI_DATA_ORDER == SPI_DATA_MSB_FIRST
	CLR_BIT(Local_u8SPCRValue, SPCR_DORD);
#endif

#if SPI_CLOCK_POLARITY == SPI_CLOCK_IDLE_HIGH
	SET_BIT(Local_u8SPCRValue, SPCR_CPOL);
#elif SPI_CLOCK_POLARITY == SPI_CLOCK_IDLE_LOW
	CLR_BIT(Local_u8SPCRValue, SPCR_CPOL);
#endif

#if SPI_CLOCK_PHASE == SPI_PHASE_SETUP_FIRST
	SET_BIT(Local_u8SPCRValue, SPCR_CPHA);
#elif SPI_CLOCK_PHASE == SPI_PHASE_SAMPLE_FIRST
	CLR_BIT(Local_u8SPCRValue, SPCR_CPHA);
#endif

#if SPI_NODE_MODE == SPI_MASTER
	DIO_voidSetPinDirection(DIO_PORTB, DIO_PIN4, DIO_OUT);
	DIO_voidSetPinDirection(DIO_PORTB, DIO_PIN5, DIO_OUT);
	DIO_voidSetPinDirection(DIO_PORTB, DIO_PIN6, DIO_IN);
	DIO_voidSetPinDirection(DIO_PORTB, DIO_PIN7, DIO_OUT);
    
	DIO_voidSetPinValue(DIO_PORTB, DIO_PIN4, DIO_HIGH);

	SET_BIT(Local_u8SPCRValue, SPCR_MSTR);

	#if SPI_PRESCALER_SELECT == SPI_PRESCALER_4
		CLR_BIT(Local_u8SPCRValue, SPCR_SPR0);
		CLR_BIT(Local_u8SPCRValue, SPCR_SPR1);
		CLR_BIT(SPSR, SPSR_SPI2X);
	#elif SPI_PRESCALER_SELECT == SPI_PRESCALER_16
		SET_BIT(Local_u8SPCRValue, SPCR_SPR0);
		CLR_BIT(Local_u8SPCRValue, SPCR_SPR1);
		CLR_BIT(SPSR, SPSR_SPI2X);
	#elif SPI_PRESCALER_SELECT == SPI_PRESCALER_64
		CLR_BIT(Local_u8SPCRValue, SPCR_SPR0);
		SET_BIT(Local_u8SPCRValue, SPCR_SPR1);
		CLR_BIT(SPSR, SPSR_SPI2X);
	#elif SPI_PRESCALER_SELECT == SPI_PRESCALER_128
		SET_BIT(Local_u8SPCRValue, SPCR_SPR0);
		SET_BIT(Local_u8SPCRValue, SPCR_SPR1);
		CLR_BIT(SPSR, SPSR_SPI2X);
	#elif SPI_PRESCALER_SELECT == SPI_PRESCALER_2_DOUBLE
		CLR_BIT(Local_u8SPCRValue, SPCR_SPR0);
		CLR_BIT(Local_u8SPCRValue, SPCR_SPR1);
		SET_BIT(SPSR, SPSR_SPI2X);
	#elif SPI_PRESCALER_SELECT == SPI_PRESCALER_8_DOUBLE
		SET_BIT(Local_u8SPCRValue, SPCR_SPR0);
		CLR_BIT(Local_u8SPCRValue, SPCR_SPR1);
		SET_BIT(SPSR, SPSR_SPI2X);
	#elif SPI_PRESCALER_SELECT == SPI_PRESCALER_32_DOUBLE
		CLR_BIT(Local_u8SPCRValue, SPCR_SPR0);
		SET_BIT(Local_u8SPCRValue, SPCR_SPR1);
		SET_BIT(SPSR, SPSR_SPI2X);
	#elif SPI_PRESCALER_SELECT == SPI_PRESCALER_64_DOUBLE
		SET_BIT(Local_u8SPCRValue, SPCR_SPR0);
		SET_BIT(Local_u8SPCRValue, SPCR_SPR1);
		SET_BIT(SPSR, SPSR_SPI2X);
	#endif

#elif SPI_NODE_MODE == SPI_SLAVE
	DIO_voidSetPinDirection(DIO_PORTB, DIO_PIN4, DIO_IN);
	DIO_voidSetPinDirection(DIO_PORTB, DIO_PIN5, DIO_IN);
	DIO_voidSetPinDirection(DIO_PORTB, DIO_PIN6, DIO_OUT);
	DIO_voidSetPinDirection(DIO_PORTB, DIO_PIN7, DIO_IN);

	CLR_BIT(Local_u8SPCRValue, SPCR_MSTR);
#endif

	SET_BIT(Local_u8SPCRValue, SPCR_SPE);
	SPCR = Local_u8SPCRValue;
}

u8 SPI_u8Transceive(u8 Copy_u8Data)
{
	u16 Local_u16TimeoutCounter = 0;
	
#if SPI_NODE_MODE == SPI_MASTER
	DIO_voidSetPinValue(DIO_PORTB, DIO_PIN4, DIO_LOW);
#endif

	SPDR = Copy_u8Data;
	
	while((GET_BIT(SPSR, SPSR_SPIF) == 0) && (Local_u16TimeoutCounter < SPI_TIMEOUT))
	{
		Local_u16TimeoutCounter++;
	}
	
#if SPI_NODE_MODE == SPI_MASTER
	DIO_voidSetPinValue(DIO_PORTB, DIO_PIN4, DIO_HIGH);
#endif

	return SPDR;
}
