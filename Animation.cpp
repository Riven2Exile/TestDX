#include "stdafx.h"
#include "Animation.h"
#include "TextureMgr.h"
#include "GameMain.h"


extern IDirect3DDevice9 *g_pDevice;
iSprite* CreateSprite(SpriteType nType);


CFAnimation::CFAnimation()
{
    m_dwTime = 0;

    m_dwFrameTime = 50;
    m_nFrame = 0;
    m_nTotalFrame = 0;

    m_ePlayType = kAP_Loop;
    m_eState = kAS_Stop;

    m_pSprite = CreateSprite(ST_MX);
}

CFAnimation::~CFAnimation()
{

}

///////////////////////

void CFAnimation::initWithA(stFAnimation& stAn)
{
    m_dwFrameTime = stAn.dwFrameTime;
    m_nFrame    = stAn.nStartFrame;
    m_nTotalFrame = stAn.nTotalFrame;
    m_ePlayType = stAn.ePlay;

    //读取各种纹理.. 纹理管理

    for (int i = 0; i < stAn.vecTex.size(); ++i)
    {
        m_vecTex.push_back( (stTexInfo*)CTextureMgr::instance().getTexture(stAn.vecTex[i]) );
    }
    
    m_pSprite->LoadAImage("", g_pDevice); //先这样。。
    m_pSprite->setTexture( m_vecTex[m_nFrame] );
}

void CFAnimation::update(DWORD elapse)
{
    if (isRunning())
    {
        m_pSprite->Update();
        // 动画进行中
        m_dwTime += elapse;

        if (m_dwTime >= m_dwFrameTime)
        {
            // 播放预定的下一帧
            m_dwTime -= m_dwFrameTime;
            
            if (kAP_Once == m_ePlayType)
            {
                ++m_nFrame;
                if (m_nFrame >= m_nTotalFrame)
                {
                    setCurrentFrame(0);
                    stop();
                }
                else
                {
                    setCurrentFrame(m_nFrame);
                }
            }
            else if (kAP_Loop == m_ePlayType)
            {
                ++m_nFrame;
                if (m_nFrame >= m_nTotalFrame)
                {
                    setCurrentFrame(0);
                }
                else
                {
                    setCurrentFrame(m_nFrame);
                }
            }
            else if (kAP_Back == m_ePlayType)
            {
                --m_nFrame;
                if (m_nFrame < 0)
                {
                    setCurrentFrame(m_nTotalFrame - 1);
                    stop();
                }
                else
                {
                    setCurrentFrame(m_nFrame);
                }
            }
            else if (kAP_BackLoop == m_ePlayType)
            {
                --m_nFrame;
                if (m_nFrame < 0)
                {
                    setCurrentFrame(m_nTotalFrame - 1);
                }
                else
                {
                    setCurrentFrame(m_nFrame);
                }
            }

        }
    }
}

void CFAnimation::draw()
{
    // 单纯的画
    m_pSprite->Draw();
}


void CFAnimation::setCurrentFrame(UINT nFrame)
{
    m_nFrame = nFrame;

    // 纹理准备
    m_pSprite->setTexture( m_vecTex[m_nFrame] );
}


/////
void CFAnimation::setX(DWORD x)
{
    m_pSprite->SetX(x);
}
void CFAnimation::setY(DWORD y)
{
    m_pSprite->SetY(y);
}
DWORD CFAnimation::getX()
{
    return m_pSprite->GetX();
}
DWORD CFAnimation::getY()
{
    return m_pSprite->GetY();
}
void CFAnimation::setW(DWORD w)
{
    m_pSprite->setWidth(w);
}
void CFAnimation::setH(DWORD h)
{
    m_pSprite->setHeight(h);
}
DWORD CFAnimation::getW()
{
    return 0;
}
DWORD CFAnimation::getH()
{
    return 0;
}
/////



void CFAnimation::start()
{
    m_eState = kAS_Running;
}
void CFAnimation::stop()
{
    m_eState = kAS_Stop;
    m_dwTime = 0;
}
void CFAnimation::pause()
{
    m_eState = kAS_Pause;
}


bool CFAnimation::isRunning()
{
    return kAS_Running == m_eState;
}
bool CFAnimation::isStop()
{
    return kAS_Stop == m_eState;
}
bool CFAnimation::isPause()
{
    return kAS_Pause == m_eState;
}