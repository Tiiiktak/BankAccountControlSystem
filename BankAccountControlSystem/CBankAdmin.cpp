#include "CBankAdmin.h"
#include <iostream>
#include <fstream>
#include <Windows.h>
using namespace std; 

//�Ƿ�Ϊ���п�
bool CBankAdmin::IsOurCard(string id, int k)
{
	system("cls"); 
	int flag = 0; 
	if (k == 1)
	{
		cout << "\t\t=====Card Check=====" << endl;
		cout << "\tEnter the Card id:\n\t";
		cin >> id; 
	}
	for (int i = 0; i < m_cardids.size(); i++)
	{
		if (m_cardids[i] == id)
			flag = 1; 
	}
	if (k)
	{
		if (flag == 0)
			cout << "\tSorry, We can't find it in our system." << endl;
		else
			cout << "\tThis is the card of our bank." << endl;
		Back2Menu(0); 
	}
	if (flag)
		return true; 
	else
		return false;
}

//�û�ϵͳ
void CBankAdmin::CustomSystem()
{
	int flag = -1; 
	string id; 
	cout << "\tEnter you Name: " << "\n\t";
	cin >> id; 
	for (int i = 0; i < m_customvec.size(); i++)
		if (m_customvec[i]->GetName() == id)
			flag = i; 
	if (flag == -1)
	{
		cout << "\tERROR! We can't find your id in our system" << endl;
		Back2Menu(0); 
	}
	else
	{
		CCustomer* custom = m_customvec[flag]; 
		custom->menu();
	}
}

//���˵������ѡ��
void CBankAdmin::starthere()
{
	int ch; 
	while (1)
	{
		system("cls"); 
		cout << "\t   ====== WELCOME IBBC ======" << endl;
		cout << "\t1.My Account      2.Admin System" << endl;
		cout << "\t3.Card Check" << endl;
		cout << "\t0.Quit" << endl;
		cout << "\t>>>";
		cin >> ch; 
		switch (ch)
		{
		case 1:
			CustomSystem(); 
			break; 
		case 2:
			menu("007"); 
			break; 
		case 3:
			IsOurCard("000", 1); 
			break; 
		case 0: 
			return; 
		}
	}
}

//ϵͳ��ʼ��
void CBankAdmin::initial()
{
	//����ͻ��б���Ϣ
	ifstream infl("initialization.txt"); 
	string str, id, name, phone; 
	int i = 0; 
	CCustomer* tmp = NULL;
	while (infl >> str)
	{
		i %= 3;
		if (i == 0)
		{
			tmp = new CCustomer; 
			name = str; 
		}
		else if (i == 1)
		{
			id = str; 
		}
		else
		{
			phone = str;
			tmp->SetCustomer(name, id, phone);
			m_customvec.push_back(tmp);
			m_customs++;
		}
		i++; 
	}
	infl.close(); 

	//���룬ÿ���ͻ����ʲ���Ϣ
	infl.open("customersini.txt"); 
	int num, k; 
	double balance;
	string pass; 
	CAccount* tp = NULL;
	for (int j = 0; j < m_customs; j++)
	{
		infl >> num; 
		for (int s = 0; s < num; s++)
		{
			infl >> k >> id >> pass >> balance; 
			if (k == 0)
			{
				tp = new CAccount; 
				tp->initial(balance, id, pass); 
			}
			else if (k == 1)
			{
				tp = new CCreditAccount;
				tp->initial(balance, id, pass); 
			}
			else
			{
				tp = new CDebitAccount; 
				tp->initial(balance, id, pass); 
			}
			m_cardids.push_back(id); 
			m_cards++;
			m_customvec[j]->NewAccount(tp);
		}
	}
	infl.close(); 
}

