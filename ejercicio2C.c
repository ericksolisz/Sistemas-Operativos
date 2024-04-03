#include<stdio.h>
#include<unistd.h>
#include<signal.h>

int alarm_count = 0;

void sig_handler(int signum)
{
    printf("Dentro de handler\n");
    alarm_count++;

    if (alarm_count == 1) {
        alarm(2);
    }
}

int main()
{
    signal(SIGALRM, sig_handler); 

    alarm(4);
    for(int i=1;;i++)
    {

        printf("%d : dentro de main \n",i);
        sleep(1); 
    }
    
    return 0;

}