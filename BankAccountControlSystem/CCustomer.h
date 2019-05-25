#pragma once
#include "CAccount.h"
#include "CCreditAccount.h"
#include "CDebitAccount.h"
#include <vector>
using namespace std; 

class CCustomer
{	
private:
	string m_name; //����
	string m_id; //���֤
	string m_phone; //�ֻ�
	int m_cards; //��Ƭ����
	double m_assets; //���ʲ�
	double m_creditassets; //�ܿ������ö�ȣ�ÿ�ſ���Ȳ�ͬ������ƽ��
	vector<CAccount*> m_accounts; //��Ƭ����
	bool m_havecredit; //�Ƿ������ÿ�
	void ShowProfile(); //��ʾ������Ϣ
	void ShowCards(); //չʾ��Ƭ
	void reFresh(); //�ڷ��ز˵�ʱˢ���ʲ�����Ƭ���������ö��
	void ShowAssets(); //��ѯ����ӡ�ʲ�
	void ShowCreditAssets(); //��ѯ����ӡ���ö��
	void Back2Menu(int k); //���ز˵���Ч
public:
	void menu(); //�ͻ����˹������
	void NewAccount(CAccount* ac); //�����¿�Ƭ
	string GetName(); //���ؿͻ�����
	double GetCreditAssets(); //�������Ŷ��
	void SetCustomer(string name, string id, string phone); //�ͻ���ʼ��

	CCustomer(); 
};

