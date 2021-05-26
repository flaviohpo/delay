#ifndef __DELAY_H_
#define __DELAY_H_

/* usuario deve definir as seguintes coisas: 
	funcao para alimentar watchdog
	void wdt_feed(void);
	
	variavel externa que guarda os microsegundos
	extern uint32_t Milliseconds;
	
	funcao que retorna o registrador do contador de microsegundos do timer de 32 bits
	uint32_t get_microseconds(void){return LPC_TMR32B0->TC;}
	*/

typedef struct{
	uint32_t TimeComp;
	uint32_t TimeStart;
}DELAY_ts;

void delay_start(DELAY_ts * oDelay, uint32_t TimeComp);
uint8_t delay_check(DELAY_ts * oDelay);

typedef struct{
	uint32_t TimeStart;
	uint32_t Interval;
}STOPWATCH_ts;

void stopwatch_start(STOPWATCH_ts * oStopWatch);
void stopwatch_stop(STOPWATCH_ts * oStopWatch);

void delay_update(void);
void delay_blocking(uint32_t TimeComp);

#endif // __DELAY_H_
