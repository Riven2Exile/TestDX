
#include "stdafx.h"
#include "GameMain.h"
#include "DrawFlow.h"
#include "TextureMgr.h"
#include "CMSprite.h"
#include "GUI\cGuiControl.h"
#include "gui\cGuiForm.h"
#include "GUI\cGuiMgr.h"
#include "gui\cGuiButton.h"
#include "Spec\TestLogicDlg.h"
#include "GUI\Manager\GuiLayoutFileMgr.h"
#include "GUI\Manager\RegisterGui.h"
#include "LuaMgr.h"
#include "Tetris\TetrisWorld.h"
#include "Camera.h"
#include "UIEditorHelper\UIEditorHelper.h"
#include "GUI\Text\TextInterface.h"
#include "GUI\cGuiText.h"
#include "GUI\cCommonGuiHead.h"


extern IDirect3DDevice9 *g_pDevice;
extern CCamera g_camera;

///// д����������
iSprite* CreateSprite(SpriteType nType)
{
    if(ST_MX == nType)
    {
        return new CSprite;
    }
    else if (ST_3D == nType)
    {
        return new CMSprite;
    }

    return NULL;

}

// ����ʹ��,,,��Ϊ���಻֪������Ĵ�С...ÿ�ζ����ƶ�4...
iSprite* CreateSprite(SpriteType nType, unsigned int nSize)
{
    if (ST_MX == nType)
    {
        return new CSprite[nSize];
    }
    else if (ST_3D == nType)
    {
        return new CMSprite[nSize];
    }

    return NULL;
}




CGameMain::CGameMain() : _gui(cGuiMgr::Instance())
{
    

   
}

CGameMain::~CGameMain()
{

}






