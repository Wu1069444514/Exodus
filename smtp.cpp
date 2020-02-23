#include "smtp.h"

bool SendMail::sendMail(Mail my)    //����һ���ʼ�
{
	try {
		cout << "���ڷ���......" << endl;
		sendAMail(my);
		cout << "���ͳɹ���" << endl;
		return true;
	}
	catch (int err)
	{
		cout << "����ʧ�ܡ�" << endl;
		cout << "������룺" << err << " " << endl;
		/*switch (err)
		{
		case 0:cout << "���� 0���޷�����������" << endl; break;
		case 1:cout << "���� 1���������޷�����" << endl; break;
		case 2:cout << "���� 2����������ʧ��" << endl; break;
		case 3:cout << "���� 3���ʺ�ʧ��" << endl; break;
		case 4:cout << "���� 4���޷���¼" << endl; break;
		case 5:cout << "���� 5���û�������" << endl; break;
		case 6:cout << "���� 6���û������������" << endl; break;
		case 7:cout << "���� 7�������˴���" << endl; break;
		case 8:cout << "���� 8���ռ��˵�ַ����" << endl; break;
		case 9:cout << "���� 9������������ʱ����" << endl; break;
		case 10:cout << "���� 10����������ʧ��" << endl; break;
		default:cout << "δ֪����" << endl; break;
		}*/
		return false;
	}
	
}

void SendMail::sendAMail(Mail my)
{
	Sock mysock;
    int resCode;        //��������
	if (mysock.connectSocket(my.hostID.c_str(), my.port) == false)
		throw 2;//��������ʧ��

	resCode = getResponseCode(&mysock);
	//cout << resCode << endl;

    string helo("HELO ");    //�ʺ�
	helo = helo + my.localName + "\r\n";
	mysock.sendSocket(helo.c_str());

	resCode = getResponseCode(&mysock);
	//cout << resCode << endl;
	checkError(resCode);

    string login("AUTH LOGIN\r\n");    //�����¼
	mysock.sendSocket(login.c_str());

	//cout << "login" << endl;
	resCode = getResponseCode(&mysock);
	//cout << resCode << endl;
	checkError(resCode);
	//if (resCode != 334)
		//throw 4;

	string usernameBase64=base64_encode(reinterpret_cast<const unsigned char*>(my.username.c_str()), my.username.length());
    mysock.sendSocket(usernameBase64.c_str());    //�û���
	mysock.sendSocket("\r\n");

	resCode = getResponseCode(&mysock);
	//cout << resCode << endl;
	checkError(resCode);
	//if (resCode != 334)
		//throw 5;

	string passwordBase64= base64_encode(reinterpret_cast<const unsigned char*>(my.password.c_str()), my.password.length());
    mysock.sendSocket(passwordBase64.c_str());        //����
	mysock.sendSocket("\r\n");

	resCode = getResponseCode(&mysock);
	//cout << resCode << endl;
	checkError(resCode);
	//if (resCode != 235)
		//throw 6;

    mysock.sendSocket("MAIL FROM:<");    //���ͷ�����
	mysock.sendSocket(my.mailFrom.c_str());
	mysock.sendSocket(">");
	mysock.sendSocket("\r\n");

	resCode = getResponseCode(&mysock);
	//cout << resCode << endl;
	checkError(resCode);
	//if (resCode != 250)
		//throw 7;

	mysock.sendSocket("RCPT TO:<");
    mysock.sendSocket(my.mailTo.c_str());    //�����ռ���
	mysock.sendSocket(">");
	mysock.sendSocket("\r\n");

	resCode = getResponseCode(&mysock);
	//cout << resCode << endl;
	checkError(resCode);
	//if (resCode != 250)
		//throw 8;

    mysock.sendSocket("DATA\r\n");    //��������

	resCode = getResponseCode(&mysock);
	//cout << resCode << endl;
	checkError(resCode);
	//if (resCode != 354)
		//throw 9;

    string all = generateSimpleHead(my);    //������ͷ
    all = all +"\r\n\r\n"+ my.content + "\r\n";

    mysock.sendSocket(all.c_str());    //��������
	mysock.sendSocket(".\r\n");

    resCode = getResponseCode(&mysock);
	//cout << resCode << endl;
	checkError(resCode);
	//if (resCode != 250)
		//throw 10;

    mysock.sendSocket("QUIT\r\n");    //�˳�

	resCode = getResponseCode(&mysock);
	//cout << resCode << endl;
	checkError(resCode);

}

void SendMail::checkError(int err)    //��������飬������
{
	switch (err)
	{
	case 420:
	case 421:
	case 422:
	case 431:
	case 432:
	case 441:
	case 442:
	case 446:
	case 449:
	case 450:
	case 451:
	case 452:
	case 465:
	case 471:
	case 500:
	case 502:
	case 503:
	case 504:
	case 505:
	case 510:
	case 511:
	case 512:
	case 513:
	case 523:
	case 530:
	case 541:
	case 544:
	case 550:
	case 552:
	case 553:
	case 554:
	case 571:throw err; break;
	default:break;
	}
}

string SendMail::generateSimpleHead(Mail my)    //������ͷ
{
	string from("From:");
	from = from + my.mailFrom + "\r\n";

	if (my.recv.empty())
		my.recv = my.mailTo;
	//Ĭ����mailto���ķ�����

	string to("TO:");
	to = to + my.recv + "\r\n";

	string cc("");
	if (!my.cc.empty())
	{
		cc = "Cc:" + my.cc + "\r\n";
	}

	string bcc("");
	if (!my.bcc.empty())
	{
		bcc = "Bcc:" + my.bcc + "\r\n";
	}

	string dat("");
	//������

	string subject("");
	if (!my.subject.empty())
	{
		subject = "Subject:" + my.subject + "\r\n";
	}

	return from + to + cc + bcc + dat + subject;
}

int SendMail::getResponseCode(Sock * mySock)
{
	mySock->recvSocket();
	char *result=mySock->getRecvBuffer();
	string res(result);
	//cout << res << endl;
	//system("PAUSE");
	return stoi(res.substr(0, 3), 0, 10);
	
}
