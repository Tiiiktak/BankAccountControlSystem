#include <iostream>
#include "CAccount.h"
#include "CCreditAccount.h"
#include "CBankAdmin.h"
using namespace std; 


int main()
{
	cout << "hello world" << endl; 
	CBankAdmin* admin = new CBankAdmin; 
	
	admin->starthere(); 

	/*CAccount test;
	test.SaveCapitalFlow(0);
	test.PrintCapitalFlow();*/
	return 0; 
}

