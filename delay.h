/* usuario deve definir as seguintes coisas: 
	funcao para alimentar watchdog
	void wdt_feed(void);
	
	variavel externa que guarda os microsegundos
	extern uint32_t Milliseconds;
	
	funcao que retorna o registrador do contador de microsegundos do timer de 32 bits
	uint32_t get_microseconds(void){return LPC_TMR32B0->TC;}
	*/

/* If WDTEnabled == 0, _feed_dog may be NULL */
void delay_init(uint8_t WDTEnabled, void (*_feed_dog)(void), uint64_t (*_get_stopwatch_counter)(void));

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

/* This function must be called periodicaly */
void delay_update(void);

void delay_blocking(uint32_t TimeComp);
