#include "stdafx.h"
#include "TestCrash.h"


CTestCrash::CTestCrash(){

}

CTestCrash::~CTestCrash(){

}

void CTestCrash::set_crash(CrashType type)
{
	_type = type;

	// 空指针
	if (null_call_member_fun_with_no_var == _type){
		do_null_call_member_fun_with_no_var();
	}
	else if (null_call_member_fun == _type){
		do_null_call_member_fun();
	}
	else if (null_call_virtual_member_fun == _type) {
		do_null_call_virtual_member_fun();
	}
	// 数组越界访问
	else if (array_index_out_of == _type) {
		do_array_index_out_of();
	}
	else if (array_index_out_of_write == _type) {
		do_array_index_out_of_write();
	}
	else{
		printf("未定义执行!\n");
	}
}


void CTestCrash::Print(const char* sz){
	printf("%s\n", sz);
}

void CTestCrash::PrintType(){
	int n = _type;
	printf("%d\n", n);
}

void TestVirtual::Print(const char* sz)
{
	printf("TestVirtual::Print :%s\n", sz);
}


/////// 具体的各种崩
void CTestCrash::do_null_call_member_fun_with_no_var()
{
	CTestCrash *p = nullptr;
	p->Print("play a joy");
}

void CTestCrash::do_null_call_member_fun()
{
	CTestCrash *p = nullptr;
	p->PrintType();
}

void CTestCrash::do_null_call_virtual_member_fun()
{
	TestVirtual *p = nullptr;
	p->Print("help!");
}

void CTestCrash::do_array_index_out_of()
{
	TestVirtual *p = new TestVirtual; //堆
	p->_arr[3] = 4;

	delete p;

	//栈
	TestVirtual s;
	s._arr[3] = 4;
}

void CTestCrash::do_array_index_out_of_write()
{
	TestVirtual *pA = new TestVirtual[3];
	for (int i = 0; i < 10; ++i)
	{
		pA[0]._arr[i] = 4;
	}

	pA[1].Print("CTestCrash::do_array_index_out_of_write 2");
	delete[] pA;

	// 栈
	TestVirtual s[10];
	for (int i = 0; i < 10; ++i){
		s[0]._arr[i] = 4;
	}
}

