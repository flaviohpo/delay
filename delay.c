#include "stdint.h"
#include "delay.h"

#ifdef __DELAY_H_
	
	static uint8_t DelayWatchdogEnabled = 0;
	static uint64_t DelayCounter = 0;

	static void (*delay_feed_dog)(void);
	static uint64_t (*delay_get_stopwatch_counter)(void);

	void delay_init(uint8_t WDTEnabled, void (*_feed_dog)(void), uint64_t (*_get_stopwatch_counter)(void))
	{
		delay_feed_dog = _feed_dog;
		delay_get_stopwatch_counter = _get_stopwatch_counter;

		if(WDTEnabled != 0)
		{
			DelayWatchdogEnabled = 1;
		}
		else
		{
			DelayWatchdogEnabled = 0;
		}
	}

	void delay_update(void)
	{
		DelayCounter++;
	}

	void delay_blocking(uint32_t TimeComp)
	{
		DELAY_ts oDelay;
		delay_start(&oDelay, TimeComp);
		while(!delay_check(&oDelay))
		{
			if(DelayWatchdogEnabled != 0)
			{
				delay_feed_dog();
			}
		}
	}

	void delay_start(DELAY_ts * oDelay, uint32_t TimeComp)
	{
		oDelay->TimeStart = DelayCounter;
		oDelay->TimeComp = TimeComp;
	}

	uint8_t delay_check(DELAY_ts * oDelay)
	{
		return ((DelayCounter - oDelay->TimeStart) >= oDelay->TimeComp);
	}

	void stopwatch_start(STOPWATCH_ts * oStopWatch)
	{
		oStopWatch->TimeStart = delay_get_stopwatch_counter();
	}
	
	void stopwatch_stop(STOPWATCH_ts * oStopWatch)
	{
		oStopWatch->Interval = delay_get_stopwatch_counter() - oStopWatch->TimeStart;
	}
	
#endif
