#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

void Init(void);
void PWM_service (void);
void fade(void);

 uint8_t PD0_duty = 255;
 uint8_t PD1_duty = 125;
 uint8_t PD2_duty = 5;
 uint8_t PD3_duty = 0;
 uint8_t PD4_duty = 0;
 uint8_t PD5_duty = 0;
 uint8_t PD6_duty = 0;
 uint8_t PD7_duty = 0;

 uint8_t flag[8] = {1, 0, 0, 0, 0, 0, 0, 0 };

volatile uint8_t count = 0;
uint8_t count2 = 0;


int main(void){ 

	Init();

    while(1){
	
	PWM_service();

	fade();
	
	}
    
}

void Init(){


    TCCR0B = (1<<CS00); //Set timer0 prescaler to clk =  16ms between interrupts
    DDRD = 0b11111111; //All outputs  DDRB = PORTB_MASK;


    TIFR0 = (1 << TOV0);           // clear interrupt flag
    TIMSK0 = (1 << TOIE0);         // enable overflow interrupt. Timer0 is 8 bit.
    TCCR0B = (1 << CS00);         // start timer, no prescale

    sei();         // enable interrupts
	
	}
	
void PWM_service(){


if(PD0_duty >= count){PORTD |= (1<<PD0);}
	else{PORTD &= ~(1<<PD0);}
	
if(PD1_duty >= count){PORTD |= (1<<PD1);}
	else{PORTD &= ~(1<<PD1);}
	
if(PD2_duty >= count){PORTD |= (1<<PD2);}
	else{PORTD &= ~(1<<PD2);}	
	
if(PD3_duty >= count){PORTD |= (1<<PD3);}
	else{PORTD &= ~(1<<PD3);}
	
if(PD4_duty >= count){PORTD |= (1<<PD4);}
	else{PORTD &= ~(1<<PD4);}
	
if(PD5_duty >= count){PORTD |= (1<<PD5);}
	else{PORTD &= ~(1<<PD5);}
	
if(PD6_duty >= count){PORTD |= (1<<PD6);}
	else{PORTD &= ~(1<<PD6);}
	
if(PD7_duty >= count){PORTD |= (1<<PD7);}
	else{PORTD &= ~(1<<PD7);}

}

 
void fade(){
if(count==254){count2++;}

		if(count2==2){
		if(flag[0]==1){PD0_duty++;}
			else{PD0_duty--;}
		if(PD0_duty==255){flag[0]=0;}
		if(PD0_duty==50){flag[0]=1;}
		
		if(flag[1]==1){PD1_duty++;}
			else{PD1_duty--;}
		if(PD1_duty==255){flag[1]=0;}
		if(PD1_duty==50){flag[1]=1;}
		
		if(flag[2]==1){PD2_duty++;}
			else{PD2_duty--;}
		if(PD2_duty==255){flag[2]=0;}
		if(PD2_duty==50){flag[2]=1;}
		
		count2=0;	
	}
}


ISR(TIMER0_OVF_vect){

    count++;
 
}

