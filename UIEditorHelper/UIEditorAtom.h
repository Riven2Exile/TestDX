#ifndef _UI_EDITOR_ATOM_H
#define _UI_EDITOR_ATOM_H

class TiXmlElement;
class cGuiControl;

namespace UIEditor
{

    // ÿ���ؼ���Ӧһ�� atom
    class CUIAtom
    {
    public:
        CUIAtom() {}
        virtual ~CUIAtom() {}
        virtual TiXmlElement* Gen(TiXmlElement *pRoot, cGuiControl* pCtrl) ;
    };




    // �Ի���
    class CUIAtomForm : public CUIAtom
    {
    public:

        virtual TiXmlElement* Gen(TiXmlElement *pRoot, cGuiControl* pCtrl);
        
    };


    //��ť
    class CUIAtomButton : public CUIAtom
    {
    public:
        virtual TiXmlElement* Gen(TiXmlElement *pRoot, cGuiControl* pCtrl);
    };


	//��ǩ
	class CUIAtomLable : public CUIAtom
	{
	public:
		virtual TiXmlElement* Gen(TiXmlElement *pRoot, cGuiControl* pCtrl);
	};

	//������
	class CUIAtomProgress : public CUIAtom
	{
	public:
		virtual TiXmlElement* Gen(TiXmlElement *pRoot, cGuiControl* pCtrl);
	};






};



#endif