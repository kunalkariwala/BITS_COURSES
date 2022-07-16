/*********************************************************************************************
Sometimes we want to protect critical pieces of code against Control-C attacks and other such signals, save previous value of the handler so that it can be restored after the critical code has executed in the following example SIGINT is disabled. 
*********************************************************************************************/

/*   This program shows the effect of ignoring Ctrl-C. 
It also shows how to resume with its default behaviour.            
*/

#include  <stdio.h>
#include  <signal.h>

#define   MAX_i    100000
#define   DIVISOR   1000
#define   MAX_j    20000

int main(void)
{
     int            i;
     unsigned long  j, sum;

     signal(SIGINT, SIG_IGN);           
     /* ignore Ctrl-C 
     TODO We do not want people to interrupt this entire computation
     computation hence we simply ignore CTRL + C.
     TODO Therefore, we can make it atomic using signals
     */
     printf("CPU-bound loop started.  Pressing Ctrl-C has no effect....\n");
     for (i = 1; i <= MAX_i; i++)  {
          sum = 0;
          for (j = 0; j <= MAX_j; j++)
               sum += j;
          if (i % DIVISOR == 0)
               printf("Iteration %d, sum = %ld\n", i, sum);
     }
     printf("Computation is done.\n\n");

     signal(SIGINT, SIG_DFL);           /* use default              */
     printf("CPU-bound loop restarted.  Pressing Ctrl-C HAS effect now...\n");
     for (i = 1; i <= MAX_i; i++)  {
          sum = 0;
          for (j = 0; j <= MAX_j; j++)
               sum += j;
          if (i % DIVISOR == 0)
               printf("Iteration %d, sum = %ld\n", i, sum);
     }
     printf("Computation is done.\n");
}
