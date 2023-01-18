#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <wiringPi.h>

int socketfd;
int connection;
const char* ip = "45.141.102.163";
in_port_t port = 20223;
int status = 1;

int checkStatus()
{
    char sendBuffer[3] = {'g','e','t'};
    send(socketfd, sendBuffer, sizeof(sendBuffer), 0);
    char recvBuffer;
    size_t size = recv(socketfd, &recvBuffer, sizeof(recvBuffer), 0);
    int flag = 0;
    if(recvBuffer == '1')
        flag = 1;
    return flag;
}

int main()
{
    socketfd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in socketAddress;
    socketAddress.sin_family = AF_INET;
    socketAddress.sin_port = htons(port);
    socketAddress.sin_addr.s_addr = inet_addr(ip);

    connection = connect(socketfd, (struct sockaddr*)&socketAddress, sizeof(socketAddress));
    if(connection < 0)
    {
        printf("No connection\n");
        return -1;
    }
	int prevCheck = millis();
	int value= 0;
	unsigned int prew =0;
	unsigned int now = 0;
	int Ddelay = 0;
	wiringPiSetup();
	pinMode(1, OUTPUT);
	pinMode(4, INPUT);
    while(1)
    {
        if(prevCheck - now > 500)
			status = checkStatus();
        if(status == 1)
		{
			value=digitalRead(4);
			Ddelay=now-prew;
			if(8000 - Ddelay < 0){
				Ddelay = 8000;
			}
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
    }
}
