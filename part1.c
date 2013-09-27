/*
 * AF130922: Implementing Part 1 of Project
 */

#include <stdio.h>
#include <stddef.h>
#include <stdio.h>
#include "sys/alt_alarm.h"
#include "alt_types.h"

#define ALARMTICKS(x) ((alt_ticks_per_second()*(x))/10) //when you use "ALARMTICKS(5)", it specifies the interrupt period to be 0.5 second (= 1 second * 5 / 10)
#define MAX 256 //value that j will never get to in prototype_os function
#define QUANTUM_LENGTH 10 //timer interrupt period in tenths of a second

void prototype_os();
alt_u32 myinterrupt_hander (void * context);

static alt_alarm alarm;

int main()
{
  prototype_os();

  return 0; //should never get here
}

void prototype_os()
{
	char j = 0;

    //Here: initialize the timer and its interrupt handler
	//will cause an interrupt every 1 second, calling myinterrupt_handler each time with NULL as the parameter
	alt_alarm_start(&alarm, alt_ticks_per_second(), myinterrupt_hander, NULL);

    while (1)
    {
        alt_printf ("This is the prototype os for my exciting CSE351 course projects!\n");
        //Here: think about what MAX is used for. Pick up an appropriate value for it experimentally.
        //Infinite loop, MAX=256
        for (j = 0 ; j < MAX; j++);
    }
}

/*
 * Is called when the timer alarm interrupt occurs,
 * returns the number of ticks until the next timer alarm interrupt
 */
alt_u32 myinterrupt_hander (void * context)
{
     alt_printf("Interrupted by the timer!\n");
     return ALARMTICKS(QUANTUM_LENGTH);
     //Here: added on 09/25/2011 upon a group's request
     //put "#define ALARMTICKS(x) ((alt_ticks_per_second()*(x))/10)" at the beginning of your code
     //when you use "ALARMTICKS(5)", it specifies the interrupt period to be 0.5 second (= 1 second * 5 / 10)
}
