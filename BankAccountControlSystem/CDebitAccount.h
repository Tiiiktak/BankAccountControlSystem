#pragma once
#include "CAccount.h"

//���
class CDebitAccount :
	public CAccount
{
private:
	double m_insterest; //��Ϣ
	double m_rate; //�껯����
public:
	void menu(); //�˵�
	void Interest(); //��Ϣ��ȡ��չʾ
};

