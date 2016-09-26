

#include "stdafx.h"
#include "CSprite.h"
#include "DrawFlow.h"


const DWORD VertexS::FVF = D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1;


/*
    图元拓扑 从 D3DPT_TRIANGLESTRIP 改成  D3DPT_TRIANGLELIST -- >  是为了可以优化批次绘制
*/



CSprite::CSprite(): m_bVisible(true)
, m_x(0.0f)
, m_y(0.0f)
, m_z(0.0f)
, m_w(0.0f)
, m_h(0.0f)
, m_iw(0.0f)
, m_ih(0.0f)
, m_tl(0.0f)
, m_tt(0.0f)
, m_tr(1.0f)
, m_tb(1.0f)
, m_StretchX(1.0f)
, m_StretchY(1.0f)
, m_color(0xffffffff)
, m_bClip(false)
, m_pTexture(NULL)
, m_pVb(NULL)
, m_pTest(NULL)
{
    m_bDirty = false;
}

CSprite::~CSprite()
{

}




bool CSprite::LoadAImage(const char* pszName, IDirect3DDevice9* pDev)
{
    D3DXIMAGE_INFO info;
    D3DXGetImageInfoFromFileA(pszName, &info);

    //// 原来的 D3DUSAGE_DYNAMIC ， D3DPOOL_DEFAULT
    int usage = 0; D3DUSAGE_DYNAMIC;
    int pool = D3DPOOL_MANAGED; D3DPOOL_DEFAULT;

    HRESULT hr = D3DXCreateTextureFromFileExA(pDev, pszName, info.Width, info.Height, 
        info.MipLevels, usage, info.Format, (D3DPOOL)pool, D3DX_FILTER_NONE,  // D3DPOOL_DEFAULT才可行。。
        D3DX_FILTER_NONE, D3DCOLOR_ARGB(255,255,255,255), NULL, NULL, &m_pTexture);

    if (FAILED(hr) )
    {
        m_pTexture = NULL;
    }
	else{
		m_x = 0;
		m_y = 0;
		m_w = info.Width;
		m_h = info.Height;

		m_iw = info.Width;
		m_ih = info.Height;
	}
    

    int jie = 6;  // 4

    pDev->CreateVertexBuffer(jie*sizeof(VertexS),
        D3DUSAGE_WRITEONLY,
        VertexS::FVF,
        D3DPOOL_MANAGED,
        &m_pVb,
        0);

    

    m_reClip.left = 0.f;
    m_reClip.top = 0.f;
    m_reClip.right = 1.0f;
    m_reClip.bottom = 1.0f;

    m_StretchX = 1.0f;
    m_StretchY = 1.0f;


    VertexS *pVec;
    m_pVb->Lock(0, sizeof(VertexS)*jie, (void**)&pVec, 0);

    float fix = -0.5f;
    m_z = 0.f;

    m_color = 0xffffffff;

    /*   三角形带
        0   1

        2   3
    */
//     pVec[0] = VertexS(m_x + fix, m_y + fix, m_z, 1.0f, m_color, 0.0f, 0.0f);
//     pVec[1] = VertexS(m_x + (float)info.Width + fix, m_y + fix, m_z, 1.0f, m_color, 1.0f, 0.0f);
//     pVec[2] = VertexS(m_x + fix, m_y + (float)info.Height + fix, m_z, 1.0f, m_color, 0.0f, 1.0f);
// 
//     pVec[3] = VertexS(m_x + (float)info.Width + fix, m_y + (float)info.Height + fix, m_z, 1.0f, m_color, 1.0f, 1.0f);

    /*  三角形列表
        0   1/4

        2/3  5
    */
    pVec[0] = VertexS(m_x + fix, m_y + fix, m_z, 1.0f, m_color, 0.0f, 0.0f);
    pVec[1] = VertexS(m_x + (float)info.Width + fix, m_y + fix, m_z, 1.0f, m_color, 1.0f, 0.0f);
    pVec[2] = VertexS(m_x + fix, m_y + (float)info.Height + fix, m_z, 1.0f, m_color, 0.0f, 1.0f);

    pVec[3] = VertexS(m_x + fix, m_y + fix, m_z, 1.0f, m_color, 0.0f, 0.0f);
    pVec[4] = VertexS(m_x + (float)info.Width + fix, m_y + fix, m_z, 1.0f, m_color, 1.0f, 0.0f);
    pVec[5] = VertexS(m_x + (float)info.Width + fix, m_y + (float)info.Height + fix, m_z, 1.0f, m_color, 0.0f, 1.0f);



    m_pVb->Unlock();

	m_bDirty = true; //标记为脏

    return true;
}


