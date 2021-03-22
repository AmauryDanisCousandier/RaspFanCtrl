// pwm.c
// After installing bcm2835, you can build this
// with something like:
// gcc -o pwm pwm.c -l bcm2835
// sudo ./pwm

#include <bcm2835.h>
#include <stdio.h>
#include <stdlib.h>
// PWM output on RPi Plug P1 pin 12 (which is GPIO pin 18)
// in alt fun 5.
// Note that this is the _only_ PWM pin available on the RPi IO headers
#define PIN RPI_GPIO_P1_12
// and it is controlled by PWM channel 0
#define PWM_CHANNEL 0
// This controls the max range of the PWM signal
#define RANGE 1023

int get_cpu_tmp(void)
{
        FILE *file;
        char c;
        file = fopen("/sys/class/thermal/thermal_zone0/temp", "r");
    
        fclose(file);
        return 0;
}

int main(int argc, char **argv)
{
    if (!bcm2835_init())
        return 1;

    // Set the output pin to Alt Fun 5, to allow PWM channel 0 to be output there
    bcm2835_gpio_fsel(PIN, BCM2835_GPIO_FSEL_ALT5);

    // Clock divider is set to 16.
    // With a divider of 16 and a RANGE of 1024, in MARKSPACE mode,
    // the pulse repetition frequency will be
    // 1.2MHz/1024 = 1171.875Hz, suitable for driving a DC motor with PWM
    bcm2835_pwm_set_clock(BCM2835_PWM_CLOCK_DIVIDER_16);
    bcm2835_pwm_set_mode(PWM_CHANNEL, 1, 1);
    bcm2835_pwm_set_range(PWM_CHANNEL, RANGE);

    // Vary the PWM m/s ratio between 1/RANGE and (RANGE-1)/RANGE
    // over the course of a a few seconds
    /*int direction = 1; // 1 is increase, -1 is decrease
    int data = 1;
    while (1)
    {
        if (data == 1)
            direction = 1;   // Switch to increasing
        else if (data == RANGE-1)
            direction = -1;  // Switch to decreasing
        data += direction;
        bcm2835_pwm_set_data(PWM_CHANNEL, data);
        bcm2835_delay(1);
    }*/
    bcm2835_pwm_set_data(PWM_CHANNEL, atoi(argv[1]));
    bcm2835_close();
    //get_cpu_tmp();
    return 0;
}
