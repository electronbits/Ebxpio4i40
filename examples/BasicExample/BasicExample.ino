#include "Ebxpio4i40.h"


Ebxpio4i40 myBoard(0x3f);


void setup() {
 
  Serial.begin(115200);
  myBoard.begin(true);
  delay(1000);
  myBoard.energize(&myBoard.relay1);
  delay(400);
  
  Serial.print("state of relay2: ");
  Serial.println(myBoard.relay2.state);

  Serial.print("state of relay4: ");
  Serial.println(myBoard.relay4.state);

  Serial.print("state of input1: ");
  Serial.println(myBoard.input1.state);
  
  myBoard.energize(&myBoard.relay3);
  Serial.print("Read board: ");
  Serial.println(myBoard.read(),HEX);
  Serial.println(myBoard.printState());
}


void loop() {
  delay(1000);
  myBoard.energize(&myBoard.relay2);
  delay(1000);
  myBoard.denergize(&myBoard.relay2);
  delay(500);
  myBoard.energize(&myBoard.relay4);
  delay(600);
}
