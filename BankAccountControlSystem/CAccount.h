#pragma once
#include <string>

//����,�����˻�
class CAccount
{
protected:
	bool m_accountsec; //�˻���ȫ״̬
	double m_balance; //�˻����
	std::string m_adnumber; //�˺�16λ
	std::string m_password; //�����˺�����6λ
	bool CheckPassword(); //�˶�����
public:
	virtual void menu(); 
	virtual bool Deposit(); //��Ǯ����������ʾ
	virtual bool Withdrawal(); //ȡǮ����������ʾ
	virtual void ShowBalance(int k); //�����
	int* NumberBack(); //�����˻��˺ź���λ,ָ������
	bool SaveCapitalFlow(); //������ˮ���ļ���
	bool PrintCapitalFlow(); //��ӡ��ˮ
	void Back2Menu(int k); //���ض�Ч
	
	CAccount();
	~CAccount();
};

