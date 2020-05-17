/*
 * Stop_watch.c
 *
 * Created: 17/05/2020 6:32:36 AM
 *  Author: M
 */ 


#include "LCD.h"
#include "Timer0.h"
uint8_t min=0  ;
uint8_t hour=0 ;
uint8_t sec=0  ;
int main(void)
{						
	CLRBIT(SREG,7);
	LCD_init();			// instructions for the user
	LCD_write_command(0x01);
	LCD_write_string("PD2->Pause");
	LCD_write_command(0xc0);
	LCD_write_string("PD3->Resume");
	_delay_ms(500);
	LCD_write_command(0x01);
	LCD_write_string("PD4->Reset");
	_delay_ms(500);
	SETBIT(MCUCR,ISC00);
	SETBIT(MCUCR,ISC01);
	SETBIT(GICR,INT0);
	SETBIT(MCUCR,ISC10);
	SETBIT(MCUCR,ISC11);
	SETBIT(GICR,INT1);
	sei();

	timer_normal_init();
	
	while(1)
	{
										
	while((GETBIT(PIND,4)==1)){}		// to reset the stop watch
	_delay_ms(15);
	sec=0;
	min=0;
	hour=0;
}

    }

ISR(TIMER0_OVF_vect){
static uint16_t count = 0;

count++;
	
if (count ==62){
	
	sec++;
	if (sec>=60){
		sec=0 ;
		min ++ ;
		if (min>=60){
			min=0;
			hour++;
				}
		}
	count=0;
	LCD_write_command(0x01);
	LCD_write_command(0x82);
	LCD_write_string("Stop Watch");
	LCD_write_command(0xc4);
	LCD_write_num(hour);
	LCD_write_char(':');
	LCD_write_num(min);
	LCD_write_char(':');
	LCD_write_num(sec);
	
}

}
ISR(INT0_vect){					//pause
	CLRBIT(TIMSK,TOIE0);
}
ISR(INT1_vect){					//resume
	SETBIT(TIMSK,TOIE0);
	}