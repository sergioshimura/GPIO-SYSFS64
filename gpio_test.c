#include <stdio.h>
#include <stdlib.h>

#include "gpio_high_level.h"

int main(){
	int gpio_num = get_gpio_number("C0");
	printf("GPIOC0 : gpio_num = %d\n", gpio_num);
	open_gpio(gpio_num);
	set_gpio_dir(gpio_num, GPIO_DIR_OUT);
	for(int i = 0; i< 100; i++){
		set_gpio(gpio_num, GPIO_HIGH);
		delay(500); //500ms
		set_gpio(gpio_num, GPIO_LOW);
		delay(500); //500ms
	}
	exit(1);
	return -1;
}
