#include "../stdafx.h"
#include "RoundProcess.h"
#include "../CSprite.h"

RoundProcess::RoundProcess()
{

}

RoundProcess::~RoundProcess()
{

}


/////////////

void RoundProcess::init()
{

}

void RoundProcess::loadImage(const char* pszName, IDirect3DDevice9* pDev)
{
	return;
    D3DXIMAGE_INFO info;
    D3DXGetImageInfoFromFileA(pszName, &info);

    D3DXCreateTextureFromFileExA(pDev, pszName, info.Width, info.Height, 
        info.MipLevels, D3DUSAGE_DYNAMIC, info.Format, D3DPOOL_DEFAULT, D3DX_FILTER_TRIANGLE,  // D3DPOOL_DEFAULT²Å¿ÉÐÐ¡£¡£
        D3DX_FILTER_TRIANGLE, D3DCOLOR_ARGB(255,255,255,255), NULL, NULL, &m_pTexture);

    pDev->CreateVertexBuffer(6*sizeof(VertexS),
        D3DUSAGE_WRITEONLY,
        VertexS::FVF,
        D3DPOOL_MANAGED,
        &m_pVb,
        0);

    m_x = 0;
    m_y = 0;
    m_w = info.Width;
    m_h = info.Height;


    VertexS *pVec;
    m_pVb->Lock(0, sizeof(VertexS)*6, (void**)&pVec, 0);

    float fix = -0.5f;
    float z = 0.f;

    m_color = 0xffffffff;

    pVec[0] = VertexS(m_x + fix, m_y + fix, z, 1.0f, m_color, 0.0f, 0.0f);
    pVec[1] = VertexS(m_x + (float)info.Width + fix, m_y + fix, z, 1.0f, m_color, 1.0f, 0.0f);
    pVec[2] = VertexS(m_x + fix, m_y + (float)info.Height + fix, z, 1.0f, m_color, 0.0f, 1.0f);

    pVec[3] = VertexS(m_x + fix, m_y + (float)info.Height + fix, z, 1.0f, m_color, 0.0f, 1.0f);
    pVec[4] = VertexS(m_x + (float)info.Width + fix, m_y + fix, z, 1.0f, m_color, 1.0f, 0.0f);
    pVec[5] = VertexS(m_x + (float)info.Width + fix, m_y + (float)info.Height + fix, z, 1.0f, m_color, 1.0f, 1.0f);

    m_pVb->Unlock();
}

void RoundProcess::setProcees(float fValue)
{

}

void RoundProcess::update()
{

}

void RoundProcess::draw()
{

}