#include <wiringPi.h>
#include <iostream>
int main (void) {
int value= 0;
unsigned int prew =0;
unsigned int now = 0;
int Ddelay = 0;
wiringPiSetup();
pinMode(1, OUTPUT);
pinMode(4, INPUT);
for(;;){
		value = digitalRead(4);
		Ddelay=now-prew;
		if (4000-Ddelay < 0) {
                        Ddelay = 4000;
                }
		std::cout<<"Data: "<<value<< " Timer: "<<4000-Ddelay<<"\n";

		if (value == 1) {
			prew=millis();
		}
		
		now=millis();
		if(Ddelay < 4000){
			digitalWrite(1, HIGH);
		}
		
		if (Ddelay >= 4000) {
			digitalWrite(1, LOW);
			Ddelay = 0;
		}
    }
 return 0;
}
