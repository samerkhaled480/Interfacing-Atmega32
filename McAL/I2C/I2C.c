#include "I2C.h"

#define TWBR_val ((((F_CPU / F_SCL) / Prescaler) - 16 ) / 2)


void I2C_Master_init(void)
{
	TWBR = TWBR_val; // for 400K scl and 16Mhz freq uc
}

uint8 I2C_Master_start(uint8 slave_address)
{
	uint8 status;		
	/* Enable TWI, generate START */
    TWCR = (1<<TWSTA) | (1<<TWEN) | (1<<TWINT); 

	/* Wait until TWI finish its current job */
    while( READ_BIT(TWCR,TWINT) == 0 );					

	/* Read TWI status register */
    status = TWSR & 0xF8;		

	/* Check weather START transmitted or not? */
    if(status != 0x08)		
    return 0;			/* Return 0 to indicate start condition fail */

	/* Write SLA+W in TWI data register */
    TWDR = slave_address<<1;		

	/* Enable TWI & clear interrupt flag */
    TWCR = (1<<TWEN) | (1<<TWINT);

    while( READ_BIT(TWCR,TWINT) == 0 );	/* Wait until TWI finish its current job */

    status = TWSR & 0xF8;		/* Read TWI status register */

    if(status == 0x18)		/* Check for SLA+W transmitted &ack received */
    return 1;			/* Return 1 to indicate ack received */
    if(status == 0x20)		/* Check for SLA+W transmitted &nack received */
    return 2;			/* Return 2 to indicate nack received */
    else
    return 3;			/* Else return 3 to indicate SLA+W failed */
}

uint8 I2C_Master_Repeated_Start(uint8 slave_address)
{
    uint8_t status;		/* Declare variable */

    TWCR = (1<<TWSTA) | (1<<TWEN) | (1<<TWINT); /* Enable TWI, generate start */

    while( READ_BIT(TWCR,TWINT) == 0 );			/* Wait until TWI finish its current job */

    status = TWSR & 0xF8;		/* Read TWI status register */
    if( status != 0x10 )		/* Check for repeated start transmitted */
    return 0;					/* Return 0 for repeated start condition fail */
	
    TWDR = slave_address;				/* Write SLA+R in TWI data register */
    TWCR = (1<<TWEN) | (1<<TWINT);	/* Enable TWI and clear interrupt flag */

    while( READ_BIT(TWCR,TWINT) == 0 );	/* Wait until TWI finish its current job */

    status=TWSR&0xF8;		/* Read TWI status register */

    if(status == 0x40)		/* Check for SLA+R transmitted &ack received */
    return 1;				/* Return 1 to indicate ack received */
    if(status == 0x48)		/* Check for SLA+R transmitted &nack received */
    return 2;				/* Return 2 to indicate nack received */
    else
    return 3;				/* Else return 3 to indicate SLA+W failed */ 
}

uint8 I2C_Master_Write(uint8 data)	
{
    uint8 status = 0;		

    TWDR=data;

	/* Enable TWI and clear interrupt flag */
    TWCR = (1<<TWEN) | (1<<TWINT);	

	/* Wait until TWI finish its current job */
    while(  READ_BIT(TWCR,TWINT) == 0  );	

    status = TWSR & 0xF8;		/* Read TWI status register */

    if(status == 0x28)			/* Check for data transmitted &ack received */
    return 0;					/* Return 0 to indicate ack received */
    if(status == 0x30)			/* Check for data transmitted &nack received */
    return 1;					/* Return 1 to indicate nack received */
    else
    return 2;					/* Else return 2 for data transmission failure */
}

uint8 I2C_Master_Read_Ack(void)		
{
	/* Enable TWI, generation of ack */
    TWCR = (1<<TWEN) | (1<<TWINT) | (1<<TWEA); 

	/* Wait until TWI finish its current job */
    while(  READ_BIT(TWCR,TWINT) == 0  );	

    return TWDR;			
}

uint8 I2C_Master_Read_Nack(void)		
{
	/* Enable TWI and clear interrupt flag */
    TWCR = (1<<TWEN) | (1<<TWINT);	

	/* Wait until TWI finish its current job */
    while(  READ_BIT(TWCR,TWINT) == 0  );	

	
    return TWDR;		
}

void I2C_Master_Stop(void)	
{
	/* Enable TWI, generate stop */
    TWCR = (1<<TWSTO) | (1<<TWINT) | (1<<TWEN); 

	/* Wait until stop condition execution */
    //while(  READ_BIT(TWCR,TWINT) == 0  );	
}

void I2C_Slave_Init(uint8 slave_address)
{
	/* Assign Address in TWI address register */
    TWAR = slave_address << 1;   
}

int8 I2C_Slave_Listen(void)
{
    uint8_t status;	

	/* Enable TWI, Enable ack generation */
    TWCR = (1<<TWEN) | (1<<TWEA) | (1<<TWINT);		

    while(  READ_BIT(TWCR,TWINT) == 0  );	/* Wait to be addressed */

    status = TWSR ;//& 0xF8;		/* Read TWI status register */

    if(status == 0x60 || status == 0x68)	/* Own SLA+W received &ack returned */
    return 0;							/* Return 0 to indicate ack returned */

    if(status==0xA8 || status==0xB0)	/* Own SLA+R received &ack returned */
    return 1;							/* Return 0 to indicate ack returned */

    if(status==0x70 || status==0x78)	
    return 2;							

    return 3;                           

}

int8 I2C_Slave_Transmit(uint8 data)
{
    uint8 status;

    TWDR = data;			

	/* Enable TWI & clear interrupt flag */
    TWCR = (1<<TWEN) | (1<<TWINT) | (1<<TWEA);

    while(  READ_BIT(TWCR,TWINT) == 0  );	/* Wait until TWI finish its current job */

    status = TWSR & 0xF8;	/* Read TWI status register */

    if(status==0xA0)		/* Check for STOP/REPEATED START received */
	{
		TWCR|=(1<<TWINT);	/* Clear interrupt flag & return -1 */
		return -1;
	}

    if(status==0xB8)		/* Check for data transmitted &ack received */
    	return 0;			/* If yes then return 0 */

    if(status==0xC0)		/* Check for data transmitted &nack received */
    {
		TWCR|=(1<<TWINT);	/* Clear interrupt flag & return -2 */
		return -2;
    }

    if(status==0xC8)		/* Last byte transmitted with ack received */
    	return -3;			/* If yes then return -3 */

    else					/* else return -4 */
   		return -4;
}

uint8 I2C_Slave_Receive(void)
{
    uint8 status;		
	
    TWCR = (1<<TWEN) | (1<<TWEA) | (1<<TWINT); /* Enable TWI & generation of ack */

    while(  READ_BIT(TWCR,TWINT) == 0  );	/* Wait until TWI finish its current job */

    status = TWSR & 0xF8;		

    if(status==0x80||status==0x90)	/* Check for data received &ack returned */
    return TWDR;					/* If yes then return received data */

	/* Check for data received, nack returned & switched to not addressed slave mode */
    if(status == 0x88 || status == 0x98)
		return TWDR;		/* If yes then return received data */

    if(status==0xA0)		/* Check wether STOP/REPEATED START */
    {
		TWCR |= (1<<TWINT);	/* Clear interrupt flag & return -1 */
		return -1;
    }
    else
    	return -2;			/* Else return -2 */
}
