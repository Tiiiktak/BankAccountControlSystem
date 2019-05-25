#pragma once
#include "CCreditAccount.h"
#include "CDebitAccount.h"
#include "CCustomer.h"
#include <fstream>

class CBankAdmin
{
private:
	int m_customs; //客户人数
	int m_cards; //发卡数量
	vector<CCustomer*> m_customvec; //客户向量
	vector<string> m_cardids; //存储所发卡片卡号
	void menu(string adminid); //银行后台管理系统
	void CustomSystem(); //客户账户管理
	bool CreditCard(); //信用卡办理
	bool DebitCard(); //借记卡办理
	void CheckCardsNum(int k); //查询发卡数量
	void CheckCustNum(int k); //查询客户数量
	CCustomer* NewCustom(int p, string name = "000"); //新客户注册
	bool IsOurCard(string id, int k = 0); //查询是否为本行发卡
	void Back2Menu(int k); //返回动效
public:
	void starthere(); //身份选择菜单
	void initial(); //初始化
	CBankAdmin(); 
};

