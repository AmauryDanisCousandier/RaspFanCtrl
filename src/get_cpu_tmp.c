/*
** AmauryDanisCousandier PROJECT, 2021
** RaspFanCtrl
** File description:
** get_cpu_tmp.c
*/

#include "fanctrl.h"

short get_cpu_tmp(void)
{
    int fd;
    char buff[3];

    //open the file with cpu temp
    fd = open("/sys/class/thermal/thermal_zone0/temp", O_RDONLY);
    read(fd, buff, 2);      //read only 2 first char of file content
    close(fd);      //close da file
    buff[2] = '\0';     //add end char at the end of string buff
    //return cpu temp converted to short var type
    return ((buff[0] - 48) * 10) + ((buff[1]) - 48);
}