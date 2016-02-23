
#include "UIEditorAtom.h"
#include "..\ToolLib\tinyXML\tinyxml.h"
#include "..\GUI\cGuiControl.h"



namespace UIEditor
{
    TiXmlElement* CUIAtom::Gen(TiXmlElement *pRoot, cGuiControl* pCtrl)
    {
        return 0;
    }

    /////////// 对话框
    TiXmlElement* CUIAtomForm::Gen( TiXmlElement *pRoot, cGuiControl* pCtrl )
    {
        TiXmlElement *pEle = new TiXmlElement("dlg");
        pEle->SetAttribute("id", 1/*pCtrl->GetID()*/);
        pEle->SetAttribute("name", "Dlg1");
        pEle->SetAttribute("type", "GuiDialog");
        int x = 0, y = 0;
        pCtrl->GetPos(x, y);
        pEle->SetAttribute("x", x);
        pEle->SetAttribute("y", y);
//         pEle->SetAttribute("width", pCtrl->);
//         pEle->SetAttribute("height", pCtrl->GetSize().cy);

        pRoot->LinkEndChild(pEle);
        return pEle;
    }

	// ==========>>>>  按钮
    TiXmlElement* CUIAtomButton::Gen( TiXmlElement *pRoot, cGuiControl* pCtrl )
    {
        TiXmlElement *pEle = new TiXmlElement("Ctrl");
        pEle->SetAttribute("id", pCtrl->GetID());
        pEle->SetAttribute("name", "Ctrl1");
        pEle->SetAttribute("type", "GuiButton");
        int x = 0, y = 0;
        pCtrl->GetPos(x, y);
        pEle->SetAttribute("x", x);
        pEle->SetAttribute("y", y);
//         pEle->SetAttribute("width", pCtrl->GetSize().cx);
//         pEle->SetAttribute("height", pCtrl->GetSize().cy);

        pRoot->LinkEndChild(pEle);
        return pEle;
    }

	// ========>>>>>>> 标签
	TiXmlElement* CUIAtomLable::Gen(TiXmlElement *pRoot, cGuiControl* pCtrl)
	{
		TiXmlElement *pEle = new TiXmlElement("Ctrl");
		pEle->SetAttribute("id", pCtrl->GetID());
		pEle->SetAttribute("name", "Ctrl1");
		pEle->SetAttribute("type", "CGuiLable");
		int x = 0, y = 0;
		pCtrl->GetPos(x, y);
		pEle->SetAttribute("x", x);
		pEle->SetAttribute("y", y);
		pRoot->LinkEndChild(pEle);
		return pEle;
	}

	// ======= >>>>>>> 进度条
	TiXmlElement* CUIAtomProgress::Gen(TiXmlElement *pRoot, cGuiControl* pCtrl)
	{
		TiXmlElement *pEle = new TiXmlElement("Ctrl");
		pEle->SetAttribute("id", pCtrl->GetID());
		pEle->SetAttribute("name", "CtrlP");
		pEle->SetAttribute("type", "CGuiProgress");
		int x = 0, y = 0;
		pCtrl->GetPos(x, y);
		pEle->SetAttribute("x", x);
		pEle->SetAttribute("y", y);
		pRoot->LinkEndChild(pEle);
		return pEle;
	}
};