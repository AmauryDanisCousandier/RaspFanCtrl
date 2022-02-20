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
        if (tmp > high + 10) bcm2835_pwm_set_data(PWM_CHANNEL, 1023);
        else if (tmp > high + 5) bcm2835_pwm_set_data(PWM_CHANNEL, 900)
        else if (tmp > high) bcm2835_pwm_set_data(PWM_CHANNEL, 700);
        else if (tmp < low) bcm2835_pwm_set_data(PWM_CHANNEL, 0);
    }
    bcm2835_close();
}

int manual_mode(void)
{
    char buff;
    int fan_speed = 500;

    if (init()) return 1;
    while (1) {
        read(0, &buff, 1);
        if (fan_speed >= 0 && buff == '+') fan_speed += 50;
        else if (fan_speed <= 1000 && buff == '-') fan_speed -= 50;
        bcm2835_pwm_set_data(PWM_CHANNEL, fan_speed);
    }
    bcm2835_close();
}

int static_mode(char *argv)
{
    short temp = ((argv[0] - 48) * 10) + ((argv[1]) - 48);
    if (init()) return 1;
    bcm2835_pwm_set_data(PWM_CHANNEL, temp);
    return (0);
}

int main(int argc, char **argv)
{
    if (argc == 1) return (auto_mode(45, 50));
    if (argc == 2 && argv[1][0] == '-' && argv[1][1] == 'm') return (manual_mode());
    if (argc == 2 && argv[1][0] == '-' && argv[1][1] == 's') return (static_mode(argv[2]));
    return 0;
}
