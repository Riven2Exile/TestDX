#include "stdafx.h"
#include "..\..\CSprite.h"
#include "..\..\TextureMgr.h"
#include <vector>

///// 不让外部访问的全局变量 static 
extern class IDirect3DDevice9 *g_pDevice;

unsigned int BKDRHash(const char *str);

////// 还可能跟字体相关,

int nWordNum = 0;  //记录一帧里面的字数
int Textinterface_nTextArraySize = 0;
int Textinterface_nTextIndex = 0;
int TextInterface_nIncrease = 100;
std::vector<iSprite*> Textinterface_vecText;


void TextInterface_InitText()
{
	
}

void Textinterface_ResetTextoutOneFrame()
{
	Textinterface_nTextIndex = 0;
	
	for (auto var : Textinterface_vecText)
	{
		var->setVisible(false);
	}
}


void TextOutput(const int& xT, const int &yT, const char* str)
{
	int nLen = strlen(str);
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
		iSprite *sp;

		if (Textinterface_nTextIndex < Textinterface_nTextArraySize)
		{
			sp = Textinterface_vecText[Textinterface_nTextIndex];
		}
		else
		{
			sp = new CSprite;
			sp->LoadAImage("", g_pDevice);
			Textinterface_vecText.push_back(sp);
			Textinterface_nTextArraySize = Textinterface_vecText.size();
		}

		
		sp->setTexture(pTex);
		sp->setVisible(true);

		++Textinterface_nTextIndex;

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
		sp->Draw();		// 3. 压入绘制流

		x_start += nRealWeight;
	}
	
}

