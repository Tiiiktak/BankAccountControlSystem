#include "CCustomer.h"
#include <iostream>
#include <iomanip>
#include <Windows.h>
using namespace std; 

//���ز˵���Ч
void CCustomer::Back2Menu(int k)
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

//ˢ�±���
void CCustomer::reFresh()
{
	double ass = 0, creass = 0; 
	int credflag = 0; 
	for (int i = 0; i < m_accounts.size(); i++)
	{
		if (m_accounts[i]->IsCard() == 1)
		{
			creass += m_accounts[i]->GetBalance();
			credflag = 1; 
		}
		else
			ass += m_accounts[i]->GetBalance(); 
	}
	m_cards = m_accounts.size(); 
	m_assets = ass; 
	m_creditassets = creass; 
	if (credflag)
		m_havecredit = true;
	else
		m_havecredit = false; 
}

//�ͻ����˲˵�
void CCustomer::menu()
{
	int ch; 
	while (1)
	{
		system("cls");
		cout << "\t=======My Account=======" << endl;
		cout << "\tHello, " << m_name << "!" << endl; 
		cout << "\t1.Cards         2.Assets" << endl;
		cout << "\t3.Creditassets  4.Profile" << endl;
		cout << "\t0.Back" << endl;
		cout << "\t>>>";
		cin >> ch; 
		switch (ch)
		{
		case 1:
			ShowCards(); 
			break; 
		case 2:
			ShowAssets(); 
			break;
		case 3:
			ShowCreditAssets(); 
			break;
		case 4:
			ShowProfile(); 
			break;
		default:
			return;
		}
		reFresh(); 
	}
}

//��ʾ������Ϣ
void CCustomer::ShowProfile()
{
	cout << "\t\t===ME===" << endl;
	cout << "\tName:" << m_name << endl; 
	cout << "\tID:" << m_id << endl;
	cout << "\tPhone:" << m_phone << endl;
	cout << "\tPress any key to back."; 
	char ch; 
	cin >> ch; 
	Back2Menu(0); 
}

//չʾ��Ƭ
void CCustomer::ShowCards()
{
	system("cls"); 
	cout << "\tYou have " << m_accounts.size() << " cards" << endl;
	cout << "\tHere are your cards" << endl;
	for (int i = 0; i < m_accounts.size(); i++)
	{
		cout << "\t" << i + 1 << ". ";
		CAccount* p = m_accounts[i];
		if (p->IsCard() == 1)
			cout << "Credit   ";
		else if (p->IsCard() == 2)
			cout << "Debit    ";
		else
			cout << "PassBook "; 
		cout << m_accounts[i]->NumberBack();
		cout << setfill(' ') << setw(10) << m_accounts[i]->GetBalance(); 
		cout << "yuan" << endl; 
	}
	cout << "\tEnter the card number you want to manage or 0 to back" << endl; 
	cout << "\t>>>"; 
	int ch; 
	cin >> ch; 
	if (ch > 0 && ch <= m_accounts.size())
		m_accounts[ch - 1]->menu();
	else
		cout << "\tERROR!Please Try again" << endl;
	Back2Menu(0); 
}

//�ͻ���ʼ��
void CCustomer::SetCustomer(string name, string id, string phone)
{
	m_name = name; 
	m_id = id; 
	m_phone = phone; 
}

//�¿�Ƭ����
void CCustomer::NewAccount(CAccount* ac)
{
	m_accounts.push_back(ac);
	m_cards++; 
	if (ac->IsCard() == 1)
	{
		m_havecredit = true;
		m_creditassets += ac->GetBalance(); 
	}
	else
	{
		m_assets += ac->GetBalance(); 
	}
}

//�ʲ�
void CCustomer::ShowAssets()
{
	system("cls");
	cout << "\tAssets : " << m_assets << " yuan" << endl;
	Back2Menu(0);
}

//���ö��
void CCustomer::ShowCreditAssets()
{
	system("cls");
	cout << "\tCredit Assets : " << m_creditassets << " yuan" << endl;
	Back2Menu(0);
}

//��������
std::string CCustomer::GetName()
{
	return m_name;
}

//���ض��
double CCustomer::GetCreditAssets()
{
	return m_creditassets; 
}

CCustomer::CCustomer()
{
	m_cards = 0;
	m_assets = 0;
	m_creditassets = 0;
	m_havecredit = false;
}
