#include"GLCD.h"


//Decimal Numbers in 3 X 5 Format 
static const char Dec_FontLookup [][5] =
{
    {0x3E, 0x51, 0x49, 0x45, 0x3E},// 0 
    {0x00, 0x42, 0x7F, 0x40, 0x00},// 1 
    {0x42, 0x61, 0x51, 0x49, 0x46},// 2 
    {0x21, 0x41, 0x45, 0x4B, 0x31},// 3 
    {0x18, 0x14, 0x12, 0x7F, 0x10},// 4 
    {0x27, 0x45, 0x45, 0x45, 0x39},// 5 
    {0x3C, 0x4A, 0x49, 0x49, 0x30},// 6 
    {0x01, 0x71, 0x09, 0x05, 0x03},// 7 
    {0x36, 0x49, 0x49, 0x49, 0x36},// 8 
    {0x06, 0x49, 0x49, 0x29, 0x1E},// 9 
};


void GLCD_Init()
{
    GLCD_CONTROL_PORT_DIR = 0xff;
    GLCD_DATA_PORT_DIR    = 0xff;

    GLCD_DATA_PORT = 0xff;
    
    SET_BIT(GLCD_CONTROL_PORT,RS);
    SET_BIT(GLCD_CONTROL_PORT,EN);
    SET_BIT(GLCD_CONTROL_PORT,RST);

    CLR_BIT(GLCD_CONTROL_PORT,RST);
    _delay_us(10);
    SET_BIT(GLCD_CONTROL_PORT,RST);
    _delay_us(10);

    CLR_BIT(GLCD_CONTROL_PORT,RS);
    
    SET_BIT(GLCD_CONTROL_PORT,CS1);
    SET_BIT(GLCD_CONTROL_PORT,CS2);

    GLCD_CmdWrite(0x3F);
    GLCD_CmdWrite(0xC0);

    CLR_BIT(GLCD_CONTROL_PORT,CS1);
    CLR_BIT(GLCD_CONTROL_PORT,CS2);

    SET_BIT(GLCD_CONTROL_PORT,EN);
    
}

void GLCD_SelectChip(uint8 selection) // 0x00 or 0x0f or 0xf0 or 0xff
{
    switch (selection)
    {
        case 0x00:
        {
            CLR_BIT(GLCD_CONTROL_PORT,CS1);
            CLR_BIT(GLCD_CONTROL_PORT,CS2);
        }break;
        case 0xf0:
        {
            SET_BIT(GLCD_CONTROL_PORT,CS1);
            CLR_BIT(GLCD_CONTROL_PORT,CS2);

        }break;
        case 0x0f:
        { 
            CLR_BIT(GLCD_CONTROL_PORT,CS1);
            SET_BIT(GLCD_CONTROL_PORT,CS2);

        }break;
        case 0xff:
        { 
            SET_BIT(GLCD_CONTROL_PORT,CS1);
            SET_BIT(GLCD_CONTROL_PORT,CS2);

        }break;
    }
}

void GLCD_SelectPage(uint8 selection)//from 0 to 7
{
    switch (selection)
    {
    case 0: GLCD_CmdWrite(0xB8);break;
    case 1: GLCD_CmdWrite(0xB9);break;
    case 2: GLCD_CmdWrite(0xBA);break;
    case 3: GLCD_CmdWrite(0xBB);break;
    case 4: GLCD_CmdWrite(0xBC);break;
    case 5: GLCD_CmdWrite(0xBD);break;
    case 6: GLCD_CmdWrite(0xBE);break;
    case 7: GLCD_CmdWrite(0xBF);break;
    default:
        break;
    }
}