//admin�˵�
void CBankAdmin::menu(string adminid)
{
	int ch;
	while (1)
	{
		system("cls");
		cout << "\t   =====IBBC Admin System=====" << endl;
		cout << "\tWelcome, id " << adminid << endl;
		cout << "\t1.Credit Card        2.Debit Card" << endl;
		cout << "\t3.Customer Num       4.Card Num" << endl;
		cout << "\t5.Register           6.Refresh" << endl;
		cout << "\t0.Back" << endl;
		cout << "\t>>>";
		cin >> ch;
		switch (ch)
		{
		case 0:
			return;
		case 1:
			CreditCard(); 
			break;
		case 2:
			DebitCard();
			break;
		case 3:
			CheckCustNum(1); 
			break;
		case 4:
			CheckCardsNum(1); 
			break;
		case 6:
			Refreshfile();
			break;
		case 5:
			CCustomer* tmp = NULL;
			tmp = NewCustom(0); 
			m_customvec.push_back(tmp); 
			break;  
		}
	}
}

//�¿ͻ�ע��
CCustomer* CBankAdmin::NewCustom(int p, string name)
{
	if (p == 0)
	{
		system("cls"); 
		cout << "\t======Account Register======" << endl;
		cout << "\tcustomer's name: "; 
		cin >> name; 
	}
	string id, phone; 
	cout << "\tHello," << name << "!" << endl;
	while (1)
	{
		cout << "\tPlease enter your identity number" << endl << "\t>>>";
		cin >> id; 
		if (id.length() == 18)
			break;
		else
			cout << "\tERROR! Please Try Again!" << endl; 
	}
	while (1)
	{
		cout << "\tPlease enter your mobile phone number" << endl << "\t>>>";
		cin >> phone; 
		if (phone.length() == 11)
			break; 
		else
			cout << "\tERROR! Please Try Again!" << endl;
	}
	CCustomer* tmp = new CCustomer; 
	tmp->SetCustomer(name, id, phone); 
	m_customs++; 
	if (p == 0)
	{
		cout << "\tRegister successfully!" << endl;
		Back2Menu(0); 
	}
	return tmp; 
}

//���ÿ�����
bool CBankAdmin::CreditCard()
{
	system("cls");
	string name;
	int flag = -1;
	cout << "\t======Credit Card Apply======" << endl;
	//�ͻ�����
	cout << "\tcustomer's name: ";
	cin >> name;
	//�ڹ˿������в����Ƿ����Ѵ��ڹ˿�
	for (int i = 0; i < m_customvec.size(); i++)
	{
		if (m_customvec[i]->GetName() == name)
		{
			flag = i;
			break;
		}
	}
	CCustomer* custom;
	//�������û�
	if (flag == -1)
	{
		custom = NewCustom(1, name);
	}
	else
		custom = m_customvec[flag];
	//���Ŷ��
	double creditline;
	char ch;
	cout << "\tHello, manager" << endl;
	while (1)
	{
		cout << "\tEnter the credit line: ";
		cin >> creditline;
		cout << "\tThe Credit Line is " << creditline << " (y/n) ";
		cin >> ch;
		if (ch == 'y' || ch == 'Y')
			break;
	}

	//����
	string cardid; 
	while (1)
	{
		cout << "\tSet Card number: " << "\n\t";
		cin >> cardid;
		if (cardid.length() == 16)
		{
			int flag = 1;
			
			if (IsOurCard(cardid))
				flag = 0;	
			for (int i = 0; i < 16; i++)
			{
				if (cardid[i] < '0' || cardid[i] > '9')
				{
					flag = 0; 
					break; 
				}
			}		
			if (flag)
				break; 
		}
		else
			cout << "\tERROR! Try Again" << endl; 
	}
	m_cardids.push_back(cardid);

	//������
	int day; 
	while (1)
	{
		cout << "\tSet Repay day of per month: ";
		cin >> day; 
		if (day > 0 && day < 28)
			break;
		else
			cout << "\tERROR! Try Again" << endl;
	}

	//��������
	string password1, password2; 
	while (1)
	{
		while (1)
		{
			cout << "\tSet PassWord(6 numbers): ";
			cin >> password1;
			if (password1.length() == 6)
			{
				int flag = 1;
				for (int i = 0; i < 6; i++)
					if (password1[i] < '0' || password1[i] > '9')
						flag = 0;
				if (flag == 1)
				{
					break;
				}
				//cout << "\tERROE! Please Try Again" << endl;
			}
			cout << "\tERROE! Please Try Again" << endl;
		}

		cout << "\n\tPlease enter password again: ";
		cin >> password2;
		if (password1 == password2)
			break;
		else
			cout << "\tERROE! Please Try Again" << endl;
		
	}

	//����
	CAccount* card = new CCreditAccount; 

	//��Ƭ��ʼ��
	card->SetCard(creditline, cardid, password1, day);
	
	custom->NewAccount(card); 
	
	if (flag == -1)
		m_customvec.push_back(custom); 
	cout << "\n\tSuccessfully Apply" << endl; 
	Back2Menu(0); 
	m_cards++; 
	return true; 
}