void CGameMain::init()
{
	LuaMgr::Instance().Init();
	LuaMgr::Instance().Test();

    _gui.Init();

    m_pTest = CreateSprite(/*ST_3D*/ ST_MX);

	m_SpriteWhiteCube = CreateSprite(/*ST_3D*/ ST_MX);
	m_SpriteWhiteCube->LoadAImage("", g_pDevice);
	m_SpriteWhiteCube->setTexture(NULL);
	m_SpriteWhiteCube->SetColor(0xffffffff);
	m_SpriteWhiteCube->setWidth(36);
	m_SpriteWhiteCube->setHeight(36);
	m_SpriteWhiteCube->SetX(40);

    for (int i = 0; i < TEST_SIZE; ++i)
    {
        m_sp[i] = CreateSprite(ST_MX);
    }

    srand(time(NULL));  //��������

    //m_test.Clip();

	// һЩ����
	
// 	byte a = 0x41;
// 	byte a2[2] = {0x80, 0x41};
// 	printf("%s  %s \n", &a, a2);


    //// ����һЩ����..
    CTextureMgr& T = CTextureMgr::instance();
	T.addTexture("MyRes/empty.png", "empty");
    T.addTexture("MyRes/0016.tga", "m1");
    T.addTexture("MyRes/0017.tga", "m2");
    T.addTexture("MyRes/0018.tga", "m3");
    T.addTexture("MyRes/0019.tga", "m4");
    T.addTexture("MyRes/0020.tga", "m5");
    T.addTexture("MyRes/0021.tga", "m6");
    T.addTexture("MyRes/0022.tga", "m7");
    T.addTexture("MyRes/0023.tga", "m8");   

    T.addTexture("MyRes/SpinningPeas.png", "greenHead");    //��ͷ
    T.addTexture("MyRes/hammerMan.jpg", "hammerMan");   //���� //���� ������

    T.addTexture("MyRes/Riven_Splash_0.jpg", "Riven");  //����

    T.addTexture("MyRes/moxia.jpg", "moxia"); //ħ��

    T.addTexture("MyRes/0020�ر�1.tga", "close1");//�رհ�ť
    T.addTexture("MyRes/0021�ر�2.tga", "close2");
    T.addTexture("MyRes/0022�ر�3.tga", "close3");
    T.addTexture("MyRes/0023�ر�4.tga", "close4");
    T.addTexture("MyRes/��ʾ�����.tga", "dlg"); //�Ի������
    T.addTexture("MyRes/0113��������.tga", "lable1");  
    T.addTexture("MyRes/+1.tga", "+1");
    T.addTexture("MyRes/+2.tga", "+2");
    T.addTexture("MyRes/+3.tga", "+3");
    T.addTexture("MyRes/+4.tga", "+4");
    T.addTexture("MyRes/-1.tga", "-1");
    T.addTexture("MyRes/-2.tga", "-2");
    T.addTexture("MyRes/-3.tga", "-3");
    T.addTexture("MyRes/-4.tga", "-4");
    T.addTexture("MyRes/0605��Ѫ����.tga", "pB");
    T.addTexture("MyRes/0607��Ѫ����.tga", "pF");

    T.addTexture("MyRes/cube.tga", "cube");
    T.addTexture("MyRes/cubeBlend.tga", "cubeBlend");

	T.addTexture("MyRes/font_kai.bmp", "font_kai");	// ��������

	T.addTexture("MyRes/scroll_btn_down1.tga", "scroll_btn_down1");// ������
	T.addTexture("MyRes/scroll_btn_down2.tga", "scroll_btn_down2");
	T.addTexture("MyRes/scroll_btn_down3.tga", "scroll_btn_down3");
	T.addTexture("MyRes/scroll_btn_down4.tga", "scroll_btn_down4");
	T.addTexture("MyRes/scroll_btn_up1.tga", "scroll_btn_up1");
	T.addTexture("MyRes/scroll_btn_up2.tga", "scroll_btn_up2");
	T.addTexture("MyRes/scroll_btn_up3.tga", "scroll_btn_up3");
	T.addTexture("MyRes/scroll_btn_up4.tga", "scroll_btn_up4");
	T.addTexture("MyRes/scroll_btn_mid1.tga", "scroll_btn_mid1");
	T.addTexture("MyRes/scroll_btn_mid2.tga", "scroll_btn_mid2");
	T.addTexture("MyRes/scroll_btn_mid3.tga", "scroll_btn_mid3");
	T.addTexture("MyRes/scroll_btn_mid4.tga", "scroll_btn_mid4");
	T.addTexture("MyRes/slide_btn.tga", "slide_btn");
	T.addTexture("MyRes/slide_bar.tga", "slide_bar");
	T.addTexture("MyRes/slide_background.tga", "slide_background");


	m_SpriteWhiteCube->setTexture(T.getTexture("greenHead"));

    // �������� end
    m_pTest->LoadAImage("", g_pDevice);
    m_pTest->setTexture(T.getTexture( "moxia"/*"Riven"*/));
    m_pTest->setWidth(1024);
    m_pTest->setHeight(768); //��������Ļ
	m_pTest->setVisible(false);
    // //     m_test.SetX(100.f);
    // //     m_test.SetY(200.f);
    //     m_pTest->setStretchX(0.8f);
    //     m_pTest->setStretchY(0.8f);
	//m_pTest->setTextureU1(0.5f);

    // ����
    initAnimation();

    const int perLine = 30; //ÿ�л�����

    for (int i = 0; i < TEST_SIZE; ++i)
    {
        //m_sp[i]->LoadImage("MyRes/SpinningPeas.png", g_pDevice);
        m_sp[i]->LoadAImage("", g_pDevice); //����������
        if(/*true*/ rand()%2)
        {
            m_sp[i]->setTexture(T.getTexture("greenHead"));
            m_sp[i]->setWidth(37);
            m_sp[i]->setHeight(37);
        }
        else
        {
            m_sp[i]->setTexture(T.getTexture("m8" /*"hammerMan"*/));
            m_sp[i]->setWidth(384/* 90*/);
            m_sp[i]->setHeight(384/*115*/);
        }

        m_sp[i]->SetX(i%perLine * 40);
        m_sp[i]->SetY(i/perLine * 20);

        //m_sp[i]->Clip();//���ü�
    }



    //// load gui config
    CRegisterGui one;

    //CGuiLayoutFileMgr::Instance().LoadAllLayoutFile();

    
    //
	m_pDlgTest = new CTestLogicDlg/*cGuiControl*/;
	m_pDlgTest->SetOffSet(250,250);
	//m_pDlgTest->SetPos(50, 50); // ������ӿؼ��Ļ������λ�þ���Ҫ���ϸ��ؼ���ƫ��
	m_pDlgTest->SetWidth(328);
	m_pDlgTest->SetHeight(232);
	m_pDlgTest->SetTexture("dlg");
	m_pDlgTest->Show(true);

    m_pCtrlTest = new cGuiButton(m_pDlgTest);
    m_pCtrlTest->SetOffSet(300, 10);
    m_pCtrlTest->SetWidth(27);
    m_pCtrlTest->SetHeight(27);
    //m_pCtrlTest->SetTexture("close1");
    m_pCtrlTest->SetID(110);
    m_pCtrlTest->SetBtnStateImage(cGuiButton::kBS_Normal, "close1");
    m_pCtrlTest->SetBtnStateImage(cGuiButton::kBS_MouseOn, "close2");
    m_pCtrlTest->SetBtnStateImage(cGuiButton::kBS_Clicked, "close3");
    m_pCtrlTest->SetBtnStateImage(cGuiButton::kBS_Disable, "close4");
    m_pCtrlTest->Show();

	cGuiProgress* pPro = new cGuiProgress(m_pDlgTest);
	pPro->SetOffSet(0, 0);
	//pPro->SetOffSet(100, 60);
	pPro->SetWidth(140);
	pPro->SetHeight(9);
	pPro->SetBackImage("pB");
	pPro->SetBarImage("pF");
	pPro->SetProgress(40);
	pPro->SetID(11000001);

    cGuiButton *pBtnTemp = new cGuiButton(m_pDlgTest);
    pBtnTemp->SetWidth(18);
    pBtnTemp->SetHeight(18);
    pBtnTemp->SetTexture("+1");
    pBtnTemp->SetBtnStateImage(cGuiButton::kBS_Normal, "+1");
    pBtnTemp->SetBtnStateImage(cGuiButton::kBS_MouseOn, "+2");
    pBtnTemp->SetBtnStateImage(cGuiButton::kBS_Clicked, "+3");
    pBtnTemp->SetBtnStateImage(cGuiButton::kBS_Disable, "+4");
    pBtnTemp->Show();
    //pBtnTemp->SetPos(100, 90);
	pBtnTemp->SetOffSet(100, 90);
    pBtnTemp->SetID(111);


    cGuiControl *pC = new cGuiLable(m_pDlgTest);
    pC->SetWidth(55);
    pC->SetHeight(24);
    pC->Show();
    pC->SetTexture("lable1");
    //pC->SetPos(185, 65);
	pC->SetOffSet(135, 15);
    FRECT fr;
    fr.left = 0.0f;
    fr.top = 0.0f;
    fr.right = 0.8f;
    fr.bottom = 1.0f;
    //pC->SetClip(fr);//�ü�test ��Bug�� (��Ӧ���ù̶�λ�����ü�, Ӧ��Ҫ�ðٷֱ�)
    
	cGuiText *pLable = new cGuiText(m_pDlgTest);
	pLable->SetText("test"); //����
	pLable->SetOffSet(0, 200);

	cGuiScroll *pScroll = new cGuiScroll(m_pDlgTest);	//������
	pScroll->SetScrollType(cGuiScroll::kST_Up_Down);
	pScroll->SetWidth(100);
	pScroll->SetHeight(112);
	pScroll->SetOffSet(0, 80);

	cGuiSlide *pSlide = new cGuiSlide(m_pDlgTest);	//����
	pSlide->SetOffSet(215, 100);

	cGuiList *pListGui = new cGuiList(m_pDlgTest);  //�б�
	pListGui->SetWidth(200);
	pListGui->SetHeight(100);
	stCustomCtrlPack pack;
	cGuiLable *pLableList1 = new cGuiLable(pListGui);
	pLableList1->SetTexture("close1"); //�����ͨ������õ���ߵĽӿ�~ 
	pLableList1->SetWidth(27);
	pLableList1->SetHeight(27);
	pack.listCtrl.push_back(pLableList1);
	pListGui->AddAListCtrl(pack);
	pack.listCtrl.clear();
	cGuiLable *pLableList2 = new cGuiLable(pListGui);
	pLableList2->SetTexture("close2");
	pLableList2->SetWidth(27);
	pLableList2->SetHeight(27);
	pack.listCtrl.push_back(pLableList2);
	pListGui->AddAListCtrl(pack);

	cGuiEdit *pEdit = new cGuiEdit(m_pDlgTest); // �༭��
	pEdit->SetWidth(200);
	pEdit->SetHeight(20);
	pEdit->SetOffSet(150,40);



	m_pDlgTest->AddControl(m_pCtrlTest);
	m_pDlgTest->AddControl(pPro);
	m_pDlgTest->AddControl(pBtnTemp);
	m_pDlgTest->AddControl(pC);
	m_pDlgTest->AddControl(pLable);
	m_pDlgTest->AddControl(pScroll);
	m_pDlgTest->AddControl(pSlide);
	m_pDlgTest->AddControl(pListGui);
	m_pDlgTest->AddControl(pEdit);


    // �Ի���2
    m_pCtrlDlg2 = new cGuiForm;
    m_pCtrlDlg2->SetOffSet(50, 50);
    m_pCtrlDlg2->SetWidth(328);
    m_pCtrlDlg2->SetHeight(232);
    m_pCtrlDlg2->SetTexture("dlg");
    m_pCtrlDlg2->Show(true);
    //m_pCtrlDlg2->SetDrag(false); //���ò����϶�

    _gui.AddCtrl(m_pDlgTest);    //�Ի�����������
    //_gui.AddCtrl(m_pCtrlDlg2);
    ((CTestLogicDlg*)m_pDlgTest)->Init();



    ////test
    _pTWorld = new /*Tetris::*/TetrisWorldView;
    
    _pTWorld->setCubeImage("cube"); //todo: ����view��Ҫ��һЩ����
    _pTWorld->setWCubeImage("cubeBlend");
    _pTWorld->setCubeSize(36);      //Ҫ��������Ŀ��!!
    _pTWorld->SetWorldSize(10, 20); //���м���
    //_pTWorld->setViewRect(0, 0, 36)
    _pTWorld->init();

    //_pTWorld->Start();              //��ʼ�߼� (����ע�ͼ���)



    ////// test UIEditor
    UIEditor::CUIEditorHelper uiHelper;
    uiHelper.GenFormatFile(m_pDlgTest);
	const char *p = typeid(m_pDlgTest).name();

	cGuiControl * pTP = uiHelper.GenFormFromFile();
	if (pTP)
	{
		pTP->SetTexture("dlg");
		pTP->Show();
		_gui.AddCtrl(pTP);
	}
}


