#ifndef TETRIS_WORLD_H
#define TETRIS_WORLD_H

#include "TetrisBase.h"

//namespace Tetris
//{



class TetrisWorld
{
protected:
    stCube** _pWorld; //二维数组
    int _width;
    int _height;
    const int _perHeight;   //预留高度

    stTCube* _pCurTCube;
    stTCube* _pNextTcbe;    //下一个积木
    bool _bCurTCubeRun; //是否有正在下落的积木

    unsigned long _dwFrameTimeTotal;    //累积..
    unsigned long _dwFrameInterval;     //一帧的间隔




    void CubeBlend();   //执行正在下落的方块与世界绑定

    // 墙踢(针对旋转)
    bool IfNeedWallKick();

    // 执行命令
    void CommandDown();
    bool CommandLeft();
    bool CommandRight();
    void CommandTurnClock();
    void CommandTurnAntiClock();

    //生成方块
    void GenI(stTCube& cube);
    void GenO(stTCube& cube);
    void GenJ(stTCube& cube);
    void Gen7(stTCube& cube);
    void GenS(stTCube& cube);
    void GenT(stTCube& cube);
    void GenZ(stTCube& cube);

    //state
    enum tState{
        kStop = 0,      //停止
        kRunning = 1,   //进行中
        kRemoving= 2,   //消除中
    };

    tState _state;

public:

    TetrisWorld();
    virtual ~TetrisWorld();

    void SetWorldSize(int width, int height);

    void GenATCube();

    // 扩展
    //void SetWorldContent( 关卡参数 ); // 有关卡的

    // 工作流(过程)
    void Start();
    void Run(unsigned long dwElapse);
    void PutATCube(const stTCube& cube);    //放置一个新的方块
    void PutACommand(eTCommand command);    //执行一个玩家命令


    // 规则
    int JudgeDoRemove();    //判定消除 .. 返回值:消除的行数


};



//} // end namespace Tetris


#endif