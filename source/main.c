#include <unistd.h>
#include "GPIO_INIT.h"
#include <stdio.h>
#include <wiringPi.h>

#define CLK 11
#define LAT 9
#define DAT 10
#define GPSET0 7
#define GPCLR0 10
#define GPLEV0 13

void init_gpio(unsigned int *gpio, int pin_number, int function);
void write_gpio(unsigned int *gpio, int pin_number, int n);
int read_gpio(unsigned int *gpio, int pin_number);

int main()
{   
    printf("Created by: Tariq Rahmani, Daniel Contreras, Benjamin Sterling\n");
    unsigned int *gpio = gpioPtr();
    int buttons[16] = {};
    int oldButtons[16] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
    init_gpio(gpio, CLK, 0b001);
    init_gpio(gpio, LAT, 0b001);
    init_gpio(gpio, DAT, 0b000);    
    printf("Please press a button..\n");
    while (1) 
    {   
        write_gpio(gpio, CLK, 1);
        write_gpio(gpio, LAT, 1);
        delayMicroseconds(12);
        write_gpio(gpio, LAT, 0);

        int i = 0;
        while(i < 16)
        {
            delayMicroseconds(6);
            write_gpio(gpio, CLK, 0);
            delayMicroseconds(6);
            buttons[i] = read_gpio(gpio, DAT);
            write_gpio(gpio, CLK, 1);
            i++;
        }
        
        
        if(buttons[3] == 0)
        {
            printf("Program is terminating\n");
            return 0;
        }
        else if(buttons[0] == 0 && oldButtons[0] == 1)
        {
            printf("You have pressed B\n");
            printf("Please press a button..\n");
        }
        else if(buttons[1] == 0 && oldButtons[1] == 1)
        {
            printf("You have pressed Y\n");
            printf("Please press a button..\n");
        }
        else if(buttons[2] == 0 && oldButtons[2] == 1)
        {
            printf("You have pressed Select\n");
            printf("Please press a button..\n");
        }
        else if(buttons[4] == 0 && oldButtons[4] == 1)
        {
            printf("You have pressed Joy-pad UP\n");
            printf("Please press a button..\n");
        }
        else if(buttons[5] == 0 && oldButtons[5] == 1)
        {
            printf("You have pressed Joy-pad DOWN\n");
            printf("Please press a button..\n");
        }
        else if(buttons[6] == 0 && oldButtons[6] == 1)
        {
            printf("You have pressed Joy-pad LEFT\n");
            printf("Please press a button..\n");
        }
        else if(buttons[7] == 0 && oldButtons[7] == 1)
        {
            printf("You have pressed Joy-pad RIGHT\n");
            printf("Please press a button..\n");
        }
        else if(buttons[8] == 0 && oldButtons[8] == 1)
        {
            printf("You have pressed A\n");
            printf("Please press a button..\n");
        }
        else if(buttons[9] == 0 && oldButtons[9] == 1)
        {
            printf("You have pressed X\n");
            printf("Please press a button..\n");
        }
        else if(buttons[10] == 0 && oldButtons[10] == 1)
        {
            printf("You have pressed LEFT\n");
            printf("Please press a button..\n");
        }
        else if(buttons[11] == 0 && oldButtons[11] == 1)
        {
            printf("You have pressed RIGHT\n");
            printf("Please press a button..\n");
        }
        else{}
        
        int k;
        for(k=0; k<16; k++)
        {
            oldButtons[k] = buttons[k];
        }
        delay(50);
    }
    return 0;
}

/**
 *
 */
void init_gpio(unsigned int *gpio, int pin_number, int function) 
{
    int reg = pin_number / 10; 
    int bit = (pin_number % 10) * 3; 
    gpio[reg] = (gpio[reg] & ~(0b111 << bit)) | (function << bit);
}

/**
 *
 */
void write_gpio(unsigned int *gpio, int pin_number, int n)
{
    if (n == 1)
        gpio[GPSET0] = 1 << pin_number;
    else
        gpio[GPCLR0] = 1 << pin_number;
}

/**
 *
 */
int read_gpio(unsigned int *gpio, int pin_number)
{
    return (gpio[GPLEV0] >> pin_number) & 1; 
}