void CGameMain::AddGui(cGuiControl* pCtrl)
{
    _gui.AddCtrl(pCtrl);
    //pCtrl->Show();
}

void CGameMain::update(DWORD elasped)
{
    
    ////TODO: ������Ϸ��һЩ�߼�
    m_pTest->Update();
	m_SpriteWhiteCube->Update();

    //m_pTest->SetColor(0xffff0000); //��ɫ����

    for (int i = 0; i < TEST_SIZE; ++i)
    {
        m_sp[i]->Update();
        //m_sp[i]->SetX(1 + m_sp[i]->GetX());
    }

    m_AniAuto.update(elasped);

    _gui.Update(elasped);
    //m_pDlgTest->Update();

    //test
    _pTWorld->run(elasped);
}


void CGameMain::draw()
{
    // todo: ��
    if (g_pDevice)
    {
        // ����ջ�������
        CDrawFlow::Instance().clear();

		Textinterface_ResetTextoutOneFrame();

        g_pDevice->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0xffaaaaaa, 1.0f, 0);

        g_pDevice->BeginScene();

        m_pTest->Draw(); //�� ����

		m_SpriteWhiteCube->Draw();
//         for (int i = 0; i < TEST_SIZE; ++i) //�� ��ͷ
//         {
//             m_sp[i]->Draw();
//         }

        //m_AniAuto.draw(); //����
        //m_pDlgTest->Draw();
        _gui.Draw();

        _pTWorld->draw();

		// ��������
		//test font;
		const char* pstr = "fly";
		TextOutput(0, 100, pstr);
		TextOutput(10, 120, "t");
 		TextOutput(0, 200, "����");


        CDrawFlow::Instance().draw(); //������

        

        g_pDevice->EndScene();
        g_pDevice->Present(0,0,0,0);
    }
    
}




