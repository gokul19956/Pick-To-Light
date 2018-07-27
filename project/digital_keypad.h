#ifndef DIGITAL_KEYPAD_H
#define DIGITAL_KEYPAD_H

#define LEVEL_CHANGE			0
#define STATE_CHANGE			1

#define SWITCH1					0x06
#define SWITCH2					0x05
#define SWITCH3					0x03
#define ALL_RELEASED			0x07

#define INPUT_PINS				0x07

void init_digital_keypad(void);
unsigned char read_digital_keypad(unsigned char detection_type);

#endif
