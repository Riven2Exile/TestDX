#include "stdafx.h"
#include "..\..\CSprite.h"
#include "..\..\TextureMgr.h"
#include <vector>

///// �����ⲿ���ʵ�ȫ�ֱ��� static 
extern class IDirect3DDevice9 *g_pDevice;

unsigned int BKDRHash(const char *str);

////// �����ܸ��������,

int nWordNum = 0;  //��¼һ֡���������
int Textinterface_nTextArraySize = 0;
int Textinterface_nTextIndex = 0;
int TextInterface_nIncrease = 100;
std::vector<iSprite*> Textinterface_vecText;

DWORD g_font_color = 0xffffffff;

void TextInterface_InitText()
{
	
}

void TextSetColorNext(const DWORD& dw){
	g_font_color = dw;
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
	// 1. ��str���дʻ�Ĳ��ɵ�����,Ӣ���ǵ��ֽ�(���Ҳ����),������˫�ֽ� (ע��Ч��)
	static const byte low = 0xff;
	static const byte H = 0x80;
	static const int x_edge = 1;
	static const int y_edge = 0;
	int height = 12; //�߶�
	int weight = 12; //
	int x_start = xT; 

	// 2. �ҵ�����λ�ú����� (��Ҫ�õ�����size)
	IDirect3DTexture9* pTex = CTextureMgr::instance().getTexture("font_kai");
	bool b_english = true;
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
		int nRealWeight = weight;
		if (b < H)
		{
			nRealWeight = weight / 2; //ע��Ӣ�Ŀ���Ǽ����
			b_english = true;
		}
		else{
			nRealWeight = weight; //����
			b_english = false;
		}

		//������������
		int y = 0;
		int x = 0; 
		int fix = 0;
		if (b_english)
		{
			y = str[i] / low;
			x = str[i];
			fix = 2;
		}
		else
		{
			y = str[i] - 0x7f;
			x = str[i+1] + 1;
			++i;
		}
		

		static float bitmap_width = float(low*weight + x_edge * 2); //λͼ���

		float tu1 = (x * nRealWeight + x_edge + fix) / bitmap_width;
		float tu2 = (x * nRealWeight + nRealWeight + x_edge + fix) / bitmap_width;

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
		sp->SetColor(g_font_color);
		sp->Update();
		sp->Draw();		// 3. ѹ�������

		x_start += nRealWeight;
	}
	
}

