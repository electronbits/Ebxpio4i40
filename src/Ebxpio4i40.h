/*
 * Ebxpio4i40.h
 *
 *  Created on: Nov 10, 2019
 *  Author: Electronbits
 *  Website: www.electronbits.com
 *  This is an Arduino library for EBIOXP0919-4I4O
 *	This library needs Wire.h as it is using its functions to
 *	create communication in I2C to the borad
 *
 */

#ifndef EBXPIO4I40_H
#define EBXPIO4I40_H

#include "Arduino.h"
#include <Wire.h>

/**
 * This class provides interface between users and 
 * EBXPIO4I4O board. User can energize/de-energize relays
 * Read inputs
 * Prints states of relays and inputs
 * @param _boardAddress for constructing class it needs
 * the board address.
 */
class Ebxpio4i40 {

	/*
	 * Provides data structure for each pins.
	 * each Pin can have id, direction and state.
	 * direction defines whether is output if 1 or input if 0
	 * id defines which input/relay number the Pin object is referring to.
	 * state is a enum than can be changed at runtime, and defines the
	 * current state of the pin.
	 */
	struct Pin{
	  byte id : 2;
	  byte direction : 1;
	  byte state;
	};

	public:
	Ebxpio4i40(uint8_t);
	virtual ~Ebxpio4i40();
	bool energize(Pin*);
	bool denergize(Pin*);
	uint8_t read(void);
	byte readInput(Pin*);
	String printState(void);
	void begin(bool);
	uint8_t getBoardAddress(void);

	public:
	Pin relay1,relay2,relay3,relay4,input1,input2,input3,input4;

	private:
	uint8_t _boardAddress;
	void initRelays(void);
	void initInputs(void);

	private:
		static const uint8_t _WRITE_REGISTER = 0x1;
		static const uint8_t _READ_REGISTER = 0x0;
		static const uint8_t _CFG_REGISTER = 0x3;
		static const uint8_t _MAX_RELAY = 4;
		static const uint8_t _MAX_INPUT = 4;
		static const uint8_t _CFG_VALUE = 0xf0;

};


#endif /* EBXPIO4I40_H_ */
