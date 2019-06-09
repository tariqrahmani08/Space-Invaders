#include <unistd.h>
#include <stdio.h>
#include <wiringPi.h>
#include "GPIO_INIT.h"
#include "controller.h"

int main()
{   
    unsigned int *gpio = gpioPtr();
    unsigned int input = 0;
    unsigned int oldInput = 0;
    printf("Created by: Tariq Rahmani, Daniel Contreras, Benjamin Sterling\n");
    printf("Please enter input...\n");
    while (oldInput != 4)
    {   
        while(input == 0)
        {
            input = read_snes(gpio);
            //if(input != 0 &&  oldInput!=input)
            if (input == 0 && oldInput != 0)
            {   
                printf ("you pressed %d\n", oldInput);
                break;
            }
        }
        oldInput = input;
        input = 0;
        delay(50);
    }
        
    printf("Program is terminating...\n");
    return 0;
}