////// ��Ϣ���...
void CGameMain::OnLButtonUp(const WPARAM& wParam, const LPARAM& lParam)
{
    

    int x = LOWORD(lParam);
    int y = HIWORD(lParam);

	if (_gui.OnLButtonUp(x, y, (eMouseKeyStateMask)wParam) == 0)
    {

    }
    else
    {
       
    }
}

void CGameMain::OnLButtonDown(const WPARAM& wParam, const LPARAM& lParam)
{
    int x = LOWORD(lParam);
    int y = HIWORD(lParam);

    if( _gui.OnLButtonDown(x, y, wParam) == 0)
    {

    }
    else
    {
        m_sp[0]->SetX( m_sp[0]->GetX() + 10);
    }
    //printf("CGameMain::OnLButtonDown\n"); //��һ��down, ֻ�ᷢһ����Ϣ
}

void CGameMain::OnRButtonDown(const WPARAM& wParam, const LPARAM& lParam)
{
    m_sp[0]->SetX( m_sp[0]->GetX() - 10 );
}

void CGameMain::OnRButtonUp(const WPARAM& wParam, const LPARAM& lParam)
{
    
}

void CGameMain::OnChar(const WPARAM& wParam, const LPARAM& lParam)
{
    ///// �ַ���ascii�� 
    printf("char: %c\n", wParam);
}

