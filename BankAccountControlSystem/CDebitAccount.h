#pragma once
#include "CAccount.h"

//���
class CDebitAccount :
	public CAccount
{
private:
	double m_insterest; //��Ϣ
	double m_rate; //�껯����
	virtual bool SaveCapitalFlow(int k, double money = 0); //������ˮ���ļ���
public:
	int IsCard(); 
	void menu(); //�˵�
	void Interest(); //��Ϣ��ȡ��չʾ
	CDebitAccount(); 
};

