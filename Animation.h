
///////// 帧动画
#include <vector>

#ifndef _ANIMATION_H
#define _ANIMATION_H

enum eAniPlay
{
    kAP_Once,   //播放一次
    kAP_Loop,   //循环播放
    kAP_Back,   //往后播放
    kAP_BackLoop,   //循环倒播
};


enum eAniState
{
    kAS_Running,    //播放中
    kAS_Stop,       //停止
    kAS_Pause,      //暂停
};

// 帧动画结构体
struct stFAnimation
{
    eAniPlay    ePlay;          //播放方式
    DWORD       dwFrameTime;    //帧时间
    UINT        nStartFrame;    //起始帧
    UINT        nTotalFrame;    //帧总数

    std::vector<std::string>  vecTex;   //纹理序列帧
};

class iSprite;

class CFAnimation
{
public:
    CFAnimation();
    virtual ~CFAnimation();

    void initWithA(stFAnimation& stAn); //1.播放参数 2.对应序列帧

    void update(DWORD elapse);
    void draw();
    
    void setCurrentFrame(UINT nFrame);  //设置当前帧

    void setX(DWORD x);
    void setY(DWORD y);
    DWORD getX();
    DWORD getY();

    void setW(DWORD w);
    void setH(DWORD h);
    DWORD getW();
    DWORD getH();


    // 一些操作
    inline void restart();  
    void start();    // 可以恢复 stop 和 pause 的状态
    inline void stop();
    inline void pause();

    inline bool isRunning();   // true(running), false(stop or pause)
    inline bool isStop();      // true(stop),   false(running or pause)
    inline bool isPause();     // true(pause),  false(running or pause)

private:
    DWORD m_dwTime; //记录流逝时间

    DWORD   m_dwFrameTime;// 动画切换的帧时间
    //UINT    m_nStart;   //起始帧
    UINT    m_nFrame;   // 当前帧
    UINT    m_nTotalFrame;// 总共几帧

    eAniPlay m_ePlayType;   // 循环类型
    eAniState m_eState;     // 播放状态

    // 当前帧纹理(?)
    iSprite* m_pSprite;

    std::vector<IDirect3DTexture9* >m_vecTex;    // 记录帧对应的纹理 --> (这个东西)
};


#endif