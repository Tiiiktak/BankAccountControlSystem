#include "CCreditAccount.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <iomanip>
using namespace std; 

//�Ƿ������ÿ�
int CCreditAccount::IsCard()
{
	return 1; 
}

//��Ƭ��ʼ��
void CCreditAccount::SetCard(double balance, string cardid, string pass, int day) 
{
	m_creditbalance = m_creditlimit = m_maxlimit = balance; 
	m_repaydate = day; 
	m_password = pass; 
	m_adnumber = cardid; 
	SaveCapitalFlow(0); 
}

//��Ƭ�˵�
void CCreditAccount::menu()
{
	int ch;
	while (1)
	{
		system("cls");
		cout << "\t=====CreditCard Account=====" << endl;
		cout << "\tTail number : " << NumberBack() << endl;
		cout << "\t1.Deposit        2.Withdrawl" << endl;
		cout << "\t3.Balance        4.Bill" << endl;
		cout << "\t5.Adjust         0.Back" << endl;
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
			AdjustBalance(); 
			break; 
		}
	}
}

//����
bool CCreditAccount::Deposit() 
{
	system("cls");
	double moneyoin;
	char ch;
	cout << "\tYour current Arrears: " << m_creditlimit - m_balance - m_creditbalance << endl;
	cout << "\tYour monthly repayment date is: " << m_repaydate << endl;
	cout << "\tPlease enter the deposit amount: ";
	cin >> moneyoin;
	cout << "\tYou will deposit " << moneyoin << " yuan (y/n)";
	cin >> ch;
	if (ch == 'n' || ch == 'N')
	{
		Back2Menu(1);
		return false;
	}
	if (m_creditlimit - m_creditbalance >= moneyoin)
	{
		//������С��Ƿ����
		m_creditbalance += moneyoin; 
	}
	else
	{
		//���������Ƿ����
		moneyoin -= (m_creditlimit - m_creditbalance);
		m_creditbalance = m_creditlimit; 
		m_balance += moneyoin; 
	}
	cout << "\t\tDeposit successfully" << endl;
	ShowBalance(0);
	SaveCapitalFlow(1, moneyoin); 
	cout << "\tSee Bill?(y/n) ";
	cin >> ch;
	if (ch == 'y' || ch == 'Y')
		PrintCapitalFlow();
	else
		Back2Menu(0);
	return true;
}

//ȡ��
bool CCreditAccount::Withdrawal() 
{
	system("cls");
	double moneyout, commission;
	char ch; 
	cout << "\tYour current available Credit Limit is: " << m_creditbalance + m_balance << "/" << m_creditlimit << endl;
	cout << "\tWe will charge 1% commission.(Minimum 10 yuan)" << endl;
	cout << "\tPlease enter the withdrawal amount: ";
	cin >> moneyout;
	commission = moneyout * 0.01; 
	if (commission < 10)
		commission = 10; 
	moneyout += commission; 
	if (moneyout > m_creditbalance + m_balance) //����
	{
		cout << "\t\tERROE! Insufficient Balance" << endl;
		ShowBalance(0);
		Back2Menu(0);
		return false;
	}
	cout << "\tYou will take out " << moneyout - commission << " yuan" << endl;
	cout << "\tService fee is " << commission << " yuan (y/n) "; 
	cin >> ch;
	if (ch == 'n' || ch == 'N') //�û���ֹ����
	{
		Back2Menu(1);
		return false;
	}
	if (CheckPassword()) //�˶�����
	{
		if (m_balance >= moneyout)
		{
			//ȡ����С���ֽ���
			m_balance -= moneyout; 
		}
		else
		{
			moneyout -= m_balance;
			m_balance = 0;
			m_creditbalance -= moneyout; 
		}
		cout << "\t\tSuccessful transaction" << endl;
		ShowBalance(0);
		SaveCapitalFlow(2, moneyout); 
		cout << "\tSee Bill?(y/n) ";
		cin >> ch;
		if (ch == 'y' || ch == 'Y')
			PrintCapitalFlow();
		else
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

//չʾ���
void CCreditAccount::ShowBalance(int k)
{
	if (k) //��k����,������,֮�󷵻ز˵�
		system("cls");
	cout << "\tCredit Limit: " << m_creditbalance + m_balance << "/" << m_creditlimit << endl;
	if (k)
		Back2Menu(0);
}

//�������
double CCreditAccount::GetBalance()
{
	return m_creditbalance + m_balance; 
}

//����
bool CCreditAccount::AdjustBalance() 
{
	system("cls");
	double newline; 
	char ch;
	cout << "\tYour current available Credit Limit is: " << m_creditbalance + m_balance << "/" << m_creditlimit << endl;
	while (1) 
	{
		cout << "\tYou can change the quote >=0.01 & <=" << m_maxlimit << endl;
		cout << "\tPlease enter the new quota: ";
		cin >> newline;
		if (newline >= 0.01 && newline <= m_maxlimit)
			break; 
		cout << "\tERROR! Please Try Again" << endl;
	}

	cout << "\tYou will change your quote to " << newline << " yuan(y/n)\n\t";
	cin >> ch;
	if (ch == 'n' || ch == 'N') //�û���ֹ����
	{
		Back2Menu(1);
		return false;
	}
	if (CheckPassword()) //�˶�����
	{
		double arr = m_creditlimit - m_creditbalance; 
		double tmp = m_creditbalance; 
		m_creditbalance = newline - arr; 
		m_creditlimit = newline;
		SaveCapitalFlow(3, newline - tmp);
		cout << "\t\tSuccessful change" << endl;
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

//������ˮ
bool CCreditAccount::SaveCapitalFlow(int k, double money)
{
	string filename = m_adnumber + ".txt";
	ofstream otfl; 
	if (k == 0)
	{
		ifstream infl(filename);
		infl >> m_opendate;
		infl.close();
		otfl.open(filename);
	}
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
		otfl << "Credit  " << m_adnumber << endl;
		otfl << setfill(' ') << setw(8) << "date" << setfill(' ') << setw(10) << "in";
		otfl << setfill(' ') << setw(10) << "out" << setfill(' ') << setw(10) << "Total";
		otfl << setfill(' ') << setw(10) << "Balance" << endl; 
	}
	//ʱ��
	otfl << 1900 + ltm->tm_year << setfill('0') << setw(2) << 1 + ltm->tm_mon << setfill('0') << setw(2) << ltm->tm_mday;
	if (k == 0) //��ʼ��
	{
		otfl << "          " << "          " << setfill(' ') << setw(10) << m_creditbalance << setfill(' ') << setw(10) << m_creditlimit << endl;
	}
	else if (k == 1) //����
	{
		otfl << setfill(' ') << setw(10) << money << "          " << setfill(' ') << setw(10) << m_creditbalance + m_balance << setfill(' ') << setw(10) << m_creditlimit << endl;
	}
	else if (k == 2)//ȡ��
	{
		otfl << "          " << setfill(' ') << setw(10) << -1 * money << setfill(' ') << setw(10) << m_creditbalance + m_balance << setfill(' ') << setw(10) << m_creditlimit << endl;
	}
	else //����
	{
		otfl << setfill(' ') << setw(10) << "Adjust" << setfill(' ') << setw(10) << money << setfill(' ') << setw(10) << m_creditbalance + m_balance << setfill(' ') << setw(10) << m_creditlimit << endl;
	}
	otfl.close();

	return true;
}


CCreditAccount::CCreditAccount()
{
	m_accountsec = true;
	m_balance = 0;
	m_creditbalance = m_creditlimit = m_maxlimit = 0.01; 
	m_repaydate = 11;
}
