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
    unsigned int *gpio = gpioPtr();
    int buttons[16] = {};
    
    init_gpio(gpio, CLK, 0b001);
    init_gpio(gpio, LAT, 0b001);
    init_gpio(gpio, DAT, 0b000);    

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

        int k = 0;
        while (k < 16)
        {
            printf("%d", buttons[k]);
            k++;
        }
        printf("\n");
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

