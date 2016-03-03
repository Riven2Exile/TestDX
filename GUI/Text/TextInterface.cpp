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

	// 2. 找到纹理位置和区域 (需要用到字体size)
	IDirect3DTexture9* pTex = CTextureMgr::instance().getTexture("font_kai");
	for (int i = 0; i < nLen; ++i)
	{
		CSprite *sp = new CSprite; // 先这样泄露
		sp->LoadAImage("", g_pDevice);
		sp->setTexture(pTex);

		//设置纹理坐标
		int y = str[i] / low;
		int x = str[i] % low;

		float tu1 = (x * weight) / float(low*height);
		float tu2 = (x * weight + weight) / float(low*height); //注意英文宽度是减半的

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
	

	// 3. 压入绘制流

}