extern float g_light;
float fix = 0.05f;

extern float g_duibi;
float fixDui = 0.005f;

void CGameMain::OnKeyDown(const WPARAM& wParam, const LPARAM& lParam)
{
    printf("KD:  w:%d \n", wParam);

    if (VK_UP == wParam)
    {
        //������
        g_light = g_light + fix;
    }
    else if (VK_LEFT == wParam)
    {
        m_AniAuto.setX( m_AniAuto.getX() - 5 );
        g_duibi = g_duibi - fixDui; //�Աȶ�

        m_pDlgTest->AddAllOffset(-1, 0);
    }
    else if (VK_RIGHT == wParam)
    {
        m_AniAuto.setX( m_AniAuto.getX() + 5 );

        g_duibi = g_duibi + fixDui; //�Աȶ�

        m_pDlgTest->AddAllOffset(1, 0);
    }
    else if (VK_DOWN == wParam)
    {
        g_light = g_light - fix; //����
    }
    else if (0x41 == wParam) // A
    {
        if(_pTWorld) _pTWorld->PutACommand(kTC_Left);
    }
    else if (0x42 == wParam) // B
    {
        // ��z���������ƶ�
        D3DXVECTOR3 vec = g_camera.GetLocate();
        vec.z = vec.z + 0.01f;
        g_camera.SetLocate(vec);
        D3DXMATRIXA16 view1 = g_camera.GetLookAtMatrix();
        g_pDevice->SetTransform(D3DTS_VIEW, &view1);
    }
    else if (0x43 == wParam) // C
    {
        // ��z�Ḻ�����ƶ�
        D3DXVECTOR3 vec = g_camera.GetLocate();
        vec.z = vec.z - 0.01f;
        g_camera.SetLocate(vec);
        D3DXMATRIXA16 view1 = g_camera.GetLookAtMatrix();
        g_pDevice->SetTransform(D3DTS_VIEW, &view1);
    }
    else if (0x57 == wParam) // w
    {
        if(_pTWorld) _pTWorld->PutACommand(kTC_Up);
    }
    else if (0x44 == wParam) // d
    {
        if(_pTWorld) _pTWorld->PutACommand(kTC_Right);
    }
    else if (0x45 == wParam) // e
    {
        // �������ƶ�
        D3DXVECTOR3 vec = g_camera.GetLocate();
        vec.x = vec.x - 0.01f;
        g_camera.SetLocate(vec);
        D3DXMATRIXA16 view1 = g_camera.GetLookAtMatrix();
        g_pDevice->SetTransform(D3DTS_VIEW, &view1);
    }
    else if (0x46 == wParam) // f
    {
        // �������ƶ�
        D3DXVECTOR3 vec = g_camera.GetLocate();
        vec.x = vec.x + 0.01f;
        g_camera.SetLocate(vec);
        D3DXMATRIXA16 view1 = g_camera.GetLookAtMatrix();
        g_pDevice->SetTransform(D3DTS_VIEW, &view1);
    }
    else if (0x53 == wParam) // s
    {
        if(_pTWorld) _pTWorld->PutACommand(kTC_Down);
    }

    printf("g_light:%f  g_duibi:%f\n", g_light, g_duibi);
}