void CSprite::SetX(float x){
    m_x = x;
    m_bDirty = true;
}

void CSprite::SetY(float y){
    m_y = y;
    m_bDirty = true;
}

// void CSprite::SetClipRect(FRECT& r)
// {
//     m_reClip = r;
//     m_bDirty = true;
// }


float CSprite::GetX()
{
    return m_x;
}

float CSprite::GetY()
{
    return m_y;
}

void CSprite::setWidth(float fw)
{
    m_w = fw;
    m_bDirty = true;
}
void CSprite::setHeight(float fh)
{
    m_h = fh;
    m_bDirty = true;
}


// FRECT CSprite::GetClipRect() const
// {
//     return m_reClip;
// }


void CSprite::SetColor(DWORD color)
{
    if (color == m_color)
    {
        return ;
    }

    m_color = color;
    m_bDirty = true;
}

DWORD CSprite::GetColor()
{
    return m_color;
}

void CSprite::SetAlpha(unsigned int al)
{
    if (GetAlpha() == al)
    {
        return ;
    }

    m_color = (m_color & 0x00ffffff) + (al << 24);
    m_bDirty = true;
}

unsigned int CSprite::GetAlpha()
{
    return m_color >> 24;
}
// 缩放
void CSprite::setStretchX(float x)
{
    m_StretchX = x;
    m_bDirty = true;
}

void CSprite::setStretchY(float y)
{
    m_StretchY = y;
    m_bDirty = true;
}

void CSprite::setTexture(IDirect3DTexture9* pTexture)
{
    m_pTexture = pTexture;
}

void CSprite::setTextureU1(const float& t){
	m_tl = t;
	m_bDirty = true;
}
void CSprite::setTextureU2(const float& t){
	m_tr = t;
	m_bDirty = true;
}
void CSprite::setTextureV1(const float& t){
	m_tt = t;
	m_bDirty = true;
}
void CSprite::setTextureV2(const float& t){
	m_tb = t;
	m_bDirty = true;
}

void CSprite::setClipRect(FRECT& cf)
{
    m_reClip = cf;
	m_bDirty = true;
}

bool CSprite::isClip()
{
    return m_bClip;
}
void CSprite::setClip(bool bClip)
{
    m_bClip = bClip;
}

bool CSprite::isVisible()
{
    return m_bVisible;
}

void CSprite::setVisible(bool bVisible /* = true */)
{
    m_bVisible = bVisible;
}

