/*
** AmauryDanisCousandier PROJECT, 2021
** RaspFanCtrl
** File description:
** fanctrl.h
*/

#ifndef FANCTRL_H_
#define FANCTRL_H_

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <bcm2835.h>
#include <sys/stat.h>
#include <sys/types.h>

#define PIN RPI_GPIO_P1_12
// and it is controlled by PWM channel 0
#define PWM_CHANNEL 0
// This controls the max range of the PWM signal
#define RANGE 1023

#endif