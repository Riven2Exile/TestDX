#ifndef _UI_EDITOR_ATOM_H
#define _UI_EDITOR_ATOM_H

class TiXmlElement;
class cGuiControl;

namespace UIEditor
{

    // 每个控件对应一个 atom
    class CUIAtom
    {
    public:
        CUIAtom() {}
        virtual ~CUIAtom() {}
        virtual TiXmlElement* Gen(TiXmlElement *pRoot, cGuiControl* pCtrl) ; //普通属性
		virtual bool load(TiXmlElement* pEle, cGuiControl* &pCtrl); //从xml中加载
    };




    // 对话框
    class CUIAtomForm : public CUIAtom
    {
    public:

        virtual TiXmlElement* Gen(TiXmlElement *pRoot, cGuiControl* pCtrl);
        
    };


    //按钮
    class CUIAtomButton : public CUIAtom
    {
    public:
        virtual TiXmlElement* Gen(TiXmlElement *pRoot, cGuiControl* pCtrl);
		virtual bool load(TiXmlElement* pEle, cGuiControl* &pCtrl); //从xml中加载
    };


	//标签
	class CUIAtomLable : public CUIAtom
	{
	public:
		virtual TiXmlElement* Gen(TiXmlElement *pRoot, cGuiControl* pCtrl);
	};

	//进度条
	class CUIAtomProgress : public CUIAtom
	{
	public:
		virtual TiXmlElement* Gen(TiXmlElement *pRoot, cGuiControl* pCtrl);
	};






};



#endif