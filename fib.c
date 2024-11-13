/**
 *   Name: 	fib.c
 *   Author: 	Johnnie Massart
 *   Date:  	November 13, 2024
 *
 *	Modify this program to calculate the amount of time it takes to 
 *	calculate each new fibbinocci number.  Do this as follows:
 *		1 - Set the ualarm value to 1/100 of a second.
 *		2 - Set up an interrupt on SIGALRM
 *		3 - Each time a timer interrupt occurs, increment a
 *		    counter, counting the number of interrupts or 1/100's
 *		    of a second.
 */
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

static int counter;

/* Define the method to be used when the SIGALRM is raised.  All it
 * should do is increment the value of counter.
 */
void counterInterrupt(int i)
{
    counter += 1;
}



int fib(int n) 
{
    if (n <= 1)
	return 1;
    return (fib(n-1) + fib(n-2));
}

int main() 
{
    int i;
    /* Call ualarm with two parameters of 100 (100 microseconds) 
     * This sets the alarm to go off at 100 microsecond intervals.  
     * Note that even if you set it to 1, it will not materially
     * impact the program as you are below the resolution of the system
     * clock anyway. (I am not sure what it is, but the CPU is much faster
     * than the resolution you will be able to get with the timer.  This
     * could be a function of the Alarm mechanism, or because of the fact
     * that tis is really a software interrupt.  You should be prepared to
     * explain what this means.)
     */
    ualarm(100,100);


    /* Use sigset here to set the SIGALRM handler to the method you
     * defined earlier.
     */
    sigset(SIGALRM, counterInterrupt);


    /* This outputs the number of times counter was incremented */
    for (i = 3; i < 37; i++) 
        printf("fib for %d = %d and counter = %d\n", i, fib(i), counter);
}







