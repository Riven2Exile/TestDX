#ifndef _L_GUICONTROL_H
#define _L_GUICONTROL_H

#include "..\TextureMgr.h"

#include "Text\TextInterface.h"

///// 不管显示.. 只管数据
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
	kCT_GuiScroll	= 8,	//一般不直接创建
	kCT_GuiSlide	= 9,	//滑块
	kCT_GuiList		= 10,
	kCT_GuiContainer= 11,	//容器

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

    virtual void SetWidth(float fw);	//控件的宽高不应该是 精灵的宽高
    virtual void SetHeight(float fh);
	virtual int get_width();
	virtual int get_height();

    ControlType GetCtrlType();
    void SetCtrlType(ControlType type);

    //test裁剪
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
    virtual void Draw();    //加入绘制流..

    virtual void Show(bool bShow = true);
    bool IsShow() { return _bShow; }

    void SetDrag(bool bDrag); //设置是否可以拖动
    bool CanDrag();

	bool IsFocus();
	void SetFocus(bool b);

    // 判断
    virtual bool IsAt(const int& x, const int& y);


    // 控件层次 (一般只用在第一层控件.. 即对话框)
    void MoveToFront(int id, bool bResort = false);


    ///// 消息处理 // 返回0 ..表示消息不继续往下传递了
    virtual int OnMouseMove(const int& x, const int& y, const unsigned int& nFlag ); // 返回0 ..表示消息不继续往下传递了
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

	bool _bFocus; //是否焦点
	cGuiControl* _pFather;  //父控件
	int _offsetX; //局部坐标系
	int _offsetY;

private:
    // 层次排序
    void Resort();

    bool _bShow;    //是否显示
    bool _bDrag;    //是否可拖动

    
	typedef std::list<cGuiControl*> LIST_CTRL;
    std::list<cGuiControl*> _listCtrl; // 子控件列表


    unsigned int _id;
	
	

	// 之后可能需要考虑宽和高单独使用变量来记录

protected:
	std::string _strText;	//文字
    ControlType _ctrlType;
	iSprite* _sprite; //精灵(绘制用)
};



#endif