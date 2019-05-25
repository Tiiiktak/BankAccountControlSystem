#include "CAccount.h"
#include <Windows.h>
#include <cstdio>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <fstream>
using namespace std;

//密码核对
bool CAccount::CheckPassword() 
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

//账户初始化
void CAccount::SetCard(double balance, string cardid, string pass, int day)
{
	m_balance = balance; 
	m_password = pass; 
	m_adnumber = cardid; 
	SaveCapitalFlow(0); 
}

//卡片菜单
void CAccount::menu()
{
	int ch;
	while (1)
	{
		system("cls"); 
		cout << "\t =====Passbook Account=====" << endl;
		cout << "\tTail number : " << NumberBack() << endl; 
		cout << "\t1.Deposit        2.Withdrawl" << endl;
		cout << "\t3.Balance        4.Bill" << endl;
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
		}
	}
}

//存钱
bool CAccount::Deposit() 
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
	SaveCapitalFlow(1, moneyoin);
	cout << "\t\tDeposit successfully" << endl; 
	ShowBalance(0); 
	cout << "\tSee Bill?(y/n) "; 
	cin >> ch; 
	if (ch == 'y' || ch == 'Y')
		PrintCapitalFlow(); 
	else
		Back2Menu(0); 
	return true;
}

//取钱
bool CAccount::Withdrawal() 
{
	system("cls");
	double moneyout; 
	char ch; 
	cout << "\tPlease enter the withdrawal amount: "; 
	cin >> moneyout; 
	if (moneyout > m_balance) //余额不足
	{
		cout << "\t\tERROE! Insufficient Balance" << endl; 
		ShowBalance(0); 
		Back2Menu(0); 
		return false; 
	}
	cout << "\tYou will take out " << moneyout << " yuan (y/n)"; 
	cin >> ch;
	if (ch == 'n' || ch == 'N') //用户终止交易
	{
		Back2Menu(1);
		return false;
	}
	if (CheckPassword()) //核对密码
	{
		m_balance -= moneyout; 
		SaveCapitalFlow(2, moneyout);
		cout << "\t\tSuccessful transaction" << endl; 
		ShowBalance(0);
		cout << "\tSee Bill?(y/n) ";
		cin >> ch;
		if (ch == 'y' || ch == 'Y')
			PrintCapitalFlow();
		else
			Back2Menu(0); 
		return true; 
	}
	else //密码错误
	{
		cout << "\tTransaction has been terminated" << endl; 
		cout << "\tAccount has been frozen" << endl; 
		cout << "\tPlese tyr again 30 min later" << endl; 
		m_accountsec = false; 
		Back2Menu(0); 
		return false; 
	}
}

//查询并显示余额
void CAccount::ShowBalance(int k) 
{
	if (k) //若k非零,先清屏,之后返回菜单
		system("cls"); 
	cout << "\tAccount Balance :  " << m_balance << " yuan" << endl; 
	if (k)
		Back2Menu(0);  
}

//返回余额
double CAccount::GetBalance()
{
	return m_balance;
}

//卡号后四位
string CAccount::NumberBack() 
{
	string arr;
	for (int i = 12; i < 16; i++)
		arr += m_adnumber[i]; 
	return arr;
}

//保存流水
bool CAccount::SaveCapitalFlow(int k, double money)
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
		otfl << "Passbook  " << m_adnumber << endl;
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
	else //取出
	{
		otfl << "          " << setfill(' ') << setw(10) << -1 * money;
	}
	otfl << setfill(' ') << setw(10) << m_balance << endl;
	otfl.close(); 

	return true;
}

//打印流水
bool CAccount::PrintCapitalFlow() 
{
	system("cls"); 
	string filename = m_adnumber + ".txt";
	ifstream infl(filename); 
	if (infl.fail())
	{
		cout << "\tERROR! fail to open file \"" << filename << "\"" << endl;
		return false;	
	}
	cout << "\t\t=====BILL=====" << endl; 
	string str; 
	while (!infl.eof())
	{
		getline(infl, str);
		cout << "\t" << str << endl; 
	}
	infl.close(); 
	cout << "\tEnter any key to back. "; 
	char ch; 
	cin >> ch; 
	Back2Menu(0); 
	return true;
}

//回菜单
void CAccount::Back2Menu(int k) 
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

//不是信用卡
bool CAccount::IsCredit()
{
	return false;
}


CAccount::CAccount()
{
	m_accountsec = true; 
	m_balance = 0; 
}


CAccount::~CAccount()
{
}
