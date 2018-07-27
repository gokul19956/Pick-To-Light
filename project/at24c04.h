#ifndef EEPROM_AT24C04_H
#define EEPROM_AT24C04_H

#define SLAVE_READ_EE				0xA1
#define SLAVE_WRITE_EE				0xA0

#define DUMMY						0xFF

void eeprom_at24c04_byte_write(unsigned char memory_loc, unsigned char data);
void eeprom_at24c04_page_write(unsigned char memory_loc, unsigned char *data, unsigned char count);
unsigned char eeprom_at24c04_cur_addr_read(void);
unsigned char eeprom_at24c04_random_read(unsigned char memory_loc);

#endif
