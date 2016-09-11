
//#include "../stdafx.h"     ////����ֲ�Ժ���˵
/*#include <stdio.h>*/
#include "UIEditorHelper.h"
#include "..\GUI\cGuiControl.h"
#include "..\ToolLib\tinyXML\tinyxml.h"
#include "UIEditorAtom.h"
#include "..\GUI\cGuiForm.h"
#include "..\GUI\cGuiButton.h"
#include "..\GUI\cGuiProgress.h"
#include "..\GUI\cGuiLable.h"

namespace UIEditor{

CUIEditorHelper::CUIEditorHelper()
{
    m_atomUI[kCT_GuiForm]   = new CUIAtomForm;
    m_atomUI[kCT_GuiButton] = new CUIAtomButton;
	m_atomUI[kCT_GuiLable]  = new CUIAtomLable;
	m_atomUI[kCT_GuiProcess]= new CUIAtomProgress;
}

CUIEditorHelper::~CUIEditorHelper()
{

}

CUIAtom* CUIEditorHelper::GetAtom(ControlType t)
{
    std::map<ControlType, UIEditor::CUIAtom*>::iterator itr = m_atomUI.find(t);
    if (itr != m_atomUI.end())
    {
        return itr->second;
    }
    return NULL;
}


bool CUIEditorHelper::GenFormatFile(cGuiControl* pCtrl)
{

    ControlType etype = pCtrl->GetCtrlType();
    if(kCT_GuiForm != etype) return false;


    struct stObj{
        TiXmlElement* pRoot;
        CUIEditorHelper *pHelper;
        void operator=(const stObj &obj){
            pRoot = obj.pRoot;
            pHelper = obj.pHelper;
        }
        void DoSomething(cGuiControl *pCtrl){
            //TODO: ��� pCtrl�������ǶԻ���, �����������һ�� stObj���� �ݹ�֮
            ControlType t = pCtrl->GetCtrlType();
            if (CUIAtom* pAtom = pHelper->GetAtom(t))
            {
                pAtom->Gen(pRoot, pCtrl);
                if (kCT_GuiForm == t)
                {
                    stObj foo;
                    foo = *this;
                    pCtrl->ForEachCtrl(foo);
                }
            }
            
        }
    };

    TiXmlDocument *pDoc = new TiXmlDocument; //xml�ļ�

    stObj obj;

    // file head
    obj.pRoot = new TiXmlElement("liupr");
    obj.pHelper = this;
    pDoc->LinkEndChild(obj.pRoot);

    // ������
    do 
    {
        if (CUIAtom* pAtom = GetAtom(pCtrl->GetCtrlType()))
        {
            obj.pRoot = pAtom->Gen(obj.pRoot, pCtrl);
        }
        pCtrl->ForEachCtrl(obj);
    } while (false);
    
    


	// fopen ����ʹ�����·�� ��������� ..\\UI\\young.xml
	if(pDoc->SaveFile("D:/young.xml") == false){
        printf("obj.pDoc->SaveFile false\n");
    }

    delete pDoc;


    return true;
}


cGuiControl* CUIEditorHelper::GenFormFromFile()
{
	TiXmlDocument *pDoc = new TiXmlDocument; //xml�ļ�
	pDoc->LoadFile("D:/young.xml");

	//Todo �����ļ�..����Ctrl
	TiXmlElement* pEleRoot = pDoc->RootElement(); //ͷ���Ԫ�� 
	const char *pStr = pEleRoot->Value();	// liupr
	TiXmlElement* pChildren = pEleRoot->FirstChildElement();

	cGuiControl *pCtrl = NULL;// = new cGuiForm(NULL);
	return doGenFormFromFile(pChildren, pCtrl);
}

void CUIEditorHelper::set_normal_attr(TiXmlElement* pEle, cGuiControl* &pCtrl)
{
	const char* s_name = NULL;
	if (s_name = pEle->Attribute("id")){ pCtrl->SetID(atoi(s_name)); }
	int x = 0, y = 0;
	if (s_name = pEle->Attribute("x")) { x = atoi(s_name); }
	if (s_name = pEle->Attribute("y")) { y = atoi(s_name); }
	pCtrl->SetPos(x, y);

	if (s_name = pEle->Attribute("type")){
		for (int i = 0; i < kCT_Num; ++i) {
			if (strcmp(s_name, sssssss[i]) == 0) {
				pCtrl->SetCtrlType((ControlType)i);
				break;
			}
		}
	}
}

cGuiControl* CUIEditorHelper::doGenFormFromFile(TiXmlElement* pEle, cGuiControl* &pCtrl)
{
	// ���������
	cGuiControl *pSubCtrl = NULL;
	const char* ctrl_type = NULL;
	//��ȷ������
	if (ctrl_type = pEle->Attribute("type")){ //�ؼ����� ?
		for (int i = 0; i < kCT_Num; ++i) {
			if (strcmp(ctrl_type, sssssss[i]) == 0) {
				pSubCtrl = CreateCtrl((ControlType)i, pCtrl);
				pSubCtrl->SetCtrlType((ControlType)i);

				break;
			}
		}
	}

	if (NULL == pSubCtrl){
		return pSubCtrl;
	}
	CUIAtom* pAtom = GetAtom(pSubCtrl->GetCtrlType());
	if (pAtom){
		pAtom->load(pEle, pSubCtrl);
	}


	/// �������ѭ��֮�����ɾ�����ˣ� ֻ��Ϊ�˲���
	for (TiXmlAttribute* pAttr = pEle->FirstAttribute(); pAttr; pAttr = pAttr->Next())
	{
		printf("(%s:%s) ", pAttr->Name(), pAttr->Value());
		// key, name 
	}
	printf("\n");

	//pSubCtrl = CreateCtrl(); //�������һ�������ɿؼ�����׼ȷ
	// Todo:��������

	// �����Ƿ�����Ԫ��
	for (TiXmlElement* pSubEle = pEle->FirstChildElement(); pSubEle; pSubEle = pSubEle->NextSiblingElement())
	{
		doGenFormFromFile(pSubEle, pSubCtrl);
	}

	return pSubCtrl;
}

cGuiControl* CUIEditorHelper::CreateCtrl(ControlType ctrl_type, cGuiControl* pFather)
{
	switch (ctrl_type)
	{
	case kCT_GuiForm: return new cGuiForm(pFather);
	case kCT_GuiButton: return new cGuiButton(pFather);
	case kCT_GuiLable: return new cGuiLable(pFather);
	case kCT_GuiProcess: return new cGuiProgress(pFather);
	default:
		return NULL;
		break;
	}
	
}



}; //end namespace UIEditor