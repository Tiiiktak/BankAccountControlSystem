#pragma once
#include "CAccount.h"

//储蓄卡
class CDebitAccount :
	public CAccount
{
private:
	double m_insterest; //利息
	double m_rate; //年化利率
public:
	void menu(); //菜单
	void Interest(); //利息提取、展示
};

