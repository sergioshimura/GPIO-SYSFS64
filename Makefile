CC	= gcc #use this one if in Labrador
#CC	= arm-linux-gnueabihf-gcc #use this one if you are in Linux x86 or Linux x64
CFLAGS  = -g
RM      = rm -f

default: all

all: GPIO

GPIO:  labrador_gpio_sysfs.o caninos_time.o gpio_high_level.o gpio_test.o
	$(CC) $(CFLAGS) -o gpioTest caninos_time.o labrador_gpio_sysfs.o gpio_high_level.o gpio_test.o  -lm

clean veryclean:
	$(RM) *.o