void CGameMain::OnKeyUP(const WPARAM& wParam, const LPARAM& lParam)
{
    // release key 
}

void CGameMain::OnMouseMove(const WPARAM& wParam, const LPARAM& lParam)
{
    int x = LOWORD(lParam);
    int y = HIWORD(lParam);
    /*printf("OnMouseMove (%d,%d)\n", x, y);*/ //���ڵ���Ļ����
//     if(MK_CONTROL == wParam)
//         printf("The CTRL key is down.\n");
//     else if(MK_LBUTTON == wParam)
//         printf("The left mouse button is down.\n");

	_gui.OnMouseMove(x, y, (eMouseKeyStateMask)wParam);
}

extern HWND g_hWnd;

void CGameMain::OnMouseWheel(const WPARAM& wParam, const LPARAM& lParam){
	int delta = GET_WHEEL_DELTA_WPARAM(wParam);
	eMouseKeyStateMask keyState = (eMouseKeyStateMask)GET_KEYSTATE_WPARAM(wParam);

	///// ������ڵ���Ļ����
	int x = GET_X_LPARAM(lParam);
	int y = GET_Y_LPARAM(lParam); //WHEEL_DELTA
	
	static POINT pos;
	pos.x = x;
	pos.y = y;
	::ScreenToClient(g_hWnd, &pos); ////--> ת��Ϊ�ͻ�������
	//printf("OnMouseWheel %d %d  (%d,%d) (%d,%d) \n", delta, keyState, x, y, pos.x, pos.y);
	_gui.OnMouseWheel(x, y, delta, keyState);
}

///////
void CGameMain::initAnimation()
{
    stFAnimation stFA;
    stFA.dwFrameTime = 100;
    stFA.ePlay = kAP_Loop;
    stFA.nStartFrame = 0;
    stFA.nTotalFrame = 8;
    for (int i = 1; i <= stFA.nTotalFrame; ++i)
    {
        char str[10];
        sprintf(str, "m%d", i);
        stFA.vecTex.push_back(str);
    }

    m_AniAuto.initWithA(stFA);
    m_AniAuto.setW(384);
    m_AniAuto.setH(384);
    m_AniAuto.start();
}