void CSprite::Update()
{
    if (m_bDirty)
    {
        VertexS *pVec;
        m_pVb->Lock(0, sizeof(VertexS)*6, (void**)&pVec, 0);

        float fix = -0.5f;

        /*   
        0 ++++ 1(4)
        +   +  +
        + +    +
        2(3)++ 5
        */
        // ask: 这里是通过几个栈变量
//         pVec[0] = VertexS(m_x*m_StretchX + fix, m_y*m_StretchY + fix, m_z, 1.0f, m_color, 0.0f, 0.0f);
//         pVec[1] = VertexS((m_x + m_w)*m_StretchX + fix, m_y*m_StretchY + fix, m_z, 1.0f, m_color, 1.0f, 0.0f);
//         pVec[2] = VertexS(m_x*m_StretchX + fix, (m_y + m_h)*m_StretchY + fix, m_z, 1.0f, m_color, 0.0f, 1.0f);
// 
//         pVec[3] = VertexS((m_x + m_w)*m_StretchX + fix, (m_y + m_h)*m_StretchY + fix, m_z, 1.0f, m_color, 1.0f, 1.0f);

        //顶点
        float f1 = m_x*m_StretchX + fix;
        float f2 = m_y*m_StretchY + fix;
        float f3 = (m_x + m_w)*m_StretchX + fix;
        float f4 = (m_y + m_h)*m_StretchY + fix;

        //纹理坐标

		// 用于裁剪
		float tl = m_tl /*0.0f*/; 
		float tr = m_tr /*1.0f*/;
		float tt = m_tt /*0.0f*/;
		float td = m_tb /*1.0f*/;


        // 最后再裁剪? (注意缩放)
        if (m_bClip)
        {
			float tf1 = f1;
			float tf2 = f2;
			float tf3 = f3;
			float tf4 = f4;
            //f1 = f1 < m_reClip.left ? m_reClip.left : f1;   //x Left
			if (m_reClip.left > 0.0f)
			{
				f1 = tf1*(1.0f+m_reClip.left);
				tl = m_reClip.left;
			}

            //f2 = f2 < m_reClip.top ? m_reClip.top : f2;     //y Top
			if (m_reClip.top > 0.0f)
			{
				f2 = tf2 * (1.0f + m_reClip.top);
				tt = m_reClip.top;
			}

			// f3 = f3 > m_reClip.right ? m_reClip.right : f3; //x Right
			if (m_reClip.right < 1.0f)
			{
				f3 = tf3 - (tf3-tf1)*(1-m_reClip.right);
				tr = m_reClip.right;
			}
            
			// f4 = f4 > m_reClip.bottom ? m_reClip.bottom : f4 ;  // y bottom
			if (m_reClip.bottom < 1.0f)
			{
				f4 = tf4 - (tf4-tf2)*(1-m_reClip.bottom);
				td = m_reClip.bottom;
			}
        }

        pVec[0] = VertexS(f1, f2, m_z, 1.0f, m_color, tl/*0.0f*/, tt/*0.0f*/);
        pVec[1] = VertexS(f3, f2, m_z, 1.0f, m_color, tr/*1.0f*/, tt/*0.0f*/);
        pVec[2] = VertexS(f1, f4, m_z, 1.0f, m_color, tl/*0.0f*/, td/*1.0f*/);
        
        pVec[3] = VertexS(f1, f4, m_z, 1.0f, m_color, tl/*0.0f*/, td/*1.0f*/);
        pVec[4] = VertexS(f3, f2, m_z, 1.0f, m_color, tr/*1.0f*/, tt/*0.0f*/);
        pVec[5] = VertexS(f3, f4, m_z, 1.0f, m_color, tr/*1.0f*/, td/*1.0f*/);

        m_pTest = /*m_pVb;*/pVec;//test

        m_pVb->Unlock();

        m_bDirty = false;
    }
}

void CSprite::Draw()
{
    if (m_bVisible == false) {
        return ;
    }

    HRESULT hr;

    ///// 以下是改版绘制流
    stDrawCommand* pDraw = CDrawFlow::Instance().getFreeDrawFlow();
    if (pDraw)
    {
        pDraw->src_blend = D3DBLEND_SRCALPHA;
        pDraw->dest_blend = D3DBLEND_INVSRCALPHA;
        pDraw->pTexture = m_pTexture;
        pDraw->shape =  D3DPT_TRIANGLELIST; //D3DPT_TRIANGLESTRIP;
        pDraw->vFormat = VertexS::FVF;
        pDraw->nCount = 2;
        pDraw->pVecBuf = m_pTest;

        CDrawFlow::Instance().increaseIndex();
    }
}