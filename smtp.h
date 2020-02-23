#pragma once
#include "sock.h"
#include"base64.h"
using namespace std;

class Mail      //smtpģ�鷢��ʱ���ṩһ��mail������Ϊ��Ҫ����Ϣ
{
public:
    string hostID;      //smtp��������ַ
    int port;      //�˿ں�
    string localName;      //������

    string username;      //�û���
    string password;      //����

	string mailFrom;//������
	string mailTo;//������

    string subject;      //����
    string content;      //����

	//��������ͷ�õ�����Ϣ
	string recv;//��ͷ���Ľ�����
	string cc;	//����
	string bcc;	//���ܳ���
};

class SendMail      //�ṩsmtp���ŷ���
{
public:
	bool sendMail(Mail my);

private:
    void sendAMail(Mail my);      //����һ����
    void checkError(int err);      //���
    string generateSimpleHead(Mail my);      //������ͷ
    int getResponseCode(Sock *mySock);      //���ܷ���������
};
