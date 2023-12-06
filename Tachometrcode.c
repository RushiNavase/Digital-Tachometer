#include <stm32f10x.h>
#include <stdio.h>
void delay(int val);
int lcd_cmd(char cmd){
	GPIOA->ODR=0x00F0& cmd;
	GPIOB->ODR=0x02;//RS=0,EN=1
	delay(10);
	GPIOB->ODR=0x00;//RS=0,EN=0
	GPIOA->ODR=(0x00F0& (cmd<<4));
	GPIOB->ODR=0x02;//RS=0,EN=1
	 delay(10);
	GPIOB->ODR=0x00;//RS=0,EN=0
}
int lcd_data(char data){
	GPIOA->ODR=0x00F0& data;
	GPIOB->ODR=0x03;//RS=1,EN=1
	delay(10);
	GPIOB->ODR=0x01;//RS=1,EN=0
	GPIOA->ODR=(0x00F0& (data<<4));
	GPIOB->ODR=0x03;//RS=1,EN=1
	 delay(10);
	GPIOB->ODR=0x01;//RS=1,EN=0
}
void lcd_string(char *s){
	  while(*s!='\0'){
			lcd_data(*s++);
		}
	}
int lcd_init(){
	lcd_cmd(0x02);
	lcd_cmd(0x28);
	lcd_cmd(0x01);
	lcd_cmd(0x0F);
}
void delay(int val){
	for(int i=0;i<=val;i++){
	SysTick->LOAD=72000;
	SysTick->VAL=0;
	SysTick->CTRL=0x05;
	while((SysTick->CTRL & 0x10000)==0){}
	SysTick->CTRL=0x0000;
	}
	
}
int main(){
	int t1,t2,Flag=0;
	float period,freq,rpm;
	char RPM[16];
	RCC->APB2ENR=0x0C;// GPIO clock enable 
	RCC->APB1ENR=0x01;//TIM2 clock enable
	GPIOA->CRL&=0x0000;
	GPIOA->CRL|=0x33330008;//PA0(CH1) input with pull up
	GPIOA->ODR =0x01;
	GPIOB->CRL=0x00000033;
	TIM2->CCMR1|=0x01;//CC1S=01(input capture at ch1)
	TIM2->CCER=0x01;//CC1P=0,CC1E=1
	TIM2->ARR=50000;
	TIM2->PSC=720;//(72Mhz/720=100000 and 1/100000=10us hence timer will overflow after=10us*50000=0.5sec)
	TIM2->SR=0x0000;
	TIM2->CR1=0x01;//Timer CEN=1 i.e counter enabled
	lcd_init();
	while(1){
		int t1=0,t2=0,Ov=0,Flag=0;
	if(Flag==0){
	while((TIM2->SR &(1<<1))==0);
		t1=TIM2->CCR1;//Read the captured value
		TIM2->SR&=~0xFFFFFFFF;
		Flag=1;  
	}
		if(Flag==1){
		while((TIM2->SR &(1<<1))==0){
			if((TIM2->SR & (1<<0))==1){
			Ov++;
			TIM2->SR&=0x00;	
			}
		}
		t2=TIM2->CCR1;//Read the captured value
		delay(230);
		TIM2->SR&=0x00000000;
		lcd_cmd(0x01);//clear screen
		//if timer  do not overflow
		if(Ov==0){
		period=(float)(0.00001*(t2-t1));
		freq=(1/period);
		rpm=freq*60;//number of rotation in a minute
		lcd_cmd(0x80);
		lcd_string("Rotation per Min");
		sprintf(RPM,"%.4f",rpm);
		lcd_cmd(0xC0);
		lcd_string(RPM);
				}
		//if timer overflow 
		else{
		period=(float)(0.00001*((t2+(50000*Ov))-t1));	
		freq=(1/period);
		rpm=freq*60;//number of rotation in a minute
		lcd_cmd(0x80);
		lcd_string("Rotation per Min");
		sprintf(RPM,"%.4f",rpm);
		lcd_cmd(0xC0);
		lcd_string(RPM);
				}
		Flag=0;
		}
	
	}
	
}
