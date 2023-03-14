/*
@File name: labrador_gpio_sysfs.h
@Author Igor Ruschi Andrade E Lima <igor.lima@lsitec.org.br>
@LSITEC
*/

#ifndef __LABRADOR_GPIO_SYSFS_H

#define __LABRADOR_GPIO_SYSFS_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <fcntl.h>
#include <string.h>

#endif

#define     GPIOC4          68
#define     GPIOC5          69 //GPIOC5 = 64 + 5 = 69
#define     GPIOB13         45 //GPIOB13 = 32+13 = 45
#define     GPIOB14         46 //GPIOB14 = 32+14 = 46
#define     GPIOB2          34 
#define     GPIOB1          33
#define     GPIOB0          32
#define     GPIOB10         42
#define     GPIOB15         47    //32+15 = 
#define     GPIOB16         48
#define     GPIOC22         86
#define     GPIOC24         88
#define     GPIOC25         89
#define     GPIOA27         27
#define     GPIOA31         31
#define     GPIOA28         28
#define     GPIOB19         51
#define     GPIOC23         87//64+23
#define     GPIOE2          130 //128 + 2
#define     GPIOE3          131
#define     GPIOB18         50//32+18
#define     GPIOC0          64//32+0
#define     GPIOC1          65

#define GPIO_DIR_OUT    0x2
#define GPIO_DIR_IN     0x1
#define GPIO_HIGH       0x1
#define GPIO_LOW        0x0


int gpio_open_dir_fd(int gpio);
int gpio_open_val_fd(int gpio, int flags);
int gpio_read(int gpiofd);
int gpio_write(int gpiofd, int value);
int gpio_direction(int gpiofd, int dir);
int gpio_export(int gpio);
void gpio_unexport(int gpio);
