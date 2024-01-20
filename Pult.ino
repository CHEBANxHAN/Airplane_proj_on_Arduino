#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

#define pinx 0
#define piny 1
#define reg 4

RF24 radio(9, 10);

int tdata[3];

byte address[][6] = {"1Node", "2Node", "3Node", "4Node", "5Node", "6Node"};

void setup() {
  Serial.begin(9600); 

  pinMode(pinx, INPUT);
  pinMode(piny, INPUT);
  pinMode(reg, INPUT);

  radio.begin();              
  radio.setAutoAck(1);        
  radio.setRetries(0, 15);    
  radio.enableAckPayload();   
  radio.setPayloadSize(32);   

  radio.openWritingPipe(address[0]);  
  radio.setChannel(5);        

  radio.setPALevel (RF24_PA_MAX);   
  radio.setDataRate (RF24_250KBPS); 

  radio.powerUp();        
  radio.stopListening();

}

void loop() {
  tdata[0] = map(analogRead(pinx), 0, 1023, 0, 90);
  tdata[1] = map(analogRead(piny), 0, 1023, 0, 90);
  tdata[2] = map(analogRead(reg), 0, 1023, 800, 2300);
  radio.write(&tdata, sizeof(tdata));
  Serial.println(tdata[2]);
  

}
