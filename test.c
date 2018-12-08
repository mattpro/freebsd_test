
#include <sys/param.h>
#include <sys/module.h>
#include <sys/kernel.h>
#include <sys/systm.h>
#include <sys/types.h>

#include <sys/bus.h>
#include <dev/spibus/spi.h>
#include <dev/spibus/spibusvar.h>
#include <sys/gpio.h>

#include <sys/kthread.h>
#include <sys/proc.h>
#include <sys/sched.h>

#include "gpio_if.h"
#include "spibus_if.h"

device_t dev;

void spi_send( uint8_t byte );


static void led_task(void* arg)
{
	device_t devLed;
	devLed = devclass_get_device( devclass_find("gpio"), 0);
	GPIO_PIN_SETFLAGS( devLed, 26, GPIO_PIN_OUTPUT);
	for(;;)
	{
		GPIO_PIN_TOGGLE(dev, 26);
	}


}



void spi_send( uint8_t byte )
{
	struct spi_command spi_cmd;
	uint8_t temp;

	memset(&spi_cmd, 0, sizeof(struct spi_command) );
	spi_cmd.tx_data = &byte;
	spi_cmd.rx_data = &temp;
	spi_cmd.rx_data_sz = 1;
	spi_cmd.tx_data_sz = 1;
	
	// SPIBUS_TRANSFER(device_get_parent( devSpi ), devSpi, &spi_cmd );

}


static int hello_modevent( module_t mod __unused, int event, void *arg __unused)
{
	int error = 0;
//	int i;	

	switch (event)
	{
		case MOD_LOAD:
			uprintf("Inicjalizacja i wywolanie taska \n");
			kproc_create( led_task, NULL, NULL, 0,0, "led task" );
		//	dev = devclass_get_device( devclass_find("gpio"), 0 );
		//	if ( dev == NULL )
		//	{
		//		uprintf("Device class gpio not found \n");
		//	}

		//	GPIO_PIN_SETFLAGS(dev, 26, GPIO_PIN_OUTPUT);
		//	for( i = 0 ; i < 255 ; i ++ )
		//	{
		//		GPIO_PIN_TOGGLE( dev, 26);
		//		DELAY(50000);
		//	}
		//	
		//	GPIO_PIN_SET(dev, 26, GPIO_PIN_LOW);

		break;
		case MOD_UNLOAD:
			uprintf("By by\n");
		break;
		default:
			error = EOPNOTSUPP;
		break;
	}

	return error;
}


static moduledata_t hello_mod = {
	"hello",
	hello_modevent,
	NULL
};


DECLARE_MODULE(hello, hello_mod, SI_SUB_DRIVERS, SI_ORDER_MIDDLE);

