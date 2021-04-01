// pwm.c
// After installing bcm2835, you can build this
// with something like:
// gcc -o pwm pwm.c -l bcm2835
// sudo ./pwm

#include "fanctrl.h"

int main(int argc, char **argv)
{
    short tmp;
    if (!bcm2835_init())
        return 1;
    bcm2835_gpio_fsel(PIN, BCM2835_GPIO_FSEL_ALT5);
    bcm2835_pwm_set_clock(BCM2835_PWM_CLOCK_DIVIDER_16);
    bcm2835_pwm_set_mode(PWM_CHANNEL, 1, 1);
    bcm2835_pwm_set_range(PWM_CHANNEL, RANGE);
    while (1) {
        tmp = get_cpu_tmp(void);
        if (tmp > 50)bcm2835_pwm_set_data(PWM_CHANNEL, 1023);
        if (tmp < 50)bcm2835_pwm_set_data(PWM_CHANNEL, 0);
    }
    bcm2835_close();
    return 0;
}
