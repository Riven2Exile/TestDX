
#include "UIEditorAtom.h"
#include "..\ToolLib\tinyXML\tinyxml.h"
#include "..\GUI\cGuiControl.h"



namespace UIEditor
{
    TiXmlElement* CUIAtom::Gen(TiXmlElement *pRoot, cGuiControl* pCtrl)
    {
        return 0;
    }

	bool CUIAtom::load(TiXmlElement* pEle, cGuiControl* &pCtrl){
		if (NULL == pEle)
			return false;


		const char* szTemp = NULL;

		

		szTemp = pEle->Attribute("id");
		if (szTemp) { pCtrl->SetID(atoi(szTemp)); }

		int x = 0, y = 0;
		if (szTemp = pEle->Attribute("x")) { x = atoi(szTemp); }
		if (szTemp = pEle->Attribute("y")) { y = atoi(szTemp); }
		pCtrl->SetPos(x, y);

		if (szTemp = pEle->Attribute("width")) { x = atoi(szTemp); }
		if (szTemp = pEle->Attribute("height")){ y = atoi(szTemp); }
		pCtrl->SetWidth(x);
		pCtrl->SetHeight(y);

		return true;
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
        pEle->SetAttribute("width", pCtrl->get_width());
		pEle->SetAttribute("height", pCtrl->get_height());

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
		pEle->SetAttribute("width", pCtrl->get_width());
		pEle->SetAttribute("height", pCtrl->get_height());
//         pEle->SetAttribute("width", pCtrl->GetSize().cx);
//         pEle->SetAttribute("height", pCtrl->GetSize().cy);

        pRoot->LinkEndChild(pEle);
        return pEle;
    }
	bool CUIAtomButton::load(TiXmlElement* pEle, cGuiControl* &pCtrl){
		__super::load(pEle, pCtrl);
		return true;
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