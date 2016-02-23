
///////// ֡����
#include <vector>

#ifndef _ANIMATION_H
#define _ANIMATION_H

enum eAniPlay
{
    kAP_Once,   //����һ��
    kAP_Loop,   //ѭ������
    kAP_Back,   //���󲥷�
    kAP_BackLoop,   //ѭ������
};


enum eAniState
{
    kAS_Running,    //������
    kAS_Stop,       //ֹͣ
    kAS_Pause,      //��ͣ
};

// ֡�����ṹ��
struct stFAnimation
{
    eAniPlay    ePlay;          //���ŷ�ʽ
    DWORD       dwFrameTime;    //֡ʱ��
    UINT        nStartFrame;    //��ʼ֡
    UINT        nTotalFrame;    //֡����

    std::vector<std::string>  vecTex;   //��������֡
};

class iSprite;

class CFAnimation
{
public:
    CFAnimation();
    virtual ~CFAnimation();

    void initWithA(stFAnimation& stAn); //1.���Ų��� 2.��Ӧ����֡

    void update(DWORD elapse);
    void draw();
    
    void setCurrentFrame(UINT nFrame);  //���õ�ǰ֡

    void setX(DWORD x);
    void setY(DWORD y);
    DWORD getX();
    DWORD getY();

    void setW(DWORD w);
    void setH(DWORD h);
    DWORD getW();
    DWORD getH();


    // һЩ����
    inline void restart();  
    void start();    // ���Իָ� stop �� pause ��״̬
    inline void stop();
    inline void pause();

    inline bool isRunning();   // true(running), false(stop or pause)
    inline bool isStop();      // true(stop),   false(running or pause)
    inline bool isPause();     // true(pause),  false(running or pause)

private:
    DWORD m_dwTime; //��¼����ʱ��

    DWORD   m_dwFrameTime;// �����л���֡ʱ��
    //UINT    m_nStart;   //��ʼ֡
    UINT    m_nFrame;   // ��ǰ֡
    UINT    m_nTotalFrame;// �ܹ���֡

    eAniPlay m_ePlayType;   // ѭ������
    eAniState m_eState;     // ����״̬

    // ��ǰ֡����(?)
    iSprite* m_pSprite;

    std::vector<IDirect3DTexture9* >m_vecTex;    // ��¼֡��Ӧ������ --> (�������)
};


#endif