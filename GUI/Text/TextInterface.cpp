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
	int x_start = xT; 

	// 2. �ҵ�����λ�ú����� (��Ҫ�õ�����size)
	IDirect3DTexture9* pTex = CTextureMgr::instance().getTexture("font_kai");
	for (int i = 0; i < nLen; ++i)
	{
		CSprite *sp = new CSprite; // ������й¶
		sp->LoadAImage("", g_pDevice);
		sp->setTexture(pTex);

		byte b = (byte)str[i];
		int nRealWeight = height;
		if (b < 0xff)
		{
			nRealWeight = height / 2; //ע��Ӣ�Ŀ���Ǽ����
		}

		//������������
		int y = str[i] / low;
		int x = str[i] % low;

		float tu1 = (x * nRealWeight) / float(low*height);
		float tu2 = (x * nRealWeight + nRealWeight) / float(low*height);

		float tv1 = y / (float)H;
		float tv2 = (y*height + height) / float(H*height);
		sp->setTextureU1(tu1);
		sp->setTextureU2(tu2);
		sp->setTextureV1(tv1);
		sp->setTextureV2(tv2);

		sp->SetX(x_start);
		sp->SetY(yT);
		sp->setWidth(nRealWeight);
		sp->setHeight(height);
		sp->SetColor(0xffffffff);
		sp->Update();
		sp->Draw();

		x_start += nRealWeight;
	}
	

	// 3. ѹ�������

}

