#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MATH.h"

#include "../MCAL/DIO_interface.h"

#include "SSD_config.h"
#include "SSD_private.h"
#include "SSD_interface.h"

void SSD_voidInit(void)
{
    DIO_voidSetPortDirection(SSD_PORT, DIO_OUT);
    
    #if SSD_TYPE == SSD_COMMON_CATHODE
        DIO_voidSetPortValue(SSD_PORT, DIO_LOW);
    #elif SSD_TYPE == SSD_COMMON_ANODE
        DIO_voidSetPortValue(SSD_PORT, DIO_HIGH);
    #endif
}

void SSD_voidDisplayNumber(u8 Copy_u8Number)
{
    if (Copy_u8Number <= 9)
    {
        #if SSD_TYPE == SSD_COMMON_CATHODE
            DIO_voidSetPortValue(SSD_PORT, SSD_u8Numbers[Copy_u8Number]);
            
        #elif SSD_TYPE == SSD_COMMON_ANODE
            DIO_voidSetPortValue(SSD_PORT, ~SSD_u8Numbers[Copy_u8Number]);
            
        #else
            #error "Invalid SSD_TYPE configuration"
        #endif
    }
}
