#pragma once
#include <string>
using namespace std; 

//存折,基础账户
class CAccount
{
protected:
	bool m_accountsec; //账户安全状态
	double m_balance; //账户余额
	string m_adnumber; //账号16位
	string m_password; //账号密码6位
	bool CheckPassword(); //核对密码
	virtual bool Deposit(); //存钱操作，含提示
	virtual bool Withdrawal(); //取钱操作，含提示
	virtual void ShowBalance(int k); //查询并显示余额
	virtual bool SaveCapitalFlow(int k, double money = 0); //保存流水在文件中
	bool PrintCapitalFlow(); //打印流水
	void Back2Menu(int k); //返回菜单动态效果
public:
	virtual void menu(); //卡片菜单
	string NumberBack(); //返回账户账号后四位数字
	virtual double GetBalance(); //返回账户余额
	virtual bool IsCredit(); //是否是信用卡
	virtual void SetCard(double balance, string cardid, string pass, int day = 11); //卡片初始化
	
	CAccount();
	~CAccount();
};

