
#ifndef TETRIS_BASE_H
#define TETRIS_BASE_H

#include <vector>

//namespace Tetris{

// ����˹��������
enum eCubeType{
    kCT_None = -1,
    kCT_I   = 0, 
    kCT_J   = 1,
    kCT_7   = 2,
    kCT_O   = 3,
    kCT_S   = 4,
    kCT_T   = 5,
    kCT_Z   = 6,

    kCT_Max,
};

enum eTState{
    kTS_Empty   = 0,
    kTS_Fill    = 1,


    kTS_Num,
};

// ����С��
struct stCube{
    int x;
    int y;
    eTState state; // 0:�����, 1:�����

    stCube():x(0),y(0),state(kTS_Empty){
    }

    stCube(int _x, int _y, eTState _s){
        x = _x;
        y = _y;
        state = _s;
    }
};

// ����˹����
struct stTCube{
    eCubeType type;
    std::vector<stCube> _vecCube;
    int dir; //���� [0-3]

    stTCube():type(kCT_None), dir(0){

    }

    void Left(int value = 1);   //����value����λ(���ж��赲)
    void Right(int value = 1);  //����value����λ(���ж��赲)
    void Down(int value = 1);   //����value����λ(���ж��赲)
    void ClockTurn();       //˳ʱ��ת
    void AntiClockTurn();   //��ʱ��ת
};



///////////// ������
const int c_width = 10;
const int c_height = 20;




///////////// ����ָ��
enum eTCommand{
    kTC_None    = 0,
    kTC_Down    = 1,
    kTC_Up      = 2,
    kTC_Left    = 3,
    kTC_Right   = 4,
    kTC_TurnClockwise = 5,      //˳ʱ����ת
    kTC_TurnAnticlockwise = 6,  //��ʱ����ת


    kTC_Max,
};






// ����API


void turnClock(stTCube& cube);       //˳ʱ����ת
void turnAntiClock(stTCube& cube);   //��ʱ����ת



//} //end namespace





#endif