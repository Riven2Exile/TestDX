#ifndef _TEST_LOGIC_H
#define _TEST_LOGIC_H

/////// ��Ӧҵ��Ŀؼ�id

class cGuiButton;


class CTestLogicDlg : public cGuiForm
{
public:
	explicit CTestLogicDlg(cGuiControl* pFather);
    virtual ~CTestLogicDlg();

    void Init();

    void OnButtonClick(int id);

private:
    cGuiButton* _btn;
    cGuiButton* _btnAdd;
};


#endif