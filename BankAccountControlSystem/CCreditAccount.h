#pragma once
#include "CAccount.h"

//���ÿ��������Դ���
class CCreditAccount :
	public CAccount
{
private:
	double m_creditbalance; //���ÿ��������ö��(ʵ�ʿ���=�������ö��+�û���ֵ���)
	double m_creditlimit; //���ÿ���Ȩ�ܶ��
	double m_maxlimit; //���ɵ����(����ʱ���)
	int m_repaydate; //������
	bool Deposit(); //���ÿ�����
	bool Withdrawal(); //���ÿ�ȡ��
	void ShowBalance(int k); //��ѯ����ʾ���ö��
	bool AdjustBalance(); //�������ö��
	bool SaveCapitalFlow(int k, double money = 0); //������ˮ���ļ���
public:
	void menu(); //��Ƭ�˵�
	bool IsCredit(); //�Ƿ����ÿ�
	void SetCard(double balance, string cardid, string pass, int day = 11); //��Ƭ��ʼ��
	double GetBalance(); //�������ö��
	
	CCreditAccount(); 
};

