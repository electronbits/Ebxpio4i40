/*
* Ebxpio4i40.cpp
 *
 *  Created on: June 2020
 *  Author: Electronbits
 *  Website: www.electronbits.com
 *  This is an Arduino library for EBIOXP0919-4I4O which provides
 *  class and methods to control the relays and read inputs
 *
 */

#include "Ebxpio4i40.h"


/*
 * Stores chip address
 * @param _boardAddress: chip_address
*/

Ebxpio4i40::Ebxpio4i40(uint8_t _boradAddress) {
	this->_boardAddress= _boradAddress;
} // Ebxpio4i40

/*
 * Initilizes the Board board address
 * Configure the board to have 4 inputs and for outputs by
 * writing 0b11110000 (0xF0) into CFG_REGISTER register
 * de-enrgizing all relays.
 * It skips the init the chip it is has been already configured.
 * @param it will init the chip no matter what if it's been already configured if true,
 * otherwise skips if the chip has been configured before.
 */
void Ebxpio4i40::begin(bool cleanChip){
	if (!read() == Ebxpio4i40::_CFG_VALUE || true==cleanChip){
		Wire.begin(_boardAddress);
		Wire.beginTransmission(_boardAddress);
		Wire.write(Ebxpio4i40::_CFG_REGISTER);
		Wire.write(0xf0);
		Wire.endTransmission();
		Wire.beginTransmission(_boardAddress);
		Wire.write(Ebxpio4i40::_WRITE_REGISTER);
		Wire.write(0x0);
		Wire.endTransmission();
	}
	initRelays();
	initInputs();
} // begin


/*
 * Initilizes the Relays of the board
 * It reads the current relays status and fill up the states accordingly.
 * HIGH means the relay is activated.
 */
void Ebxpio4i40::initRelays(void){
	relay1.id=0;relay2.id=1;relay3.id=2;relay4.id=3;
	uint8_t relays_value = (read()&0xf);
	relay1.state=relays_value&0x1?HIGH:LOW;relay2.state=relays_value&0x2?HIGH:LOW;
	relay3.state=relays_value&0x4?HIGH:LOW;relay4.state=relays_value&0x8?HIGH:LOW;
	relay1.direction=OUTPUT;relay2.direction=OUTPUT;relay3.direction=OUTPUT;relay4.direction=OUTPUT;
} // initRelays

/*
 * Initilizes the inputs of the board
 * It reads the current inputs and fill up the states accordingly.
 * Noted, inputs are all pulled-up, so LOW means activated and
 * HIGH means Deactivated.
 */
void Ebxpio4i40::initInputs(void){
	input1.id=0;input2.id=1;input3.id=2;input4.id=3;
	uint8_t input_value = (read()&0xf0)>>4;
	input1.state=input_value&0x1?HIGH:LOW; input2.state=input_value&0x2?HIGH:LOW;
	input3.state=input_value&0x4?HIGH:LOW;input4.state=input_value&0x8?HIGH:LOW;
	input1.direction=INPUT;input2.direction=INPUT;input3.direction=INPUT;input4.direction=INPUT;
} // initInputs


Ebxpio4i40::~Ebxpio4i40(void) {
	// TODO Auto-generated destructor stub
}


/*
 * Energizes relays of board, taking the relay pointer.
 * @param relay pointer to the specific relay
 * @return boolean value. if true means the relay has been successfully energized
 * otherwise returns false
 */
bool Ebxpio4i40::energize(Pin *relay){
  uint8_t relayLocation = (read()&0xf) | (1<<relay->id);
  Wire.begin(_boardAddress);
  Wire.beginTransmission(_boardAddress);
  Wire.write(Ebxpio4i40::_WRITE_REGISTER);   
  Wire.write(relayLocation);             
  int ret = Wire.endTransmission();
  if(ret==0){
	  relay->state=HIGH;
	  return true;
  }
  else return false;
} // energize


/*
 * Energizes relays of board, taking the relay pointer.
 * @param relay pointer to the specific relay
 * @return boolean value. if true means the relay has been successfully energized
 * otherwise returns false
 */
bool Ebxpio4i40::denergize(Pin *relay){
  uint8_t relayLocation = (read()&0xf) & (0xf^1<<relay->id);
  Wire.begin(_boardAddress);
  Wire.beginTransmission(_boardAddress);
  Wire.write(Ebxpio4i40::_WRITE_REGISTER);
  Wire.write(relayLocation);
  int ret = Wire.endTransmission();
  if(ret==0){
	  relay->state=LOW;
	  return true;
  }
  else return false;
} // denergize

/*
 * It returns 8bit value 4-MSB bit is
 * for Input value and 4-LSB bits is 
 * for ouput (relay) value.
 */
uint8_t Ebxpio4i40::read(void){
  uint8_t value=0;
  Wire.begin(_boardAddress);
  Wire.beginTransmission(_boardAddress);
  Wire.write(Ebxpio4i40::_READ_REGISTER);
  Wire.endTransmission();
  Wire.requestFrom((int)_boardAddress,1);
//   while(Wire.available())
//     {
  value = Wire.read();
    // }
  return value;
} // read

/*
 * Provides ability to read the current status of the input
 * @param input number as a pointer
 * @return state of input,
 * if it returns 2, means the passing object is invalid.
 */
byte Ebxpio4i40::readInput(Pin *input){
	if(!input->direction == INPUT){
		return 2;
	}
	uint8_t input_value = (read()&0xf0)>>4;
	return  input_value & (1<<input->id);
} // readInput


/*
 * Provides a string describing relays states
 * and inputs status. each report followed by a new line.
 */
String Ebxpio4i40::printState(void){
	uint8_t status = read();
	String res= "";
	for(byte i=0;i<Ebxpio4i40::_MAX_RELAY;i++){
		res += "Relay #"+String((i+1))+(String)(status & (1<<i)?" On\n":" Off\n");
	}
	uint8_t input_value = (status&0xf0)>>4;
	for(byte i=0;i<Ebxpio4i40::_MAX_INPUT;i++){
			res += "Input #"+String((i+1))+(String)( input_value & (1<<i)?" Deactivated\n":" Activated\n");
		}
	return res;
} // printState


/*
* Returns board/chip address
@return: uint8_t
*/
uint8_t Ebxpio4i40::getBoardAddress(){
	return this->_boardAddress;
} // getBoardAddress