#ifndef _TEST_LOGIC_H
#define _TEST_LOGIC_H

/////// ��Ӧҵ��Ŀؼ�id

class cGuiButton;
class cGuiEdit;
class CTestCrash;

class CTestLogicDlg : public cGuiForm
{
public:
	explicit CTestLogicDlg(cGuiControl* pFather);
    virtual ~CTestLogicDlg();

    void Init();

	void OnButtonClick(cGuiButton *pBtn);
	

private:
	void OnEditComplate(cGuiControl*);

    cGuiButton* _btn;
    cGuiButton* _btnAdd;
	cGuiEdit* _edit_ctrl;


	CTestCrash *pTestCrash;
};


#endif