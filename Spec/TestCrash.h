/*
	测试各种崩溃


	空指针访问成员函数，
	空指针访问

*/


class CTestCrash
{
public:
	CTestCrash();
	virtual ~CTestCrash();


	enum CrashType{
		null_call_member_fun_with_no_var,	//空指针对象调用成员函数，且这个成员函数没有访问到自己的成员变量
		null_call_member_fun,				//空指针对象调用成员函数，且这个成员函数会访问到自己的成员变量
		null_visit_member_var,				//空指针对象访问自己的成员变量
		null_call_virtual_member_fun,		//空指针对象调用自己的虚函数
		array_index_out_of,					//数组越界
		array_index_out_of_write,			//数组越界，写坏了下一个元素
		wild_call_member_fun,				
		wild_visit_member_var,				//野指针对象访问成员变量
	};


	void set_crash(CrashType type);


	void Print(const char* sz);
	void PrintType();
private:


	////// 写各种崩溃的情况
	void do_null_call_member_fun_with_no_var(); 
	void do_null_call_member_fun();
	void do_null_visit_member_var();
	void do_null_call_virtual_member_fun();
	void do_array_index_out_of();
	void do_array_index_out_of_write();

	CrashType _type; //崩溃类型

};


class TestVirtual{
public:
	TestVirtual(){ _arr[0] = 0; _arr[1] = 0; }
	virtual void nothing(){}
	virtual void Print(const char* sz);

	int _arr[2];
};