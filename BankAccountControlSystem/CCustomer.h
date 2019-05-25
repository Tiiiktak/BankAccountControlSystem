#pragma once
#include "CAccount.h"
#include "CCreditAccount.h"
#include "CDebitAccount.h"
#include <vector>
using namespace std; 

class CCustomer
{	
private:
	string m_name; //姓名
	string m_id; //身份证
	string m_phone; //手机
	int m_cards; //卡片数量
	double m_assets; //总资产
	double m_creditassets; //总可用信用额度（每张卡额度不同，不调平）
	vector<CAccount*> m_accounts; //卡片向量
	bool m_havecredit; //是否有信用卡
	void ShowProfile(); //显示个人信息
	void ShowCards(); //展示卡片
	void reFresh(); //在返回菜单时刷新资产、卡片数量、信用额度
	void ShowAssets(); //查询并打印资产
	void ShowCreditAssets(); //查询并打印信用额度
	void Back2Menu(int k); //返回菜单动效
public:
	void menu(); //客户个人管理界面
	void NewAccount(CAccount* ac); //创建新卡片
	string GetName(); //返回客户姓名
	double GetCreditAssets(); //返回授信额度
	void SetCustomer(string name, string id, string phone); //客户初始化

	CCustomer(); 
};

