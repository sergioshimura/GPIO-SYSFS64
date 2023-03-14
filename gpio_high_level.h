
/*
@File name: gpio_high_level.h
@Author Igor Ruschi Andrade E Lima <igor.lima@lsitec.org.br>
@LSITEC
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <fcntl.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/time.h>  
#include <sys/ioctl.h>

#ifndef __LABRADOR_GPIO_SYSFS
#include "labrador_gpio_sysfs.h"
#endif

#ifndef __CANINOS_TIME_H
#include "caninos_time.h"
#endif


/*******************************************************************
 *  File Descriptors...
 * 
*******************************************************************/
//Files Descriptors

int gpio_dir_fds[160];
int gpio_val_fds[160];


/*debounce for gpio example*/
int read_gpio_status(int gpio);

int get_gpio_number(char *gpio);

/*
open the gpio, abstracting low level layer
abstract export sysfs and val file
*/
int open_gpio(int gpio_num);

/*
close the gpio, abstract low level layer
*/
int close_gpio(int gpio_num);

int set_gpio_dir(int gpio_num, const unsigned int gpio_dir);

/*
set the value of the gpio, abstract all linux file stuffs
*/
int set_gpio(int gpio_num, const unsigned int value);

int get_gpio(int gpio_num);
