#include "stdafx.h"
#include "LineSprite.h"
#include "DrawFlow.h"
#include "CSprite.h"

enum { ding_num = 2 };

CLineSprite::CLineSprite()
{
	m_pSelfVertex = new VertexS[ding_num];
}

CLineSprite::~CLineSprite()
{

}

void CLineSprite::set_line(const int& x1, const int& y1, const int& x2, const int& y2)
{
	m_pSelfVertex[0].x = x1;
	m_pSelfVertex[0].y = y1;
	m_pSelfVertex[1].x = x2;
	m_pSelfVertex[1].y = y2;
}

void CLineSprite::set_color(const DWORD& c)
{
	m_pSelfVertex[0].color = c;
	m_pSelfVertex[1].color = c;
}

void CLineSprite::draw()
{
	stDrawCommand* pDraw = CDrawFlow::Instance().getFreeDrawFlow();
	if (pDraw)
	{
		pDraw->src_blend = D3DBLEND_SRCALPHA;
		pDraw->dest_blend = D3DBLEND_INVSRCALPHA;
		pDraw->pTexture = NULL;
		pDraw->shape = D3DPT_LINELIST;
		pDraw->vFormat = VertexS::FVF;
		pDraw->nCount = ding_num;
		pDraw->pVecBuf = m_pSelfVertex;

		CDrawFlow::Instance().increaseIndex();
	}
}

