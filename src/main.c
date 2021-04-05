// pwm.c
// After installing bcm2835, you can build this
// with something like:
// gcc -o pwm pwm.c -l bcm2835
// sudo ./pwm

#include "fanctrl.h"

short get_cpu_tmp(void)
{
    int fd;
    char buff[3];

    //open the file with cpu temp
    fd = open("/sys/class/thermal/thermal_zone0/temp", O_RDONLY);
    read(fd, buff, 2);      //read only 2 first char of file content
    close(fd);              //close da file
    buff[2] = '\0';         //add end char at the end of string buff
    //return cpu temp converted to short var type
    return ((buff[0] - 48) * 10) + ((buff[1]) - 48);
}

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