void GLCD_GoToXY(uint8 x , uint8 y)// x 0-127 , y 0-7
{
    if( (y < 8) && (y >= 0) && (x < 128) && (x >=0) )
    {
        if(x<64)
        {
            GLCD_SelectChip(0xf0);
            GLCD_SelectPage(y);
            GLCD_CmdWrite( ( x | (1<<6) ) );
        }
        else
        {
            x-=64;
            GLCD_SelectChip(0x0f);
            GLCD_SelectPage(y);
            GLCD_CmdWrite( ( x | (1<<6) ) );
        }
    }
}

void GLCD_CmdWrite(uint8 cmd)
{
    GLCD_DATA_PORT = cmd;         //Send the command nibble
   
    CLR_BIT(GLCD_CONTROL_PORT,RS); // Send LOW pulse on RS pin for selecting command register 
   
    CLR_BIT(GLCD_CONTROL_PORT,EN);
    _delay_us(100);
    SET_BIT(GLCD_CONTROL_PORT,EN); // Generate a High-to-low pulse on EN pin
   
  
    _delay_us(10);
}

void GLCD_DataWrite(uint8 data)
{
    GLCD_DATA_PORT = data;         //Send the data on DataBus nibble
    
    SET_BIT(GLCD_CONTROL_PORT,RS); // Send HIGH pulse on RS pin for selecting data register 
   
    CLR_BIT(GLCD_CONTROL_PORT,EN);
    _delay_us(100);
    SET_BIT(GLCD_CONTROL_PORT,EN); // Generate a High-to-low pulse on EN pin
   
    
    _delay_us(10);
}

void GLCD_DisplayChar(uint8 *ptr_array)
{
    uint8 i;
    for( i=0 ; i<6 ; i++ ) // 5x7 font, 5 chars + 1 blankspace
    {
        GLCD_DataWrite(ptr_array[i]);
    }  
}

void GLCD_DispalyString(uint8 **ptr_arry ,uint8 arr_size , uint8 x , uint8 y)
{
    uint8 i , j;
    uint8 * temp = 0;

	GLCD_GoToXY(x,y);

    for( i=0 ; i < arr_size ; i++ ) 
    {   
       
        if( (x+(i*6)) >= 127 || ( x+6 >= 127) )
        {
            GLCD_GoToXY(0,y+1);
        }
        else if( x+6 >= 64 && x < 64 )
        {
            GLCD_GoToXY(64,y);
            x=64;
        }

        temp = (uint8*) *(ptr_arry+i);

		for( j=0 ; j<6 ; j++)
        {   
            x++;
            GLCD_DataWrite(*(temp+j));
        }
    }
}


void GLCD_DispalyNum(uint32 num, uint8 x , uint8 y)
{
    
    int8 counter ;

    uint8 ValueToPrint = 0;

	GLCD_GoToXY(x,y);
    if(num == 0)
    {
        for( counter = 0 ; counter < 5 ; counter++ ) 
        {   
            if( (x+( counter *6)) >= 127 || ( x+6 >= 127) )
            {
                GLCD_GoToXY(0,y+1);
            }
            else if( x+6 >= 64 && x < 64 )
            {
                GLCD_GoToXY(64,y);
                x=64;
            }
            ValueToPrint = Dec_FontLookup[0][ counter ];
            GLCD_DataWrite(ValueToPrint);   
        }
    }
    else
    {
        uint8_t  temp_arr[10];
        
        for(counter = 0 ; num != 0 ; counter++)
        {
            temp_arr[counter] = (num % 10);
            num /= 10; 
        }

        counter--;

        while (counter >= 0)
        {
            for( uint8 i=0 ; i < 5 ; i++ ) 
            {   
                if( (x+(i*6)) >= 127 || ( x+6 >= 127) )
                {
                    GLCD_GoToXY( 0 , y + 1);
                }
                else if( x+6 >= 64 && x < 64 )
                {
                    GLCD_GoToXY( 64 , y);
                    x = 64;
                }
                ValueToPrint = Dec_FontLookup[  temp_arr[counter] ][i];
                GLCD_DataWrite(ValueToPrint);   
            }

            counter--;
        }
        
    }
}


