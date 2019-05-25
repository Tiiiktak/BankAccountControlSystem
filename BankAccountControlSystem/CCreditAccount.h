#pragma once
#include "CAccount.h"

//信用卡，派生自存折
class CCreditAccount :
	public CAccount
{
private:
	double m_creditbalance; //信用卡可用信用额度(实际可用=可用信用额度+用户充值金额)
	double m_creditlimit; //信用卡授权总额度
	double m_maxlimit; //最大可调额度(发卡时额度)
	int m_repaydate; //还款日
	bool Deposit(); //信用卡还款
	bool Withdrawal(); //信用卡取款
	void ShowBalance(int k); //查询并显示信用额度
	bool AdjustBalance(); //调整信用额度
	bool SaveCapitalFlow(int k, double money = 0); //保存流水在文件中
public:
	void menu(); //卡片菜单
	bool IsCredit(); //是否信用卡
	void SetCard(double balance, string cardid, string pass, int day = 11); //卡片初始化
	double GetBalance(); //返回信用额度
	
	CCreditAccount(); 
};

