#pragma once
#include <string>
using namespace std; 

//����,�����˻�
class CAccount
{
protected:
	bool m_accountsec; //�˻���ȫ״̬
	double m_balance; //�˻����
	string m_adnumber; //�˺�16λ
	string m_password; //�˺�����6λ
	bool CheckPassword(); //�˶�����
	virtual bool Deposit(); //��Ǯ����������ʾ
	virtual bool Withdrawal(); //ȡǮ����������ʾ
	virtual void ShowBalance(int k); //��ѯ����ʾ���
	virtual bool SaveCapitalFlow(int k, double money = 0); //������ˮ���ļ���
	bool PrintCapitalFlow(); //��ӡ��ˮ
	void Back2Menu(int k); //���ز˵���̬Ч��
public:
	virtual void menu(); //��Ƭ�˵�
	string NumberBack(); //�����˻��˺ź���λ����
	virtual double GetBalance(); //�����˻����
	virtual bool IsCredit(); //�Ƿ������ÿ�
	virtual void SetCard(double balance, string cardid, string pass, int day = 11); //��Ƭ��ʼ��
	
	CAccount();
	~CAccount();
};

