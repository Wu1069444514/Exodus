#include "sock.h"
#include <stdexcept>
#include <sys/types.h> 
using namespace std;


Sock::Sock()
{
	WORD sockVersion = MAKEWORD(2, 2);
	WSADATA data;
	if (WSAStartup(sockVersion, &data) != 0)
	{
		throw runtime_error("�׽��ֳ�ʼ��ʧ��\n");
	}

	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == -1)
	{
		throw runtime_error("�׽��ֳ�ʼ��ʧ��\n");
	}
}

bool Sock::connectSocket(const char * hostID, int port)
{
	server.sin_family = AF_INET;
	hp = gethostbyname(hostID);
	if (hp == (struct hostent *)0)
	{
		throw 0;// "�޷�����������";
		return false;
	}
	memcpy((char *)&server.sin_addr, (char *)hp->h_addr, hp->h_length);
	server.sin_port = htons(port);

	

	if (connect(sock, (sockaddr *)&server, sizeof server) == -1)
	{
		throw 1; // "�������޷�����";
		return false;
	}
	else
		return true;
}

void Sock::sendSocket(const char * s)
{
	send(sock, s, strlen(s), 0);
}

int Sock::recvSocket()
{
	memset(recvBuffer, 0, BUFSIZ);
	return recv(sock, recvBuffer, BUFSIZ, 0);
}

char * Sock::getRecvBuffer()
{
	return recvBuffer;
}


Sock::~Sock()
{
	closesocket(sock);
}

