#ifndef TETRIS_WORLD_H
#define TETRIS_WORLD_H

#include "TetrisBase.h"

//namespace Tetris
//{



class TetrisWorld
{
protected:
    stCube** _pWorld; //��ά����
    int _width;
    int _height;
    const int _perHeight;   //Ԥ���߶�

    stTCube* _pCurTCube;
    stTCube* _pNextTcbe;    //��һ����ľ
    bool _bCurTCubeRun; //�Ƿ�����������Ļ�ľ

    unsigned long _dwFrameTimeTotal;    //�ۻ�..
    unsigned long _dwFrameInterval;     //һ֡�ļ��




    void CubeBlend();   //ִ����������ķ����������

    // ǽ��(�����ת)
    bool IfNeedWallKick();

    // ִ������
    void CommandDown();
    bool CommandLeft();
    bool CommandRight();
    void CommandTurnClock();
    void CommandTurnAntiClock();

    //���ɷ���
    void GenI(stTCube& cube);
    void GenO(stTCube& cube);
    void GenJ(stTCube& cube);
    void Gen7(stTCube& cube);
    void GenS(stTCube& cube);
    void GenT(stTCube& cube);
    void GenZ(stTCube& cube);

    //state
    enum tState{
        kStop = 0,      //ֹͣ
        kRunning = 1,   //������
        kRemoving= 2,   //������
    };

    tState _state;

public:

    TetrisWorld();
    virtual ~TetrisWorld();

    void SetWorldSize(int width, int height);

    void GenATCube();

    // ��չ
    //void SetWorldContent( �ؿ����� ); // �йؿ���

    // ������(����)
    void Start();
    void Run(unsigned long dwElapse);
    void PutATCube(const stTCube& cube);    //����һ���µķ���
    void PutACommand(eTCommand command);    //ִ��һ���������


    // ����
    int JudgeDoRemove();    //�ж����� .. ����ֵ:����������


};



//} // end namespace Tetris


#endif