
/*
@File name: labrador_gpio_sysfs.c
@Author Igor Ruschi Andrade E Lima <igor.lima@lsitec.org.br>
@LSITEC
*/

#ifndef __LABRADOR_GPIO_SYSFS_H

#include "labrador_gpio_sysfs.h"

#endif



int gpio_open_dir_fd(int gpio){
    char fd_path[100];
    sprintf(fd_path, "/sys/class/gpio/gpio%d/direction", gpio);
    return open(fd_path,  O_WRONLY | O_SYNC);
}

int gpio_open_val_fd(int gpio, int flags){
    char fd_path[100];
    sprintf(fd_path, "/sys/class/gpio/gpio%d/value", gpio);
	return open(fd_path,  flags);
}

int gpio_read(int gpiofd){
    int ret = 0;
	char in[3] = {0, 0, 0};

    if(gpiofd < 0) {
		printf("[ERROR]:gpiofd is invalid\n");
		ret = -1;
	}

    //
    //ret = read(gpiofd, in, 1);
	do {
		ret = read(gpiofd, in, 1);
		lseek(gpiofd, 0, SEEK_SET);
	} while (ret == 0);
	if(ret == -1){
		printf("[ERROR]: value read %d bytes: %s\n", ret, in);
		lseek(gpiofd, 0, SEEK_SET);
		return -1;
	}
	//printf("[DEBUG]: value read %d bytes: %s\n", ret, in);
	
    if(in[0] == '1'){
		lseek(gpiofd, 0, SEEK_SET);
        return GPIO_HIGH;
    }else
    {
        if(in[0] == '0'){
			lseek(gpiofd, 0, SEEK_SET);
            return GPIO_LOW;
		}else
        {
            printf("[ERROR] When read from gpio\n");
            return -1;
        }
    }
    
}

int gpio_write(int gpiofd, int value){
    int ret = 0;
    char buf[50];
    
    if(gpiofd < 0) {
		printf("[ERROR]:gpiofd is invalid\n");
		ret = -1;
	}

    lseek(gpiofd, 0, SEEK_SET);

    if(value == GPIO_HIGH)
        strcpy(buf, "1");
    else
        if(value == GPIO_LOW)
            strcpy(buf, "0");
		else
			printf("[ERROR] Invalid value requested to set GPIO\n");
		
    
    ret = write(gpiofd, buf, strlen(buf));
	//printf("write %d bytes to gpio value file, strlen(buf) = %d requested to write : %s\n", ret, strlen(buf), buf);
    if(ret < 0){
        printf("[ERROR]: can't set gpio\n");
		return ret;
    }else{
		if(ret == strlen(buf))//success
			return 0;
	}

    return ret;
}

int gpio_direction(int gpiofd, int dir){
	int ret = 0;
	char buf[50];
	if(gpiofd < 0) {
		printf("[ERROR]:gpiofd is invalid\n");
		ret = -1;
	}

    lseek(gpiofd, 0, SEEK_SET);

	if(dir == GPIO_DIR_OUT){
		if (3 != write(gpiofd, "out", 3)) {
			printf("[ERRO]:Couldn't set GPIO direction to out\n");
			ret = -2;
		}
	}else
    if(dir == GPIO_DIR_IN){
        if(2 != write(gpiofd, "in", 2)) {
			printf("[ERROR]:Couldn't set GPIO direction to in\n");
			ret = -4;
		}
    }
	return ret;
}

int gpio_export(int gpio)
{
	int efd;
	char buf[50];
	int gpiofd, ret;

	/* check if it has already been exported */
	sprintf(buf, "/sys/class/gpio/gpio%d/value", gpio);
	efd = open(buf, O_WRONLY);
	if(efd != -1) {
		close(efd);
		return 0;
	}

	efd = open("/sys/class/gpio/export", O_WRONLY | O_SYNC);

	if(efd != -1) {
		sprintf(buf, "%d", gpio); 
		ret = write(efd, buf, strlen(buf));
		if(ret < 0) {
			printf("[ERROR]:Export failed\n");
			return -2;
		}
		close(efd);
	} else {
		// If we can't open the export file, we probably
		// dont have any gpio permissions
		return -1;
	}
	return 0;
}

void gpio_unexport(int gpio)
{
	int gpiofd, ret;
	char buf[50];
	gpiofd = open("/sys/class/gpio/unexport", O_WRONLY | O_SYNC);
	sprintf(buf, "%d", gpio);
	ret = write(gpiofd, buf, strlen(buf));
	close(gpiofd);
}
