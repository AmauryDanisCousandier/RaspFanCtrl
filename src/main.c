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

void wait_stime(int delay)
{
	int i = 0;
	while (i++ != (delay * 100));
}

int init(void)
{
    if (!bcm2835_init()) return 1;
    bcm2835_gpio_fsel(PIN, BCM2835_GPIO_FSEL_ALT5);
    bcm2835_pwm_set_clock(BCM2835_PWM_CLOCK_DIVIDER_16);
    bcm2835_pwm_set_mode(PWM_CHANNEL, 1, 1);
    bcm2835_pwm_set_range(PWM_CHANNEL, RANGE);
    return 0;
}

int auto_mode(short low, short high)
{
    short tmp;

    if (init()) return 1;
    while (1) {
        tmp = get_cpu_tmp();
        if (tmp > high)bcm2835_pwm_set_data(PWM_CHANNEL, 1023);
        if (tmp < low)bcm2835_pwm_set_data(PWM_CHANNEL, 0);
    }
    bcm2835_close();
}

int manual_mode(void)
{
    if (init()) return 1;
    while (1) {
        tmp = get_cpu_tmp();
        if (tmp > high)bcm2835_pwm_set_data(PWM_CHANNEL, 1023);
        if (tmp < low)bcm2835_pwm_set_data(PWM_CHANNEL, 0);
    }
    bcm2835_close();
}

int main(int argc, char **argv)
{
    if (argc == 1) return (auto_mode(60, 70));
    if (argc == 2 && argv[1][0] == '-' && argv[1][1] == 'm') return (manual_mode());
    return 0;
}
