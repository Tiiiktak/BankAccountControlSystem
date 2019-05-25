#include "CDebitAccount.h"
#include <Windows.h>
#include <cstdio>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <fstream>

//保存流水
bool CDebitAccount::SaveCapitalFlow(int k, double money)
{
	string filename = m_adnumber + ".txt";
	ofstream otfl;
	if (k == 0)
		otfl.open(filename);
	else
		otfl.open(filename, ios::app);

	if (otfl.fail())
	{
		cout << "\tERROR! fail to open file \"" << filename << "\"" << endl;
		return false;
	}
	time_t now = time(0);
	tm* ltm = localtime(&now);
	if (k == 0)
	{
		otfl << m_opendate << endl; 
		otfl << "Debit  " << m_adnumber << endl;
		otfl << setfill(' ') << setw(8) << "date" << setfill(' ') << setw(10) << "in";
		otfl << setfill(' ') << setw(10) << "out" << setfill(' ') << setw(10) << "Balance" << endl;
	}
	//时间
	otfl << 1900 + ltm->tm_year << setfill('0') << setw(2) << 1 + ltm->tm_mon << setfill('0') << setw(2) << ltm->tm_mday;
	if (k == 0) //初始化
	{
		otfl << setfill(' ') << setw(10) << m_balance << "          ";
	}
	else if (k == 1) //存入
	{
		otfl << setfill(' ') << setw(10) << money << "          ";
	}
	else if (k == 2)//取出
	{
		otfl << "          " << setfill(' ') << setw(10) << -1 * money;
	}
	else //利息取出
	{
		otfl << setfill(' ') << setw(10) << "insterest" << setfill(' ') << setw(10) << money;
	}
	otfl << setfill(' ') << setw(10) << m_balance << endl;
	otfl.close();

	return true;
}

//卡种
int CDebitAccount::IsCard()
{
	return 2; 
}

//卡片菜单
void CDebitAccount::menu()
{
	int ch;
	while (1)
	{
		system("cls");
		cout << "\t  =====Debit Account=====" << endl;
		cout << "\tTail number : " << NumberBack() << endl;
		cout << "\t1.Deposit        2.Withdrawl" << endl;
		cout << "\t3.Balance        4.Bill" << endl;
		cout << "\t5.Interest" << endl;
		cout << "\t0.Back" << endl;
		cout << "\t>>>";
		cin >> ch;
		switch (ch)
		{
		case 0:
			Back2Menu(0); 
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
		case 4:
			PrintCapitalFlow();
			break;
		case 5:
			Interest(); 
			break; 
		}
	}
}

//利息计算和提取
void CDebitAccount::Interest()
{
	system("cls"); 
	time_t now = time(NULL); 

	int days = difftime(now, m_opendate) / 86400;
	cout << "\t ====Financial management====" << endl;
	ShowBalance(0); 
	cout << "\tAnnualized interest rate: " << m_rate * 100 << "%" << endl;
	cout << "\t" << days << " days since opening an account" << endl;
	double expins = m_rate * m_balance; //一年预计收益
	double ins = expins * days / 365 + days % 365 / 365 * expins;
	m_insterest = (double)(((int)(ins * 100)) / 100);
	cout << "\tinterest receivable: " << m_insterest << "yuan" << endl;
	cout << "\tExtracted to balance?(y/n)"; 
	cout << "\n\t>>>";
	char key; 
	cin >> key; 
	if (key == 'y' || key == 'Y')
	{
		if (CheckPassword())
		{
			cout << "\tExtracted Successfully!" << endl;
			m_balance += m_insterest;
			SaveCapitalFlow(3, m_insterest);
			m_insterest = 0;
			m_opendate = now; 
			EditOpendate(); 
			ShowBalance(0); 
			Back2Menu(0); 
		}
	}else
		Back2Menu(0); 
}

CDebitAccount::CDebitAccount()
{
	m_rate = 0.0287; 
	m_insterest = 0; 
}
