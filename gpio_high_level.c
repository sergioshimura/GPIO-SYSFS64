
/*
@File name: gpio_high_level.c
@Author Igor Ruschi Andrade E Lima <igor.lima@lsitec.org.br>
@LSITEC
*/

#include "gpio_high_level.h"

/*debounce for gpio example*/
int read_gpio_status(int gpio){
    int i = 0;
    int high = 0;
    int low = 0;
    int temp = 0;
    while(i<5){
        temp = get_gpio(gpio);
        if(temp == GPIO_HIGH){
            high++;
        }else{
            if(temp == GPIO_LOW){
                low++;
            }
        }
        i++;
	//5ms of delay
        delay(5);
    }
    if(high > low)
        return GPIO_HIGH;
    else
    if(low > high)
        return GPIO_LOW;
    else
        return temp;
}


int get_gpio_number(char *gpio){
	int factor;
	switch(gpio[0]){
		case 'A': factor = 0;
		break;
		case 'a': factor = 0;
		break;
		case 'B': factor = 1;
		break;
		case 'b': factor = 1;
		break;
		case 'C': factor = 2;
		break;
		case 'c': factor = 2;
		break;
		case 'D': factor = 3;
		break;
		case 'd': factor = 3;
		break;
		case 'E': factor = 4;
		break;
		case 'e': factor = 4;
		break;
		default:
			factor = 0;
		break;
	};
	
	return (factor * 32) + atoi(gpio + 1);
}
/*
open the gpio, abstracting low level layer
abstract export sysfs and val file
*/
int open_gpio(int gpio_num){
	int ret;
	ret = gpio_export(gpio_num);
	if(ret == 0){
		/*if the gpio was open, probably the val file will be open to, so do it here*/
		gpio_val_fds[gpio_num] = gpio_open_val_fd(gpio_num, O_RDWR | O_SYNC);
    		if(gpio_val_fds[gpio_num] < 0){
        		printf("[ERROR]: could not open value of gpio_num: %d\n", gpio_num);
        		return -1;
    		}
	}
}

/*
close the gpio, abstract low level layer
*/
int close_gpio(int gpio_num){
	gpio_unexport(gpio_num);
	return 0;
}

int set_gpio_dir(int gpio_num, const unsigned int gpio_dir){
	
	int ret;

	gpio_dir_fds[gpio_num] = gpio_open_dir_fd(gpio_num);
    	if(gpio_dir_fds[gpio_num] < 0){
        	printf("[ERROR]: could not open direction of gpio_num: %d\n", gpio_num);
        	return -1;
    	}
	
	ret = gpio_direction(gpio_dir_fds[gpio_num], gpio_dir);
    	if(ret != 0){
        	printf("[ERROR]: Could not set the direction of gpio_num: %d\n", gpio_num);
        	return -2;
    	}else{
        	close(gpio_dir_fds[gpio_num]);
    	}
	
	return 0;
}

/*
set the value of the gpio, abstract all linux file stuffs
*/
int set_gpio(int gpio_num, const unsigned int value){
	gpio_write(gpio_val_fds[gpio_num], value);
	return 0;
}

int get_gpio(int gpio_num){
	int ret;
	ret = gpio_read(gpio_val_fds[gpio_num]);
	if(ret == GPIO_HIGH || ret == GPIO_LOW){
		return ret;	
	}else{
		printf("[ERROR] could not read a valid value from gpio_num: %d\n", gpio_num);
		return -1;
	}
}

