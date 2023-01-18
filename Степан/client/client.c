#include <wiringPi.h>

int main()
{
	int value= 0;
	unsigned int prew =0;
	unsigned int now = 0;
	int Ddelay = 0;
	wiringPiSetup();
	pinMode(1, OUTPUT);
	pinMode(4, INPUT);
	for(;;){
		value=digitalRead(4);
		Ddelay=now-prew;

		if(value == 1) {
			prew=millis();
		}
		
		now=millis();
		if(Ddelay < 8000){
			digitalWrite(1, HIGH);
		}
		
		if(Ddelay >= 8000) {
			digitalWrite(1, LOW);
		}
	}	
	return 0;
}
