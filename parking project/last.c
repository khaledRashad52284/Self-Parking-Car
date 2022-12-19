#include <avr/io.h>
#include "LCD.h"
#define  F_CPU 1000000UL
#include <util/delay.h>
#include "std_macros.h"
#include "DIO.h"
int main(void)
{

	/***************************************----INITILIZATION----*********************************************
	 * *************************************                     ********************************************/

	LCD_vInit();

	  /* make Port C and D as output pins to run Dc motor and Ultrasonic  */
	DDRC &= ~(1<<PC2);
	DDRC &= ~(1<<PC3);




	DIO_vsetPINDir('D',0,1);
	DIO_vsetPINDir('D',1,1);
	DIO_vsetPINDir('D',2,1);
	DIO_vsetPINDir('D',3,1);
	DIO_vsetPINDir('D',4,1);
	

    DIO_vsetPINDir('C',0,1);
	DIO_vsetPINDir('C',1,1);
	PORTC &= ~(1<<PC0) & ~(1<<PC1);
	SET_BIT(PORTD,2);
	SET_BIT(PORTD,3);
	
	/*set up for servo motor will work on timer 1 take PWM signal to control its angle */

	DDRD |= (1<<PD5);	/* Make OC1A pin as output */

    TCNT1 = 0;		/* Set timer1 count zero */
	ICR1 = 2499;		/* Set TOP count for timer1 in ICR1 register */

		/* Set Fast PWM, TOP in ICR1, Clear OC1A on compare match, clk/64 */
	TCCR1A = (1<<WGM11)|(1<<COM1A1);
	TCCR1B = (1<<WGM12)|(1<<WGM13)|(1<<CS10)|(1<<CS11);
	OCR1A = 180;/* Set servo shaft at 0? position */


	/***************************************----PARKING MODE----*********************************************
	 * *************************************                     ********************************************/
	
	

    while(1)
	
    {	
	
    	/*check if 2 IR is OFF  then No obstacle and width is suitable for car the start Parking */

		if (  DIO_u8read('B',3)==1 && DIO_u8read('B',4)==1)
		{

			/*SHOW PARKING MODE ON SCREEN THEN BE READY AND MAKE SURE CAR DIRECTION IS STRAIGHT */

				LCD_clearscreen();
				LCD_vSend_string("parking mode");    //stop
				_delay_ms(500);
				CLR_BIT(PORTD,0);
				CLR_BIT(PORTC,1);
				CLR_BIT(PORTD,1);
				CLR_BIT(PORTC,0);
				_delay_ms(10000);

				/*  go forward straight  */

			    OCR1A = 180;/* Set servo shaft at 0? position */

				CLR_BIT(PORTD,1);
				CLR_BIT(PORTC,0);
				SET_BIT(PORTD,0);
				SET_BIT(PORTC,1);
				_delay_ms(10000);
						
				CLR_BIT(PORTD,0);
				CLR_BIT(PORTC,1);
				CLR_BIT(PORTD,1);
				CLR_BIT(PORTC,0);
				_delay_ms(10000);
						
				/* rotate 45 and go back*/

				OCR1A = 210;/* Set servo shaft at 45? position */
			   _delay_ms(10000);


				SET_BIT(PORTD,1);
				SET_BIT(PORTC,0);
				CLR_BIT(PORTD,0);
				CLR_BIT(PORTC,1);
				_delay_ms(20000);


				CLR_BIT(PORTD,0);
				CLR_BIT(PORTC,1);
				CLR_BIT(PORTD,1);
				CLR_BIT(PORTC,0);
				_delay_ms(10000);

				/*go back straight*/

				OCR1A = 180;/* Set servo shaft at 0? position */
				_delay_ms(10000);




				SET_BIT(PORTD,1);
				SET_BIT(PORTC,0);
				CLR_BIT(PORTD,0);
				CLR_BIT(PORTC,1);
				_delay_ms(5000);

				CLR_BIT(PORTD,0);
				CLR_BIT(PORTC,1);
				CLR_BIT(PORTD,1);
				CLR_BIT(PORTC,0);
				_delay_ms(10000);



				OCR1A = 160;/* Set servo shaft at -45? position  and go back */
				_delay_ms(10000);

				SET_BIT(PORTD,1);
				SET_BIT(PORTC,0);
				CLR_BIT(PORTD,0);
				CLR_BIT(PORTC,1);
				_delay_ms(5000);

				CLR_BIT(PORTD,0);
				CLR_BIT(PORTC,1);
				CLR_BIT(PORTD,1);
				CLR_BIT(PORTC,0);
				_delay_ms(10000);

				OCR1A = 190;/* Set servo shaft at 0? position  and go forward*/
				_delay_ms(10000);


				CLR_BIT(PORTD,1);
				CLR_BIT(PORTC,0);
				SET_BIT(PORTD,0);
				SET_BIT(PORTC,1);
				_delay_ms(3000);








	/***************************************----SLEEPING MODE----********************************************
	 ***************************************                     ********************************************/




			while(1){


				OCR1A = 180;/* Set servo shaft at 45? position */
				CLR_BIT(PORTD,0);
				CLR_BIT(PORTC,1);
				CLR_BIT(PORTD,1);
				CLR_BIT(PORTC,0);
				_delay_ms(10000);

				LCD_clearscreen();
				LCD_vSend_string("parked....");    //stop
				_delay_ms(500);


			}


													
						}						
									
						
		/***************************************---- SEARCH FOR SUITABLE DIMENSION ----**************************
		 ***************************************                                       **************************/

		
		else
		{

			/*STILL WALK STRAIGHT TILL FIND A SUITABLE DIMENSION FOR PARKING */

		LCD_clearscreen();
		LCD_vSend_string("GOOOOOO");
		_delay_ms(500);
		OCR1A = 180;/* Set servo shaft at 0? position and go straight */
		_delay_ms(5000);
		CLR_BIT(PORTD,1);
		CLR_BIT(PORTC,0);
		SET_BIT(PORTD,0);
		SET_BIT(PORTC,1);
		}		
	}
}

