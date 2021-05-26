#include "stdint.h"
#include "delay.h"

#ifdef __DELAY_H_
	
	static void (*delay_feed_dog)(void);
	static uint64_t (*delay_get_micros)(void);
	static uint64_t (*delay_get_millis)(void);

	/* TODO: fazer um ponteiro pra funcao q r eseta o watchdog e passar a funcao por parametro
	 * em uma funcao delay_init(...)
	 */

	static uint32_t Milliseconds = 0;

	void delay_update(void){
		Milliseconds++;
	}

	void delay_blocking(uint32_t TimeComp){
		DELAY_ts oDelay;
		delay_start(&oDelay, TimeComp);
		while(!delay_check(&oDelay)){
			//wdt_feed();
		}
	}

	void delay_start(DELAY_ts * oDelay, uint32_t TimeComp){
		oDelay->TimeStart = Milliseconds;
		oDelay->TimeComp = TimeComp;
	}

	uint8_t delay_check(DELAY_ts * oDelay){
		return ((Milliseconds - oDelay->TimeStart) >= oDelay->TimeComp);
	}

	void stopwatch_start(STOPWATCH_ts * oStopWatch){
		oStopWatch->TimeStart = get_microseconds();
	}
	
	void stopwatch_stop(STOPWATCH_ts * oStopWatch){
		oStopWatch->Interval = get_microseconds() - oStopWatch->TimeStart;
	}
	
#endif