//��ǿ�����
bool CBankAdmin::DebitCard()
{
	system("cls");
	string name;
	int flag = -1;
	cout << "\t======Debit Card Apply======" << endl;
	//�ͻ�����
	cout << "\tcustomer's name: ";
	cin >> name;
	//�ڹ˿������в����Ƿ����Ѵ��ڹ˿�
	for (int i = 0; i < m_customvec.size(); i++)
	{
		if (m_customvec[i]->GetName() == name)
		{
			flag = i;
			break;
		}
	}
	CCustomer* custom;
	//�������û�
	if (flag == -1)
	{
		custom = NewCustom(1, name);
	}
	else
		custom = m_customvec[flag];

	//����
	string cardid;
	while (1)
	{
		cout << "\tSet Card number: " << "\n\t";
		cin >> cardid;
		if (cardid.length() == 16)
		{
			int flag = 1;

			if (IsOurCard(cardid))
				flag = 0;
			for (int i = 0; i < 16; i++)
			{
				if (cardid[i] < '0' || cardid[i] > '9')
				{
					flag = 0;
					break;
				}
			}
			if (flag)
				break;
		}
		else
			cout << "\tERROR! Try Again" << endl;
	}
	m_cardids.push_back(cardid);

	//��������
	string password1, password2;
	while (1)
	{
		while (1)
		{
			cout << "\tSet PassWord(6 numbers): ";
			cin >> password1;
			if (password1.length() == 6)
			{
				int flag = 1;
				for (int i = 0; i < 6; i++)
					if (password1[i] < '0' || password1[i] > '9')
						flag = 0;
				if (flag == 1)
				{
					break;
				}
				//cout << "\tERROE! Please Try Again" << endl;
			}
			cout << "\tERROE! Please Try Again" << endl;
		}

		cout << "\n\tPlease enter password again: ";
		cin >> password2;
		if (password1 == password2)
			break;
		else
			cout << "\tERROE! Please Try Again" << endl;

	}

	//����
	CAccount* card = new CDebitAccount;

	//��Ƭ��ʼ��
	card->SetCard(0, cardid, password1); 

	custom->NewAccount(card);

	if (flag == -1)
		m_customvec.push_back(custom);
	cout << "\n\tSuccessfully Apply" << endl;
	Back2Menu(0);
	m_cards++;
	return true;
}

//��ѯ��������
void CBankAdmin::CheckCardsNum(int k)
{
	if (k)
		system("cls"); 
	cout << "\tA total of " << m_cards << " cards were processed." << endl; 
	if (k)
		Back2Menu(0); 
}

//��ѯ�ͻ�����
void CBankAdmin::CheckCustNum(int k)
{
	if (k)
		system("cls");
	cout << "\tA total of " << m_customs << " customers." << endl;
	if (k)
		Back2Menu(0);
}

//��Ч
void CBankAdmin::Back2Menu(int k)
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

//�ļ�ˢ��
void CBankAdmin::Refreshfile()
{
	string filename = "initialization.txt"; 
	ofstream otfl(filename); 
	for (int i = 0; i < m_customvec.size(); i++)
	{
		otfl << m_customvec[i]->GetName() << " " << m_customvec[i]->GetId();
		otfl << " " << m_customvec[i]->Getmobil() << endl;
		m_customvec[i]->ReFreshfile(i); 
	}
	otfl.close(); 
}

CBankAdmin::CBankAdmin()
{
	m_customs = 0;
	m_cards = 0; 
	initial(); 
}
