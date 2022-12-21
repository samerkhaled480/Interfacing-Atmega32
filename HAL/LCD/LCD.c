
#include "std_macros.h"
#include "LCD.h"


/*****************************************************************************
* Function Name: LCD_init
* Purpose      : Init lcd in 4 bit mode, clear lcd and turn off cursor
* Parameters   : void
* Return value : void
*****************************************************************************/
void LCD_init(void)
{
	LCD_INIT_PINS;
	
	LCD_write_command(0x2) ;  //select 4bit mode
	LCD_write_command(0x28);  //enable 5x7 for char.s
	LCD_write_command(0x08);  //display off , cursor off
	LCD_write_command(0x1) ;  //clear display and DDRAM content 
	LCD_write_command(0x6) ;  // start entry mode
	LCD_write_command(0xc) ;  // display on , cursor off
	
	_delay_ms(20);

}


/*****************************************************************************
* Function Name: LCD_write_command
* Purpose      : write command to lcd
* Parameters   : data: one of LCD commands
* Return value : void
*****************************************************************************/
void LCD_write_command(uint8 data)
{
	LCD_RS(0);
	
	LCD_D7(READ_BIT(data,7)); // Data bit7  = D7
	LCD_D6(READ_BIT(data,6)); // Data bit6  = D6
	LCD_D5(READ_BIT(data,5)); // Data bit5  = D5
	LCD_D4(READ_BIT(data,4)); // Data bit4  = D4
	LCD_EN(1);
	_delay_ms(1);
	LCD_EN(0);
	_delay_ms(1);
	
	LCD_D7(READ_BIT(data,3)); // Data bit3  = D7
	LCD_D6(READ_BIT(data,2)); // Data bit2  = D6
	LCD_D5(READ_BIT(data,1)); // Data bit1  = D5
	LCD_D4(READ_BIT(data,0)); // Data bit0  = D4
	LCD_EN(1);
	_delay_ms(1);
	LCD_EN(0);
	_delay_ms(1);
}


/*****************************************************************************
* Function Name: LCD_write_data
* Purpose      : write symbol on lcd
* Parameters   : data: Ascii value of specific symbol
* Return value : void
*****************************************************************************/
void LCD_write_data( uint8 data)
{
	LCD_RS(1);

	LCD_D7(READ_BIT(data,7)); // Data bit7  = D7
	LCD_D6(READ_BIT(data,6)); // Data bit6  = D6
	LCD_D5(READ_BIT(data,5)); // Data bit5  = D5
	LCD_D4(READ_BIT(data,4)); // Data bit4  = D4
	LCD_EN(1);
	_delay_ms(1);
	LCD_EN(0);
	_delay_ms(1);
	
	LCD_D7(READ_BIT(data,3)); // Data bit3  = D7
	LCD_D6(READ_BIT(data,2)); // Data bit2  = D6
	LCD_D5(READ_BIT(data,1)); // Data bit1  = D5
	LCD_D4(READ_BIT(data,0)); // Data bit0  = D4
	LCD_EN(1);
	_delay_ms(1);
	LCD_EN(0);
	_delay_ms(1);
}


/*****************************************************************************
* Function Name: LCD_write_string
* Purpose      : write full string on LCD
* Parameters   : data: string 
* Return value : void
*****************************************************************************/
void LCD_write_string(uint8 * data)
{
	uint8 i=0;
	while (data[i] != '\0')
	{
		LCD_write_data(data[i]);
		i++;
	}
}


/*****************************************************************************
* Function Name: LCD_write_num
* Purpose      : print a whole number up to 32bits
* Parameters   : number : number to print  
* Return value : void
*****************************************************************************/
void LCD_write_num(int32 number)
{
	uint8  temp_arr[10];
	int8   counter = 0;
		
	if(number == 0)
	{
		LCD_write_data(number+48);
		return;
	}
	if(number < 0)
	{
		number*=-1;
		LCD_write_data(45);
	}
	
	for(counter = 0 ; number != 0 ; counter++)
	{
		temp_arr[counter] = (number % 10) + 48;
		number /= 10; 
	}
	counter--;
	while (counter >= 0)
	{
		LCD_write_data( temp_arr[counter] );
		counter--;
	}
}