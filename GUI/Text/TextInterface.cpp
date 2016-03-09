#include "stdafx.h"
#include "..\..\CSprite.h"
#include "..\..\TextureMgr.h"

///// 不让外部访问的全局变量 static 
extern class IDirect3DDevice9 *g_pDevice;



void TextOutput(const int& xT, const int &yT, const char* str, const int& nLen)
{
	if (nLen <= 0 || NULL == str)
		return;


	// 1. 对str进行词汇的拆解成单个字,英文是单字节(宽度也减半),中文是双字节 (注意效率)
	static const byte low = 0xff;
	static const byte H = 0x80;
	int height = 24; //高度
	int weight = 12; //
	int x_start = xT; 

	// 2. 找到纹理位置和区域 (需要用到字体size)
	IDirect3DTexture9* pTex = CTextureMgr::instance().getTexture("font_kai");
	for (int i = 0; i < nLen; ++i)
	{
		CSprite *sp = new CSprite; // 先这样泄露
		sp->LoadAImage("", g_pDevice);
		sp->setTexture(pTex);

		byte b = (byte)str[i];
		int nRealWeight = height;
		if (b < 0xff)
		{
			nRealWeight = height / 2; //注意英文宽度是减半的
		}

		//设置纹理坐标
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
	

	// 3. 压入绘制流

}

