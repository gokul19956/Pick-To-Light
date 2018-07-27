#include "main.h"
#include "at24c04.h"
#include "i2c.h"
#include "delay.h"

unsigned char eeprom_at24c04_cur_addr_read(void)  //using i2c protocol
{
	char received_data = 0;

	i2c_start();
	i2c_write(SLAVE_READ_EE);
	received_data = i2c_read();

	return received_data;
}

unsigned char eeprom_at24c04_random_read(unsigned char memory_loc) //mem location is loaded and from there data is received
{
	unsigned char received_data = 0;

	i2c_start();
	i2c_write(SLAVE_WRITE_EE);
	i2c_write(memory_loc);
	i2c_rep_start();
	i2c_write(SLAVE_READ_EE);
	received_data = i2c_read(); //i2c reads the data
	i2c_stop();

	return received_data;
}

void eeprom_at24c04_byte_write(unsigned char memory_loc, unsigned char data)
{
	i2c_start();
	i2c_write(SLAVE_WRITE_EE);
	i2c_write(memory_loc);
	i2c_write(data); //i2c writes data
	i2c_stop();

    delay_ms(5);
}
