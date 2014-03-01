/*
LED Cloud
*/
#include <EEPROM.h>
#include <SPI.h>
#include <RF12B.h>
#include <rf_packet.h>

#define PAN_ID 12
#define FREQUENCY 433.0

int redPin = 5;
int greenPin = 6;
int bluePin = 9;

int r,g,b;
int _r,_g,_b;
 
void setup()
{
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  RF12.begin();
  RF12.setPanID(PAN_ID);
  RF12.setFrequency(FREQUENCY);
  _r = EEPROM.read(0);
  _g = EEPROM.read(1);
  _b = EEPROM.read(2);
  setColor(_r, _g, _b);
}
 
void loop()
{
  if (RF12.packetAvailable()) {
    RFPacket p = RF12.recvPacket();
    // Only print valid packets
    if (p.valid()) {
      if (p.readChar() == 'c') {
        r = p.readUint8();
        g = p.readUint8();
        b = p.readUint8();
        setColor(r, g, b); 
      }
    }
  }

}
 
void setColor(int red, int green, int blue)
{
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
  if (_r != red || _g != green || _b != blue) {
    EEPROM.write(0,red);
    EEPROM.write(1,green);
    EEPROM.write(2,blue);
  }
}
