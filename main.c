#include "LPC11xx.h"

uint8_t counter = 5;
void PIOINT3_IRQHandler()
{
		if((LPC_GPIO3 ->MIS & (1<<1)) == (1<<1))
		{
			counter ++;
			if(counter>10)
				counter=10;
			LPC_TMR32B1->MR1 =(SystemCoreClock /1000 /10)*counter;
			LPC_GPIO3 -> IC =(1<<1); 
		
		}
		if((LPC_GPIO3 ->MIS & (1<<2)) == (1<<2))
		{
			counter --;
			if(counter<1)
				counter=1;
			LPC_TMR32B1->MR1 =(SystemCoreClock /1000 /10)*counter;
			LPC_GPIO3 -> IC =(1<<2); 
		}

}
void KEYInit(void)
{
	
  LPC_GPIO3 ->DIR    &=~(1<<1);	
	
  LPC_GPIO3 ->DIR    &=~(1<<2);
	LPC_GPIO3 -> IE |=(1<<1);
	LPC_GPIO3 -> IE |=(1<<2);
	LPC_GPIO3 -> IS &=~(1<<1);
	LPC_GPIO3 -> IS &=~(1<<2);
	LPC_GPIO3 -> IEV &=~(1<<1);
	LPC_GPIO3 -> IEV &=~(1<<2);
	NVIC_EnableIRQ (EINT3_IRQn );	
}
void CT32B1_Init(uint32_t  interval)
{
	LPC_SYSCON ->SYSAHBCLKCTRL |=(1<<16); 
	LPC_IOCON->R_PIO1_2 &=~(0X07);
	LPC_IOCON->R_PIO1_2 |=0X03;
	LPC_SYSCON ->SYSAHBCLKCTRL  &=~(1<<16);
	LPC_SYSCON ->SYSAHBCLKCTRL |=(1<<10);
	LPC_TMR32B1 ->TCR =0X02;
	LPC_TMR32B1->PR = 0;
	LPC_TMR32B1->MCR  =0X02<<9;
	LPC_TMR32B1->PWMC  =0X02;
	LPC_TMR32B1->MR1 =(interval /10)*counter;
	LPC_TMR32B1->MR3 =interval ;
	LPC_TMR32B1->TCR = 0x01;
}
int main()
{
	KEYInit();
	
	CT32B1_Init(SystemCoreClock /1000);
	while(1)
	{
	 ;
	}
}
