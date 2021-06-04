#include "stdint.h"
#include "stdlib.h"
#include "stdio.h"
#include "delay.h"
#include "windows.h"

// Will be called every 1 ms
void CALLBACK millisecond_interruption(UINT uTimerID, UINT uMsg, DWORD *dwUser, DWORD *dw1, DWORD *dw2)
{
    delay_update();
}

int main(void)
{
    uint8_t t = 0;
    DELAY_ts DelayTeste;
    MMRESULT id = timeSetEvent(1, 1, (LPTIMECALLBACK) millisecond_interruption, NULL, TIME_PERIODIC);

    printf("O programa iniciou.\n\n");

    delay_init(0, 0, 0);

    while(t < 10)
    {
        delay_blocking(1000);
        printf("%d ", t);
        t++;
    }
    
    printf("\n\nO programa terminou.");

    timeKillEvent(id);

    return 0;
}
