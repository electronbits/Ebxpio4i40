
<img src="https://www.electronbits.com/wp-content/uploads/2019/11/photo5925044940205830409.jpg" alt="drawing" width="350" title="Ebxpio4i4o" alt="board picture"/>

#### It is an Arduino (only tested on Uno model, don't guarantee the same code works over other models) library for [*Ebxpio4i4o*](https://www.electronbits.com/product/ebioxp0919-4i4o/)


Wiring:

| *Ebxpio4i4o*    | Arduino Uno   | 
|:-------------:|:-------------:|
| SCL           | A5            |
| SDA           | A4            |
| GND           | GND           |


The library is using Wire library, so please make sure you have it functioning (as default it is functioning).

### Instruction to install the library:
1. First download the repository and unzip it.
2. copy the extracted folder *EB_XPIO4I4O* to:
    * {your Arduino folder}/libraries/
3. You are ready to go!

* There is a built-in example that shows the sample use of the library, and it can be reached from the Arduino IDE (if you successfully installed the library):
    * Files->Examples->EB_XPIO4I4O->BasicExample.ino

<dl>
  <dt>Board Description</dt>
    <dd>Input voltage: 9~30VDC – 22-14AWG 1.5mm2</dd>
    <dd>4xOutput power relays</dd>
    <dd>4xPulled-up Inputs – Powered by ULN2003 and can handle 500mA based on its datasheet</dd>
    <dd>1xExternal interrupt for inputs</dd>
    <dd>Compatible with All 5VDC Arduinos’ boards</dd>
    <dd>Compatible with EBRPIH1118 ElectronBit’s Rasspberry Pi</dd>
    <dd>Dimension: 97mm*87mm</dd>
    <dd>Pluggable terminal block connector for relays can handle 28-12AWG 2.5mm2</dd>
    <dd>Board is addressable and can have 8 of them on your I2C network</dd>

</dl>
