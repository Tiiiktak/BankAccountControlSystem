#pragma once
#include <string>

//存折,基础账户
class CAccount
{
protected:
	bool m_accountsec; //账户安全状态
	double m_balance; //账户余额
	std::string m_adnumber; //账号16位
	std::string m_password; //单个账号密码6位
	bool CheckPassword(); //核对密码
public:
	virtual void menu(); 
	virtual bool Deposit(); //存钱操作，含提示
	virtual bool Withdrawal(); //取钱操作，含提示
	virtual void ShowBalance(int k); //查余额
	int* NumberBack(); //返回账户账号后四位,指针类型
	bool SaveCapitalFlow(); //保存流水在文件中
	bool PrintCapitalFlow(); //打印流水
	void Back2Menu(int k); //返回动效
	
	CAccount();
	~CAccount();
};

