#include "CDebitAccount.h"
#include <Windows.h>
#include <cstdio>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <fstream>

//¿¨Æ¬²Ëµ¥
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

void CDebitAccount::Interest()
{
	cout << "\t ====Financial management====" << endl;
	ShowBalance(0); 
	cout << "\tAnnualized interest rate: " << m_rate * 100 << "%" << endl;
	cout << "\t"
}
