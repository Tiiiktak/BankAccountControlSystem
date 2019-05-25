#pragma once
#include "CCreditAccount.h"
#include "CDebitAccount.h"
#include "CCustomer.h"
#include <fstream>

class CBankAdmin
{
private:
	int m_customs; //�ͻ�����
	int m_cards; //��������
	vector<CCustomer*> m_customvec; //�ͻ�����
	vector<string> m_cardids; //�洢������Ƭ����
	void menu(string adminid); //���к�̨����ϵͳ
	void CustomSystem(); //�ͻ��˻�����
	bool CreditCard(); //���ÿ�����
	bool DebitCard(); //��ǿ�����
	void CheckCardsNum(int k); //��ѯ��������
	void CheckCustNum(int k); //��ѯ�ͻ�����
	CCustomer* NewCustom(int p, string name = "000"); //�¿ͻ�ע��
	bool IsOurCard(string id, int k = 0); //��ѯ�Ƿ�Ϊ���з���
	void Back2Menu(int k); //���ض�Ч
public:
	void starthere(); //���ѡ��˵�
	void initial(); //��ʼ��
	CBankAdmin(); 
};

