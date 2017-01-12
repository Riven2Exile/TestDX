/*
	���Ը��ֱ���


	��ָ����ʳ�Ա������
	��ָ�����

*/


class CTestCrash
{
public:
	CTestCrash();
	virtual ~CTestCrash();


	enum CrashType{
		null_call_member_fun_with_no_var,	//��ָ�������ó�Ա�������������Ա����û�з��ʵ��Լ��ĳ�Ա����
		null_call_member_fun,				//��ָ�������ó�Ա�������������Ա��������ʵ��Լ��ĳ�Ա����
		null_visit_member_var,				//��ָ���������Լ��ĳ�Ա����
		null_call_virtual_member_fun,		//��ָ���������Լ����麯��
		array_index_out_of,					//����Խ��
		array_index_out_of_write,			//����Խ�磬д������һ��Ԫ��
		wild_call_member_fun,				
		wild_visit_member_var,				//Ұָ�������ʳ�Ա����
	};


	void set_crash(CrashType type);


	void Print(const char* sz);
	void PrintType();
private:


	////// д���ֱ��������
	void do_null_call_member_fun_with_no_var(); 
	void do_null_call_member_fun();
	void do_null_visit_member_var();
	void do_null_call_virtual_member_fun();
	void do_array_index_out_of();
	void do_array_index_out_of_write();

	CrashType _type; //��������

};


class TestVirtual{
public:
	TestVirtual(){ _arr[0] = 0; _arr[1] = 0; }
	virtual void nothing(){}
	virtual void Print(const char* sz);

	int _arr[2];
};