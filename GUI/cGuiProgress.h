#ifndef _L_GUIPROGRESS_H
#define _L_GUIPROGRESS_H

#include "cGuiControl.h"

class cGuiLable;

class cGuiProgress : public cGuiControl
{
public:
    enum {
        min_pos = 0,
        max_pos = 100,
    };
    explicit cGuiProgress(cGuiControl* pFather);
    virtual ~cGuiProgress();


    void SetProgress(unsigned int nPos); // [0-100]
    unsigned int GetProgress();  //��ý��� [0-100]

	virtual void SetWidth(float fw);
	virtual void SetHeight(float fh);

	//virtual void SetOffSet(const int& x, const int& y);

    void SetBarImage(const char* szName);
    void SetBackImage(const char* szName);


private:

    ///// ����Ԫ��
    //������ ��cGuiControl �����еĶ���
	cGuiLable* _pBack; //����
    //������
    cGuiLable* _pBar;

    unsigned int _nPos; //100��ֵ
    //todo: ��ֵ�ı�..
};

#endif