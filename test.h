#ifndef __TEST
#define __TEST

#define LED_PIN_NUMBER	26

struct lcd_sc_t
{
	device_t dev;
	device_t dev_gpio;
	struct cdev *cdev_p;
	struct mtx mtx;
};


#endif
