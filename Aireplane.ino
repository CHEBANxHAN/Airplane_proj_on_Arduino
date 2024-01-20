#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include <Servo.h>;

#define an_pin 3

RF24 radio(9, 10);

byte address[][6] = {"1Node", "2Node", "3Node", "4Node", "5Node", "6Node"};
int rdata[3];
byte servo_pin1 = 5;
byte servo_pin2 = 6;
byte motor_pin = 4;

Servo serv1;
Servo serv2;
Servo motor;

void setup() {
  Serial.begin(9600); 

  serv1.attach(servo_pin1);
  serv2.attach(servo_pin2);
  motor.attach(motor_pin);
  pinMode(3, OUTPUT);

  //motor.writeMicroseconds(800);
  //delay(2000);
  //motor.writeMicroseconds(2300);
  //delay(6000);

  radio.begin();              
  radio.setAutoAck(1);        
  radio.setRetries(0, 15);    
  radio.enableAckPayload();   
  radio.setPayloadSize(32);   

  radio.openReadingPipe(1, address[0]);  
  radio.setChannel(5);        

  radio.setPALevel (RF24_PA_MAX);   
  radio.setDataRate (RF24_250KBPS); 

  radio.powerUp();        
  radio.startListening();


}

void loop() {
  byte pipeNo;
  int bat = map(analogRead(an_pin), 0, 1023, 0, 100);
  while (radio.available(&pipeNo)) {        // слушаем эфир со всех труб
    radio.read(&rdata, sizeof(rdata));  // чиатем входящий сигнал

  }
  if (bat > 10) {
    digitalWrite(3, HIGH);
  }
  serv1.write(rdata[0]);
  serv2.write(rdata[1]);
  motor.writeMicroseconds(rdata[2]);
  Serial.println(rdata[2]);

}
