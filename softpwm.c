#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

void Init(void);
void PWM_service (void);
void all_fade_sync(void);
void running_fade(void);

uint8_t duty_cycle[8] = {0, 0, 0, 0, 0, 0, 0, 0 };

uint8_t flag[8] = {0, 0, 0, 0, 0, 0, 0, 0 };

uint8_t current_up = 0;
uint8_t current_down = 0;


volatile uint8_t count = 0;
uint8_t all_fade_count = 0;

uint8_t running_fade_setup = 0;
uint8_t running_fade_count = 0;


int main(void){ 

	Init();

    while(1){
	
	PWM_service();

	
	/*------Uncomment the desired pattern--------*/
	//all_fade_sync();
	running_fade();
	/*-------------------------------------------*/
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


if(duty_cycle[0] >= count){PORTD |= (1<<PD0);}
	else{PORTD &= ~(1<<PD0);}
	
if(duty_cycle[1] >= count){PORTD |= (1<<PD1);}
	else{PORTD &= ~(1<<PD1);}
	
if(duty_cycle[2] >= count){PORTD |= (1<<PD2);}
	else{PORTD &= ~(1<<PD2);}	
	
if(duty_cycle[3] >= count){PORTD |= (1<<PD3);}
	else{PORTD &= ~(1<<PD3);}
	
if(duty_cycle[4] >= count){PORTD |= (1<<PD4);}
	else{PORTD &= ~(1<<PD4);}
	
if(duty_cycle[5] >= count){PORTD |= (1<<PD5);}
	else{PORTD &= ~(1<<PD5);}
	
if(duty_cycle[6] >= count){PORTD |= (1<<PD6);}
	else{PORTD &= ~(1<<PD6);}
	
if(duty_cycle[7] >= count){PORTD |= (1<<PD7);}
	else{PORTD &= ~(1<<PD7);}

}

 
void all_fade_sync(){
if(count==254){all_fade_count++;}

		if(all_fade_count==5){
			if(flag[0]==1){duty_cycle[0]++;}
				else{duty_cycle[0]--;}
			if(duty_cycle[0]==225){flag[0]=0;}
			if(duty_cycle[0]==25){flag[0]=1;}
			
			if(flag[1]==1){duty_cycle[1]++;}
				else{duty_cycle[1]--;}
			if(duty_cycle[1]==225){flag[1]=0;}
			if(duty_cycle[1]==25){flag[1]=1;}
			
			if(flag[2]==1){duty_cycle[2]++;}
				else{duty_cycle[2]--;}
			if(duty_cycle[2]==225){flag[2]=0;}
			if(duty_cycle[2]==25){flag[2]=1;}
			
		all_fade_count=0;	
	}
}


void running_fade(){
	
	if(running_fade_setup==0){duty_cycle[0]=200;current_down=0;current_up=1;running_fade_setup=1;}
	
	
	if(count==253){running_fade_count++;count=0;}
	
	
	
	if(running_fade_count==1){
		duty_cycle[current_up]++;
		duty_cycle[current_down]--;
		
		if(duty_cycle[current_up] == 200){current_up++; current_down++;  }
		if(current_up == 3){current_up = 0;}//duty_cycle[0]=0;duty_cycle[1]=0;duty_cycle[2]=0;current_down=3;}
		if(current_down == 3){current_down = 0;}
		running_fade_count=0;
	
	}
	
	
}



ISR(TIMER0_OVF_vect){

    count++;

 
}

