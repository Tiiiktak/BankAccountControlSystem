#include "CAccount.h"
#include <Windows.h>
#include <iostream>
using namespace std;

bool CAccount::CheckPassword() //����˶�
{
	string pass;
	int f = 0, flag = 1; 
	while (flag == 1)
	{
		cout << "\tPlease enter the transaction password: ";
		cin >> pass; 
		if (pass != m_password)
		{
			f++;
			if (f == 4)
			{
				return false;
			}
			cout << "\tWRONG PASSWORD" << endl;
			cout << "\tPlease try again (" << f << "/3)" << endl;
			flag = 1; 
		}
		else
			flag = 0; 
	}	
	return true; 
}

void CAccount::menu()
{
	int ch;
	while (1)
	{
		system("cls"); 
		cout << "\t=====Passbook Account=====" << endl;
		cout << "\tTail number : ";
		for (int i = 0; i < 4; i++)
			cout << NumberBack()[i];
		cout << "\n\t1.Deposit        2.Withdrawl" << endl;
		cout << "\t3.Balance        4.Bill" << endl;
		cout << "\t0.Back" << endl;
		cout << "\t>>>"; 
		cin >> ch; 
		switch (ch)
		{
		case 0:
		case 4:
			return;
		case 1:
			Deposit(); 
			break;
		case 2:
			Withdrawal(); 
			break; 
		case 3:
			ShowBalance(1); 
			break; 
		}
	}
}

bool CAccount::Deposit() //��Ǯ
{
	system("cls");
	double moneyoin;
	char ch; 
	cout << "\tPlease enter the deposit amount: "; 
	cin >> moneyoin; 
	cout << "\tYou will deposit " << moneyoin << " yuan (y/n)"; 
	cin >> ch; 
	if (ch == 'n' || ch == 'N')
	{
		Back2Menu(1); 
		return false; 
	}
	m_balance += moneyoin; 
	cout << "\t\tDeposit successfully" << endl; 
	ShowBalance(0); 
	Back2Menu(0); 
	return true;
}

bool CAccount::Withdrawal() //ȡǮ
{
	system("cls");
	double moneyout; 
	char ch; 
	cout << "\tPlease enter the withdrawal amount: "; 
	cin >> moneyout; 
	if (moneyout > m_balance) //����
	{
		cout << "\t\tERROE! Insufficient Balance" << endl; 
		ShowBalance(0); 
		Back2Menu(0); 
		return false; 
	}
	cout << "\tYou will take out " << moneyout << " yuan (y/n)"; 
	cin >> ch;
	if (ch == 'n' || ch == 'N') //�û���ֹ����
	{
		Back2Menu(1);
		return false;
	}
	if (CheckPassword()) //�˶�����
	{
		m_balance -= moneyout; 
		cout << "\t\tSuccessful transaction" << endl; 
		ShowBalance(0); 
		Back2Menu(0); 
		return true; 
	}
	else //�������
	{
		cout << "\tTransaction has been terminated" << endl; 
		cout << "\tAccount has been frozen" << endl; 
		cout << "\tPlese tyr again 30 min later" << endl; 
		m_accountsec = false; 
		Back2Menu(0); 
		return false; 
	}
}

void CAccount::ShowBalance(int k) //�����
{
	if (k)
		system("cls"); 
	cout << "\tAccount Balance :  " << m_balance << " yuan" << endl; 
	if (k)
		Back2Menu(0); 
}

int* CAccount::NumberBack() //���ź���λ
{
	int arr[4]; 
	for (int i = 12; i < 16; i++)
		arr[i - 12] = m_adnumber[i]-'0'; 
	return arr;
}

void CAccount::Back2Menu(int k) //�ز˵�
{
	if (k)
		system("cls"); 
	cout << "\tloading"; 
	for (int i = 0; i < 100000000; i++)
	{
		if (i % 10000000 == 0) 
		{
			{
				cout << ".";
				Sleep(300);
			}
		}
	}
}

CAccount::CAccount()
{
	m_accountsec = true; 
	m_adnumber = "6220190507883625"; 
	m_balance = 235.4; 
	m_password = "123456"; 
}


CAccount::~CAccount()
{
}
