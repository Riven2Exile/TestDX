#ifndef _TEST_LOGIC_H
#define _TEST_LOGIC_H

/////// 对应业务的控件id

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