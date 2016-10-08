#ifndef _L_GUICONTROL_H
#define _L_GUICONTROL_H

#include "..\TextureMgr.h"

#include "Text\TextInterface.h"

///// ������ʾ.. ֻ������
#include <list>
#include "..\iSprite.h"
enum SpriteType;


enum ControlType{
    kCT_Undefine = -1, //
    kCT_GuiForm = 0,
    kCT_GuiLable    = 1,
    kCT_GuiButton   = 2,
    kCT_GuiProcess  = 3,
	kCT_GuiText		= 4,
	kCT_GuiRadio	= 5,
	kCT_GuiCheck	= 6,
	kCT_GuiEdit		= 7,
	kCT_GuiScroll	= 8,	//һ�㲻ֱ�Ӵ���
	kCT_GuiSlide	= 9,	//����
	kCT_GuiList		= 10,
	kCT_GuiContainer= 11,	//����

    kCT_Num,
};

static const char* sssssss[] = {
	"GuiDialog",
	"GuiLable",
	"GuiButton",
	"GuiProcess",
	"GuiText",
	"GuiRadio",
	"GuiCheck",
	"GuiEdit",
	"GuiScroll",
	"GuiSlide",
	"GuiList",
	"GuiContainer",
};

static int aTest[kCT_Num == (sizeof(sssssss) / sizeof(sssssss[0]))];


typedef unsigned int UINT;

class cGuiControl
{
public:
    explicit cGuiControl(cGuiControl *pFather);
    virtual ~cGuiControl();

    void SetPos(const int& x, const int& y);
    void GetPos(int& x, int& y);
	int GetScreenPosX();
	int GetScreenPosY();
	
	virtual void SetOffSet(const int& x, const int& y);
	void GetOffSet(int& x, int& y);
	void SetOffSetX(const int& x);
	void SetOffSetY(const int& y);
	int GetOffSetX() { return _offsetX; }
	int GetOffSetY() { return _offsetY; }

    void AddAllOffset(const int& x, const int& y);

    virtual void SetWidth(float fw);	//�ؼ��Ŀ�߲�Ӧ���� ����Ŀ��
    virtual void SetHeight(float fh);
	virtual int get_width();
	virtual int get_height();

    ControlType GetCtrlType();
    void SetCtrlType(ControlType type);

    //test�ü�
    void SetClip(FRECT &rc);
    


    void SetTexture(const char* szName);

    void SetAlpha(unsigned int al);
    unsigned int GetAlpha();

    void SetID(unsigned int id);
    unsigned int GetID(){
        return _id;
    }

    void AddControl(cGuiControl* pCtrl);
	bool DeleteControl(const int& ctrlid);
    cGuiControl* FindControl(int id = -1);
    void SetFatherCtrl(cGuiControl* pCtrl);

	void Update(const DWORD& dwElaspe);
    virtual void Draw();    //���������..

    virtual void Show(bool bShow = true);
    bool IsShow() { return _bShow; }

    void SetDrag(bool bDrag); //�����Ƿ�����϶�
    bool CanDrag();

	bool IsFocus();
	void SetFocus(bool b);

    // �ж�
    virtual bool IsAt(const int& x, const int& y);


    // �ؼ���� (һ��ֻ���ڵ�һ��ؼ�.. ���Ի���)
    void MoveToFront(int id, bool bResort = false);


    ///// ��Ϣ���� // ����0 ..��ʾ��Ϣ���������´�����
    virtual int OnMouseMove(const int& x, const int& y, const unsigned int& nFlag ); // ����0 ..��ʾ��Ϣ���������´�����
	virtual int OnMouseWheel(const int& x, const int& y, const int& delta, const enum eMouseKeyStateMask& state);
    virtual int OnLButtonUp(const int& x, const int& y, const unsigned int& nFlag);
    virtual int OnLButtonDown(const int& x, const int& y, const unsigned int& nFlag);


    template<typename T>
    void ForEachCtrl(T obj){
        for (std::list<cGuiControl*>::iterator itr = _listCtrl.begin();
            itr != _listCtrl.end();
            ++itr)
        {
            obj.DoSomething(*itr);
        }
    }

	cGuiControl* GetFather() { return _pFather; }

protected:
	virtual void run(const DWORD& dwElaspe) {}

	bool _bFocus; //�Ƿ񽹵�
	cGuiControl* _pFather;  //���ؼ�
	int _offsetX; //�ֲ�����ϵ
	int _offsetY;

private:
    // �������
    void Resort();

    bool _bShow;    //�Ƿ���ʾ
    bool _bDrag;    //�Ƿ���϶�

    
	typedef std::list<cGuiControl*> LIST_CTRL;
    std::list<cGuiControl*> _listCtrl; // �ӿؼ��б�


    unsigned int _id;
	
	

	// ֮�������Ҫ���ǿ�͸ߵ���ʹ�ñ�������¼

protected:
	std::string _strText;	//����
    ControlType _ctrlType;
	iSprite* _sprite; //����(������)
};



#endif