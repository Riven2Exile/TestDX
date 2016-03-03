#include "stdafx.h"
#include "..\..\CSprite.h"
#include "..\..\TextureMgr.h"

///// �����ⲿ���ʵ�ȫ�ֱ��� static 
extern class IDirect3DDevice9 *g_pDevice;



void TextOutput(const int& xT, const int &yT, const char* str, const int& nLen)
{
	if (nLen <= 0 || NULL == str)
		return;


	// 1. ��str���дʻ�Ĳ��ɵ�����,Ӣ���ǵ��ֽ�(���Ҳ����),������˫�ֽ� (ע��Ч��)
	static const byte low = 0xff;
	static const byte H = 0x80;
	int height = 24; //�߶�
	int weight = 12; //

	// 2. �ҵ�����λ�ú����� (��Ҫ�õ�����size)
	IDirect3DTexture9* pTex = CTextureMgr::instance().getTexture("font_kai");
	for (int i = 0; i < nLen; ++i)
	{
		CSprite *sp = new CSprite; // ������й¶
		sp->LoadAImage("", g_pDevice);
		sp->setTexture(pTex);

		//������������
		int y = str[i] / low;
		int x = str[i] % low;

		float tu1 = (x * weight) / float(low*height);
		float tu2 = (x * weight + weight) / float(low*height); //ע��Ӣ�Ŀ���Ǽ����

		float tv1 = y / (float)H;
		float tv2 = (y*height + height) / float(H*height);
		sp->setTextureU1(tu1);
		sp->setTextureU2(tu2);
		sp->setTextureV1(tv1);
		sp->setTextureV2(tv2);

		sp->SetX(xT);
		sp->SetY(yT);
		sp->setWidth(weight);
		sp->setHeight(height);
		sp->SetColor(0xffffffff);
		sp->Update();
		sp->Draw();
	}
	

	// 3. ѹ�������

}

