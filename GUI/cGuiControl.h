#ifndef _L_GUICONTROL_H
#define _L_GUICONTROL_H

#include "..\TextureMgr.h"

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
    cGuiControl* FindControl(int id = -1);
    void SetFatherCtrl(cGuiControl* pCtrl);

    void Update();
    virtual void Draw();    //���������..

    virtual void Show(bool bShow = true);
    bool IsShow() { return _bShow; }

    void SetDrag(bool bDrag); //�����Ƿ�����϶�
    bool CanDrag();


    // �ж�
    virtual bool IsAt(const int& x, const int& y);


    // �ؼ���� (һ��ֻ���ڵ�һ��ؼ�.. ���Ի���)
    void MoveToFront(int id, bool bResort = false);


    ///// ��Ϣ���� // ����0 ..��ʾ��Ϣ���������´�����
    virtual int OnMouseMove(const int& x, const int& y, const unsigned int& nFlag ); // ����0 ..��ʾ��Ϣ���������´�����
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


protected:
	cGuiControl* _pFather;  //���ؼ�

private:
    // �������
    void Resort();

    bool _bShow;    //�Ƿ���ʾ
    bool _bDrag;    //�Ƿ���϶�

    
	typedef std::list<cGuiControl*> LIST_CTRL;
    std::list<cGuiControl*> _listCtrl; // �ӿؼ��б�


    unsigned int _id;
	
	int _offsetX; //�ֲ�����ϵ
	int _offsetY;

	// ֮�������Ҫ���ǿ�͸ߵ���ʹ�ñ�������¼

protected:
	std::string _strText;	//����
    ControlType _ctrlType;
	iSprite* _sprite; //����(������)
};



#endif